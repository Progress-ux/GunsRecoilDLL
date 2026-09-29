#include "config/config_node.h"
#include "config/parser.h"
#include "util/logger.h"
#include "weapon/weapon_info.h"
#include "config/config_manager.h"

#include <stdio.h>
#include <string.h>

#define APPLY_FLOAT(field, keyname)                          \
    if (strcmp(entry->key, keyname) == 0)                    \
    {                                                        \
        if (!Config_ParseFloat(entry->value, &(field).value))\
            return 0;                                        \
        (field).set = 1;                                     \
        return 1;                                            \
    }

#define APPLY_INT(field, keyname)                            \
    if (strcmp(entry->key, keyname) == 0)                    \
    {                                                        \
        if (!Config_ParseInt(entry->value, &(field).value))  \
            return 0;                                        \
        (field).set = 1;                                     \
        return 1;                                            \
    }

static int ApplyEntry(
    ConfigNode* node,
    const ConfigEntry* entry
)
{
    if (!node || !entry)
        return 0;

    APPLY_FLOAT(
        node->recoil.up_base,
        "recoil.up_base"
    );

    APPLY_FLOAT(
        node->recoil.lateral_base,
        "recoil.lateral_base"
    );

    APPLY_FLOAT(
        node->recoil.up_modifier,
        "recoil.up_modifier"
    );

    APPLY_FLOAT(
        node->recoil.lateral_modifier,
        "recoil.lateral_modifier"
    );

    APPLY_FLOAT(
        node->recoil.up_max,
        "recoil.up_max"
    );

    APPLY_FLOAT(
        node->recoil.lateral_max,
        "recoil.lateral_max"
    );

    APPLY_INT(
        node->recoil.direction_change,
        "recoil.direction_change"
    );

    APPLY_FLOAT(
        node->spread.spread,
        "spread"
    );

    return 0;
}

static int IsWeaponNode(const char* name)
{
    if (!name)
        return 0;
    return strchr(name, '.') != NULL;
}

static int BuildWeaponParams(
    ConfigManager* manager,
    ConfigNode* node
)
{
    if (!manager || !node)
        return 0;

    if (!IsWeaponNode(node->name))
        return 1;

    // Which weapon corresponds to node->name
    int weapon_id = WeaponInfo_GetId(node->name);
    if (!weapon_id)
    {
        LH_ERROR(
            "Unknown weapon section: '%s'",
            node->name
        );
        return 0;
    }

    // Write variables to manager->weapon_params[]
    WeaponParams* params =
        &manager->weapon_params[weapon_id];

    params->enabled = node->enabled.value;
    params->type = WeaponInfo_GetType(node->name);

    params->recoil.up_base =
        node->recoil.up_base;

    params->recoil.lateral_base =
        node->recoil.lateral_base;

    params->recoil.up_modifier =
        node->recoil.up_modifier;

    params->recoil.lateral_modifier =
        node->recoil.lateral_modifier;

    params->recoil.up_max =
        node->recoil.up_max;

    params->recoil.lateral_max =
        node->recoil.lateral_max;

    params->recoil.direction_change =
        node->recoil.direction_change;

    params->spread.spread =
        node->spread.spread;

    return 1;
}

static int GetParentName(
    const char* name,
    char* parent,
    size_t parent_size
)
{
    if (!name || !parent || parent_size == 0)
        return 0;

    if (strcmp(name, "default") == 0)
        return 0;

    const char* dot = strrchr(name, '.');

    if (!dot)
    {
        strncpy(parent, "default", parent_size - 1);
        parent[parent_size - 1] = '\0';
        return 1;
    }

    size_t lenght = (size_t)(dot - name);

    if (lenght == 0 || lenght >= parent_size)
        return 0;
    
    memcpy(parent, name, lenght);
    parent[lenght] = '\0';

    return 1;
}

static void MergeNode(
    ConfigNode* dst,
    const ConfigNode* src
)
{
    if (src->recoil.up_base.set)
        dst->recoil.up_base = src->recoil.up_base;

    if (src->recoil.lateral_base.set)
        dst->recoil.lateral_base = src->recoil.lateral_base;

    if (src->recoil.up_modifier.set)
        dst->recoil.up_modifier = src->recoil.up_modifier;

    if (src->recoil.lateral_modifier.set)
        dst->recoil.lateral_modifier = src->recoil.lateral_modifier;

    if (src->recoil.up_max.set)
        dst->recoil.up_max = src->recoil.up_max;

    if (src->recoil.lateral_max.set)
        dst->recoil.lateral_max = src->recoil.lateral_max;

    if (src->recoil.direction_change.set)
        dst->recoil.direction_change = src->recoil.direction_change;

    if (src->spread.spread.set)
        dst->spread.spread = src->spread.spread;

    if (src->enabled.set)
        dst->enabled = src->enabled;

    if (src->type.set)
        dst->type = src->type;
}

static int ResolveNode(
    const ConfigNodes* nodes,
    const ConfigNode* node,
    ConfigNode* result
)
{
    if (!nodes || !node || !result)
        return 0;

    memset(result, 0, sizeof(*result));

    char parent_name[64];

    if (!GetParentName(node->name, parent_name, sizeof(parent_name)))
    {
        *result = *node;
        return 1;
    }

    const ConfigNode* parent =
        ConfigNodes_FindConst(nodes, parent_name);

    if (!parent)
    {
        LH_ERROR(
            "Parent node '%s' not found for '%s'",
            parent_name,
            node->name
        );
        return 0;
    }

    ConfigNode resolved_parent;
    if (!ResolveNode(nodes, parent, &resolved_parent))
        return 0;

    *result = resolved_parent;

    MergeNode(result, node);

    strcpy(result->name, node->name);

    return 1;
}

int ConfigManager_Load(ConfigManager* manager,
                       const char* path)
{
    if (!manager || !path) 
    {
        LH_ERROR("Manager not initialized!");
        return 0;
    }
    
    // Open file
    FILE* p_file = fopen(path, "r");
    if (p_file == NULL) 
    {
        LH_ERROR("Failed to open config: %s", path);
        return 0;
    }
   
    // Temporary config nodes
    char line[128];
    char current_section[64] = "";

    int line_number = 0;

    ConfigEntry entry;
    ConfigNodes config_nodes;
    memset(&config_nodes, 0, sizeof(config_nodes));

    while (fgets(line, sizeof(line), p_file))
    {
        line_number++;

        Config_Trim(line);

        if (line[0] == '\0' || 
            line[0] == ';' || 
            line[0] == '#')
        {
            continue;
        }

        size_t len = strlen(line);

        // Section
        if (line[0] == '[' && len >= 2 && line[len - 1] == ']')
        {
            size_t section_len = len - 2;

            if (section_len == 0 || section_len >= sizeof(current_section))
            {
                LH_ERROR("Invalid section at line %d", line_number);
                fclose(p_file);
                return 0;
            }

            memcpy(current_section, line + 1, section_len);

            current_section[section_len] = '\0';

            LH_DEBUG(
                "Section: [%s]",
                current_section
            );

            continue;
        }

        // Parse Line to key = value
        if (!Config_ParseLine(line, &entry))
        {
            LH_ERROR(
                "Invalid config entry at line %d: %s", 
                line_number, 
                line
            );
            fclose(p_file);
            return 0;
        }

        LH_DEBUG(
            "key='%s' value='%s'", 
            entry.key, 
            entry.value
        );

        // if the parameter precedes the first section
        if (current_section[0] == '\0')
        {
            LH_ERROR(
                "Config entry outside of section at line %d",
                line_number
            );

            fclose(p_file);
            return 0;
        }

        // Create/Find config nodes 
        ConfigNode* node = 
            ConfigNodes_GetOrCreate(&config_nodes, current_section);

        if (!node)
        {
            LH_ERROR(
                "Failed to create config node for section '%s' at line %d",
                current_section,
                line_number
            );

            fclose(p_file);
            return 0;
        }

        // Apply key/value to node
        if (!ApplyEntry(node, &entry))
        {
            LH_ERROR(
                "Invalid key/value at line %d: %s = %s",
                line_number,
                entry.key,
                entry.value
            );

            fclose(p_file);
            return 0;
        }
    }

    // Close file
    fclose(p_file);

    LH_INFO("Config loaded: %s", path);

    // Resolve node
    for (int i = 0; i < config_nodes.count; i++)
    {
        ConfigNode resolved;
        if (!ResolveNode(&config_nodes, &config_nodes.nodes[i], &resolved))
        {
            LH_ERROR(
                "Failed to resolve node '%s'",
                config_nodes.nodes[i].name
            );
            return 0;
        }
        LH_DEBUG(
            "Resolved node: %s | up_base=%.2f lateral_base=%.2f spread=%.2f",
            resolved.name,
            resolved.recoil.up_base.value,
            resolved.recoil.lateral_base.value,
            resolved.spread.spread.value
        );

        // Build Weapon Params
        if (!BuildWeaponParams(manager, &resolved))
        {
            LH_ERROR(
                "Failed to build weapon params from node '%s'",
                resolved.name
            );
            return 0;
        }
    }

    return 1;
}

int ConfigManager_Reload(ConfigManager* manager,
                         const char* path)
{
    ConfigManager temporary;

    if (!manager)
        return 0;

    if (!ConfigManager_Load(&temporary, path))
        return 0;

    memcpy(
        manager,
        &temporary,
        sizeof(temporary)
    );

    return 1;
}

const WeaponParams* ConfigManager_GetWeaponParams(
    const ConfigManager* manager,
    int weapon_id
)
{
    if (!manager)
        return NULL;

    if (weapon_id < 0 || weapon_id >= WEAPON_MAX_ID)
        return NULL;

    return &manager->weapon_params[weapon_id];
}
