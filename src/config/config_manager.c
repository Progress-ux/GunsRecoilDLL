#include "config/config_manager.h"
#include "config/config_node.h"
#include "config/parser.h"
#include "util/logger.h"

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
   
    // Temp ConfigNode
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
            if (sscanf(line, "[%63[^]]", current_section) != 1)
            {
                LH_ERROR("Invalid section at line %d", line_number);
                fclose(p_file);
                return 0;
            }

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

    // Build Weapon Params

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
