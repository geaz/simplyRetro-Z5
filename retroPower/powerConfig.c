#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "libs/ini.h"
#include "powerConfig.h"

bool parseBool(const char* value)
{
    bool parsedValue = false;
    if(strcmp(value, "true") == 0) {
        parsedValue = true;
    }
    return parsedValue;
}

static int handler(void* user, const char* section, const char* name,
                   const char* value)
{
    powerConfig* config = (powerConfig*)user;

    #define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
    if (MATCH("features", "shutdown")) 
    {
        config->shutdownActive = parseBool(value);
    } 
    else if (MATCH("features", "batCheck")) 
    {
        config->checkActive = parseBool(value);
    } 
    else if (MATCH("debug", "active")) 
    {
        config->debugActive = parseBool(value);
    } 
    else if (MATCH("debug", "writeLog")) 
    {
        config->writeLog = parseBool(value);
    } 
    else if (MATCH("debug", "onlyReadAdc")) 
    {
        config->onlyReadAdc = parseBool(value);
    } 
    else if (MATCH("pins", "shutdown")) 
    {
        config->shutdownPin = atoi(value);
    } 
    else {
        return 0;  /* unknown section/name, error */
    }
    return 1;
}

powerConfig readPowerConfig(const char* configPath) 
{
    powerConfig config;
    ini_parse(configPath, handler, &config);
    return config;
}