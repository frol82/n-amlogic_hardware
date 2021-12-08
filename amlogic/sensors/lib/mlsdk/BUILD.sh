#!/bin/bash

# This is a sample of the command line make used to build
#   the libraries and binaries.
# Please customize this path to match the location of your
#   Android source tree. Other variables may also need
#   to be customized such as:
#   $CROSS, $PRODUCT, $KERNEL_ROOT

export ANDROID_BASE=/home/mcaramello/Software/Android/gingerbread/trunk/beagleboard_gingerbread

make MPU_NAME=MPU6050B1 VERBOSE=1 TARGET=android ANDROID_ROOT=${ANDROID_BASE} KERNEL_ROOT=${ANDROID_BASE}/kernel CROSS=${ANDROID_BASE}/prebuilt/linux-x86/toolchain/arm-eabi-4.4.0/bin/arm-eabi- PRODUCT=beagleboard MPL_LIB_NAME=mplmpu echo_in_colors=echo -f Android-shared.mk

make MPU_NAME=MPU6050B1 VERBOSE=1 TARGET=android ANDROID_ROOT=${ANDROID_BASE} KERNEL_ROOT=${ANDROID_BASE}/kernel CROSS=${ANDROID_BASE}/prebuilt/linux-x86/toolchain/arm-eabi-4.4.0/bin/arm-eabi- PRODUCT=beagleboard MPL_LIB_NAME=mplmpu echo_in_colors=echo -f Android-static.mk

#!/bin/bash

# This is a sample of the command line make used to build
#   the libraries and binaries.
# Please customize this path to match the location of your
#   Android source tree. Other variables may also need
#   to be customized such as:
#   $CROSS, $PRODUCT, $KERNEL_ROOT

export ANDROID_BASE=/home/mcaramello/Software/Android/gingerbread/trunk/beagleboard_gingerbread

make MPU_NAME=MPU3050 VERBOSE=1 TARGET=android ANDROID_ROOT=${ANDROID_BASE} KERNEL_ROOT=${ANDROID_BASE}/kernel CROSS=${ANDROID_BASE}/prebuilt/linux-x86/toolchain/arm-eabi-4.4.0/bin/arm-eabi- PRODUCT=beagleboard MPL_LIB_NAME=mplmpu echo_in_colors=echo -f Android-shared.mk

make MPU_NAME=MPU3050 VERBOSE=1 TARGET=android ANDROID_ROOT=${ANDROID_BASE} KERNEL_ROOT=${ANDROID_BASE}/kernel CROSS=${ANDROID_BASE}/prebuilt/linux-x86/toolchain/arm-eabi-4.4.0/bin/arm-eabi- PRODUCT=beagleboard MPL_LIB_NAME=mplmpu echo_in_colors=echo -f Android-static.mk

