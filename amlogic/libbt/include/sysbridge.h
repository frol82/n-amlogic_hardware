#ifndef SYSBRIDGE_H
#define SYSBRIDGE_H


int amSystemWriteSetProperty(const char* key, const char* value, int leth);
int amSystemWriteGetProperty(const char* key, char* value);

#endif