#ifndef GUNS_RECOIL_CONFIG_NODE_H
#define GUNS_RECOIL_CONFIG_NODE_H

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

typedef struct ConfigNode
{
    ConfigFloat recoil_vertical;
    ConfigFloat recoil_horizontal;
    ConfigFloat spread_base;

    int enabled;
    int type;
} ConfigNode;

#endif
