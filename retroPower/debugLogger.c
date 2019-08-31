#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

#include "debugLogger.h"

char debugLogPath[] = "/boot/retropower-log.txt";

void writeDebug(const powerConfig config, const char* message, ...) 
{
    char debugMessage[150];

    va_list args;
    va_start (args, message);
    vsnprintf (debugMessage, 150, message, args);
    va_end (args);

    if(config.debugActive)
    {
        if(config.writeLog)
        {
            FILE *debugLog;
            if(access(debugLogPath, F_OK) != -1) debugLog = fopen(debugLogPath, "a");
            else debugLog = fopen(debugLogPath, "w");

            fprintf(debugLog, "%s\n", debugMessage);
            fclose(debugLog);
        }
        else
        {
            printf("%s\n", debugMessage);
        }
    }
}