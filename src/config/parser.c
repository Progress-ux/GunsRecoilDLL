#include "parser.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>

void Config_Trim(char* str)
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

int Config_ParseLine(const char* line, ConfigEntry* entry)
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

    Config_Trim(entry->key);
    Config_Trim(entry->value);

    if (entry->key[0] == '\0' || entry->value[0] == '\0')
        return 0;

    return 1;
}
