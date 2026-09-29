#include "config/config_node.h"

#include <string.h>

static ConfigNode* ConfigNodes_Find(
    ConfigNodes* nodes,
    const char* name
)
{
    if (!nodes || !name)
        return NULL;

    for (int i = 0; i < nodes->count; i++)
    {
        if (strcmp(nodes->nodes[i].name, name) == 0)
            return &nodes->nodes[i];
    }
    return NULL;
}

static ConfigNode* CreateNode(
    ConfigNodes* nodes,
    const char* name
)
{
    if (nodes->count >= CONFIG_MAX_NODES)
        return NULL;

    ConfigNode* node = &nodes->nodes[nodes->count];

    memset(node, 0, sizeof(*node));

    strncpy(node->name, name, sizeof(node->name) - 1);
    node->name[sizeof(node->name) - 1] = '\0';

    nodes->count++;

    return node;
}

const ConfigNode* ConfigNodes_FindConst(
    const ConfigNodes* nodes,
    const char* name
)
{
    if (!nodes || !name)
        return NULL;

    for (int i = 0; i < nodes->count; i++)
    {
        if (strcmp(nodes->nodes[i].name, name) == 0)
            return &nodes->nodes[i];
    }
    return NULL;
}

ConfigNode* ConfigNodes_GetOrCreate(
    ConfigNodes* nodes,
    const char* name
)
{
    ConfigNode* node = ConfigNodes_Find(nodes, name);

    if (node)
        return node;

    return CreateNode(nodes, name);
}
