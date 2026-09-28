#ifndef GUNS_RECOIL_CONFIG_NODE_H
#define GUNS_RECOIL_CONFIG_NODE_H

#include "weapon/weapon_info.h"

#define CONFIG_MAX_NODES 64

typedef struct ConfigNode
{
    char name[64];

    RecoilParams recoil;
    SpreadParams spread;

    ConfigInt enabled;
    ConfigInt type;
} ConfigNode;

typedef struct ConfigNodes
{
    ConfigNode nodes[CONFIG_MAX_NODES];
    int count;
} ConfigNodes;

ConfigNode* ConfigNodes_GetOrCreate(
    ConfigNodes* nodes,
    const char* name
);

#endif
