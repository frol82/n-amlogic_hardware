/*
 * Copyright (c) 2017 Amlogic, Inc. All rights reserved.
 *
 * This source code is subject to the terms and conditions defined in the
 * file 'LICENSE' which is part of this source code package.
 *
 * Description:
 *      used for memory track.
 */

#define LOG_TAG "memtrack_aml"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>
#include <inttypes.h>
#include <dirent.h>
#include <stdint.h>

#include <hardware/memtrack.h>
#include <log/log.h>

#define DEBUG 0
#define VMALLOCION "/proc/ion/vmalloc_ion"
#define GPUT8X "/sys/kernel/debug/mali0/ctx"
#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

static struct hw_module_methods_t memtrack_module_methods = {
    .open = NULL,
};

struct memtrack_record record_templates[] = {
    {
        .flags = MEMTRACK_FLAG_SMAPS_UNACCOUNTED |
                 MEMTRACK_FLAG_PRIVATE |
                 MEMTRACK_FLAG_NONSECURE,
    },

/*
    {
        .flags = MEMTRACK_FLAG_SMAPS_ACCOUNTED |
                 MEMTRACK_FLAG_PRIVATE |
                 MEMTRACK_FLAG_NONSECURE,
    },
*/
};

// just return 0
int aml_memtrack_init(const struct memtrack_module *module)
{
    return 0;
}

/*
 * find the userid of process @pid
 * return the userid if success, or return -1 if not
 */
static int memtrack_find_userid(int pid)
{
    FILE *fp;
    char line[1024];
    char tmp[128];
    int userid;

    sprintf(tmp, "/proc/%d/status", pid);
    if ((fp=fopen(tmp, "r")) == NULL) {
        if (DEBUG) ALOGD("open file %s error %s", tmp, strerror(errno));
        return -1;
    }

    while (fgets(line, sizeof(line), fp) != NULL) {
        if (sscanf(line, "Uid: %d", &userid) == 1) {
            fclose(fp);
            return userid;
        }
    }

    // should never reach here
    fclose(fp);
    return -1;
}

static unsigned int memtrack_read_smaps(FILE *fp)
{
    char line[1024];
    unsigned int size, sum = 0;
    int skip, done = 0;

    uint64_t start;
    uint64_t end = 0;
    int len;
    char *name;
    int nameLen, name_pos;

    if(fgets(line, sizeof(line), fp) == 0) {
        return 0;
    }

    while (!done) {
        skip = 0;

        len = strlen(line);
        if (len < 1)
            return 0;

        line[--len] = 0;

        if (sscanf(line, "%"SCNx64 "-%"SCNx64 " %*s %*x %*x:%*x %*d%n", &start, &end, &name_pos) != 2) {
            skip = 1;
        } else {
            while (isspace(line[name_pos])) {
                name_pos += 1;
            }
            name = line + name_pos;
            nameLen = strlen(name);

            if (nameLen >= 8 &&
                    (!strncmp(name, "/dev/mali", 6) || !strncmp(name, "/dev/ump", 6))) {
                skip = 0;
            } else {
                skip = 1;
            }

        }

        while (1) {
            if (fgets(line, 1024, fp) == 0) {
                done = 1;
                break;
            }

            if(!skip) {
                if (line[0] == 'S' && sscanf(line, "Size: %d kB", &size) == 1) {
                    sum += size;
                }
            }

            if (sscanf(line, "%" SCNx64 "-%" SCNx64 " %*s %*x %*x:%*x %*d", &start, &end) == 2) {
                // looks like a new mapping
                // example: "10000000-10001000 ---p 10000000 00:00 0"
                break;
            }
        }
    }

    // converted into Bytes
    return (sum * 1024);
}

// mali t82x t83x
static int memtrack_get_gpuT8X(char *path)
{
    FILE *file;
    char line[1024];

    int gpu_size = 0;

    if ((file = fopen(path, "r")) == NULL) {
        if (DEBUG) ALOGD("open file %s error %s", path, strerror(errno));
        return 0;
    }

    while (fgets(line, sizeof(line), file) != NULL) {
            if (sscanf(line, "Total allocated memory: %d", &gpu_size) != 1)
                continue;
            else
                break;
    }
    fclose(file);
    return gpu_size;
}

static unsigned int memtrack_get_gpuMem(int pid)
{
    FILE *fp;
    char *cp, tmp[128];
    unsigned int result;

    DIR *gpudir;
    struct dirent *dir;
    int gpid = -1;

    gpudir = opendir(GPUT8X);
    if (!gpudir) {
        if (DEBUG)
            ALOGD("open %s error %s\n", GPUT8X, strerror(errno));
        sprintf(tmp, "/proc/%d/smaps", pid);
        fp = fopen(tmp, "r");
        if (fp == NULL) {
            if (DEBUG) ALOGD("open file %s error %s", tmp, strerror(errno));
            return 0;
        }
        result = memtrack_read_smaps(fp);

        fclose(fp);
        return result;
    } else {
        while ((dir = readdir(gpudir))) {
            strcpy(tmp, dir->d_name);
            if ((cp=strchr(tmp, '_'))) {
                *cp = '\0';
                gpid = atoi(tmp);
                if (gpid == pid) {
                    sprintf(tmp, GPUT8X"/%s/%s", dir->d_name, "mem_profile");
                    result = memtrack_get_gpuT8X(tmp);
                    closedir(gpudir);
                    return result;
                }
            }
        }
        closedir(gpudir);
    }
    return 0;
}

static int memtrack_get_memory(pid_t pid, enum memtrack_type type,
                             struct memtrack_record *records,
                             size_t *num_records)
{
    FILE *fp;
    FILE *ion_fp;
    char line[1024];
    char tmp[128];
    unsigned int mali_inuse = 0;
    unsigned int size;
    size_t unaccounted_size = 0;

    char ion_name[128];
    int ion_pid;
    unsigned int ion_size;
    unsigned int gpu_size;


   // ALOGD("type is %d, pid is %d\n", type, pid);
    size_t allocated_records =  ARRAY_SIZE(record_templates);
    *num_records = ARRAY_SIZE(record_templates);

    if (records == NULL) {
        return 0;
    }

    memcpy(records, record_templates, sizeof(struct memtrack_record) * allocated_records);

    if (type == MEMTRACK_TYPE_GL) {
        // find the user id of the process, only support calculate the non root process
        int ret = memtrack_find_userid(pid);
        if (ret <= 0) {
            return -1;
        }
        gpu_size = memtrack_get_gpuMem(pid);
        unaccounted_size += gpu_size;
    } else if (type == MEMTRACK_TYPE_GRAPHICS) {
        sprintf(tmp, VMALLOCION);
        if ((ion_fp = fopen(tmp, "r")) == NULL) {
            if (DEBUG) ALOGD("open file %s error %s", tmp, strerror(errno));
            return -errno;
        }

        while(fgets(line, sizeof(line), ion_fp) != NULL) {
            if (sscanf(line, "%s%d%u", ion_name, &ion_pid, &ion_size) != 3) {
                continue;
            } else {
                if (ion_pid == pid) {
                    unaccounted_size += ion_size;
                }
            }

        }

        fclose(ion_fp);
    }

    if (allocated_records > 0) {
        records[0].size_in_bytes = unaccounted_size;
       // ALOGD("graphic %u\n", unaccounted_size);
    }

    return 0;
}

int aml_memtrack_get_memory(const struct memtrack_module *module,
                                pid_t pid,
                                int type,
                                struct memtrack_record *records,
                                size_t *num_records)
{
    if (type == MEMTRACK_TYPE_GL || type == MEMTRACK_TYPE_GRAPHICS) {
        return memtrack_get_memory(pid, type, records, num_records);

    } else {
        return -EINVAL;
    }
}


struct memtrack_module HAL_MODULE_INFO_SYM = {
    common: {
        tag: HARDWARE_MODULE_TAG,
        module_api_version: MEMTRACK_MODULE_API_VERSION_0_1,
        hal_api_version: HARDWARE_HAL_API_VERSION,
        id: MEMTRACK_HARDWARE_MODULE_ID,
        name: "aml Memory Tracker HAL",
        author: "amlogic",
        methods: &memtrack_module_methods,
    },

    init: aml_memtrack_init,
    getMemory: aml_memtrack_get_memory,
};
