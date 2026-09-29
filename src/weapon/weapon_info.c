#include "weapon_info.h"

#include <string.h>

WeaponType WeaponInfo_GetType(const char* name)
{
    if (!name)
        return WEAPON_TYPE_UNKNOWN;

    if (strncmp(name, "pistol.", 7) == 0)
        return WEAPON_TYPE_PISTOL;

    if (strncmp(name, "rifle.", 6) == 0)
        return WEAPON_TYPE_RIFLE;

    if (strncmp(name, "shotgun.", 8) == 0)
        return WEAPON_TYPE_SHOTGUN;

    if (strncmp(name, "smg.", 4) == 0)
        return WEAPON_TYPE_SMG;

    if (strncmp(name, "sniper.", 7) == 0)
        return WEAPON_TYPE_SNIPER;

    if (strncmp(name, "machinegun.", 11) == 0)
        return WEAPON_TYPE_MACHINEGUN;

    return WEAPON_TYPE_UNKNOWN;
}

int WeaponInfo_GetId(const char* name)
{
    if (!name)
        return WEAPON_ID_UNKNOWN;

    if (strcmp(name, "pistol.p228") == 0)
        return WEAPON_ID_P228;

    if (strcmp(name, "sniper.scout") == 0)
        return WEAPON_ID_SCOUT;

    if (strcmp(name, "shotgun.xm1014") == 0)
        return WEAPON_ID_XM1014;

    if (strcmp(name, "smg.mac10") == 0)
        return WEAPON_ID_MAC10;

    if (strcmp(name, "rifle.aug") == 0)
        return WEAPON_ID_AUG;

    if (strcmp(name, "pistol.elite") == 0)
        return WEAPON_ID_ELITE;

    if (strcmp(name, "pistol.fiveseven") == 0)
        return WEAPON_ID_FIVESEVEN;

    if (strcmp(name, "smg.ump45") == 0)
        return WEAPON_ID_UMP45;

    if (strcmp(name, "sniper.sg550") == 0)
        return WEAPON_ID_SG550;

    if (strcmp(name, "rifle.galil") == 0)
        return WEAPON_ID_GALIL;

    if (strcmp(name, "rifle.famas") == 0)
        return WEAPON_ID_FAMAS;

    if (strcmp(name, "pistol.usp") == 0)
        return WEAPON_ID_USP;

    if (strcmp(name, "pistol.glock18") == 0)
        return WEAPON_ID_GLOCK18;

    if (strcmp(name, "sniper.awp") == 0)
        return WEAPON_ID_AWP;

    if (strcmp(name, "smg.mp5") == 0)
        return WEAPON_ID_MP5;

    if (strcmp(name, "machinegun.m249") == 0)
        return WEAPON_ID_M249;

    if (strcmp(name, "shotgun.m3") == 0)
        return WEAPON_ID_M3;

    if (strcmp(name, "rifle.m4a1") == 0)
        return WEAPON_ID_M4A1;

    if (strcmp(name, "smg.tmp") == 0)
        return WEAPON_ID_TMP;

    if (strcmp(name, "sniper.g3sg1") == 0)
        return WEAPON_ID_G3SG1;

    if (strcmp(name, "rifle.sg552") == 0)
        return WEAPON_ID_SG552;

    if (strcmp(name, "pistol.deagle") == 0)
        return WEAPON_ID_DEAGLE;

    if (strcmp(name, "rifle.ak-47") == 0)
        return WEAPON_ID_AK47;

    if (strcmp(name, "smg.p90") == 0)
        return WEAPON_ID_P90;

    return WEAPON_ID_UNKNOWN;
}
