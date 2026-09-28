#include "weapon_info.h"

#include <string.h>

int WeaponInfo_GetId(const char* name)
{
    if (!name)
        return 0;

    if (strcmp(name, "rifle.ak-47") == 0)
        return WEAPON_ID_AK47;

    if (strcmp(name, "rifle.m4a1") == 0)
        return WEAPON_ID_M4A1;

    return WEAPON_ID_UNKNOWN;
}
