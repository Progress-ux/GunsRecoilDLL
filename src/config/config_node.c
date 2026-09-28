#include "config/config_node.h"

#include <string.h>

static ConfigNode* FindNode(
    ConfigNodes* nodes,
    const char* name
)
{
    int i;

    for (i = 0; i < nodes->count; i++)
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

ConfigNode* GetOrCreateNode(
    ConfigNodes* nodes,
    const char* name
)
{
    ConfigNode* node = FindNode(nodes, name);

    if (node)
        return node;

    return CreateNode(nodes, name);
}
