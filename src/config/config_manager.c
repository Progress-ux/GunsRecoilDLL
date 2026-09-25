#include "config/config_manager.h"
#include "config/config_node.h"
#include "util/logger.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>

static void trim(char* str)
{
    char* start = str;
    char* end;

    while (isspace((unsigned char)*start)) 
        start++;

    if (start != str) 
        memmove(str, start, strlen(start) + 1);

    if (*str == '\0') return;

    end = str + strlen(str) - 1;

    while (end >= str && isspace((unsigned char)*end)) 
        end--;

    end[1] = '\0';
}

static int ParseLine(const char* line, ConfigEntry* entry)
{
    if (!line || !entry)
        return 0;

    memset(entry, 0, sizeof(*entry));

    const char* equal = strchr(line, '=');

    if (!equal)
        return 0;

    size_t key_len = (size_t)(equal - line);

    if (key_len == 0 || key_len >= sizeof(entry->key))
        return 0;

    memcpy(entry->key, line, key_len);
    entry->key[key_len] = '\0';

    strncpy(entry->value, equal + 1, sizeof(entry->value) - 1);
    entry->value[sizeof(entry->value) - 1] = '\0';

    trim(entry->key);
    trim(entry->value);

    if (entry->key[0] == '\0' || entry->value[0] == '\0')
        return 0;

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
   
    // Temp ConfigNode
    char line[128];
    char current_section[64] = "";

    int line_number = 0;

    ConfigEntry entry;

    while (fgets(line, sizeof(line), p_file))
    {
        line_number++;

        trim(line);

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
        if (!ParseLine(line, &entry))
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

        // Build Weapon Params
    }

    // Close file
    fclose(p_file);

    LH_INFO("Config loaded: %s", path);

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
