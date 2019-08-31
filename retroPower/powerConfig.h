#ifndef POWERCONFIG_H
#define POWERCONFIG_H

#include <stdbool.h>

typedef struct
{
    bool shutdownActive;
    bool checkActive;
    bool debugActive;
    bool writeLog;
    bool onlyReadAdc;
    int shutdownPin;
} powerConfig;

powerConfig readPowerConfig(const char* configPath);

#endif /* POWERCONFIG_H */