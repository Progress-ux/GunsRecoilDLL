#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
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

int Config_ParseFloat(const char* str, float* value)
{
    if (!str || *str == '\0')
        return 0;

    char *endptr;
    float val = strtof(str, &endptr);

    if (endptr == str)
        return 0;
    
    while(isspace((unsigned char)*endptr))
        endptr++;

    if (*endptr != '\0')
        return 0;

    if (value != NULL)
        *value = val;

    return 1;
}

int Config_ParseInt(const char* str, int* value)
{
    int sign = 1;
    int result = 0;
    const char* p = str;

    if (!str || !value || *str == '\0')
        return 0;

    if (*p == '-')
    {
        sign = -1;
        p++;
    }
    else if (*p == '+')
    {
        p++;
    }

    if (*p == '\0')
        return 0;

    while (*p)
    {
        if (*p < '0' || *p > '9')
            return 0;

        result = result * 10 + (*p - '0');
        p++;
    }

    *value = result * sign;

    return 1;
}
