#ifndef GUNS_RECOIL_CONFIG_NODE_H
#define GUNS_RECOIL_CONFIG_NODE_H
#define CONFIG_MAX_NODES 64

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

typedef struct ConfigNode
{
    char name[64];

    ConfigFloat recoil_vertical;
    ConfigFloat recoil_horizontal;
    ConfigFloat spread_base;

    ConfigInt enabled;
    ConfigInt type;
} ConfigNode;

typedef struct ConfigNodes
{
    ConfigNode nodes[CONFIG_MAX_NODES];
    int count;
} ConfigNodes;

ConfigNode* GetOrCreateNode(
    ConfigNodes* nodes,
    const char* name
);

#endif
