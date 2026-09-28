#ifndef GUNS_RECOIL_CONFIG_VALUE_H
#define GUNS_RECOIL_CONFIG_VALUE_H

typedef struct ConfigEntry 
{
    char key[64];
    char value[64];
} ConfigEntry;

typedef struct ConfigFloat
{
    int set;
    float value;
} ConfigFloat;

typedef struct ConfigInt
{
    int set;
    int value;
} ConfigInt;

#endif // !GUNS_RECOIL_CONFIG_VALUE_H
