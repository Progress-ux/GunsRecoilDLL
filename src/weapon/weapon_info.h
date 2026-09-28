#ifndef GUNS_RECOIL_WEAPON_INFO_H
#define GUNS_RECOIL_WEAPON_INFO_H

#define WEAPON_MAX_ID 32

#include "config/config_value.h"

typedef enum WeaponId
{
    WEAPON_ID_UNKNOWN = 0,

    WEAPON_ID_P228 = 1,
    WEAPON_ID_SCOUT = 3,
    WEAPON_ID_XM1014 = 5,
    WEAPON_ID_MAC10 = 7,
    WEAPON_ID_AUG = 8,
    WEAPON_ID_ELITE = 10,
    WEAPON_ID_FIVESEVEN = 11,
    WEAPON_ID_UMP45 = 12,
    WEAPON_ID_SG550 = 13,
    WEAPON_ID_GALIL = 14,
    WEAPON_ID_FAMAS = 15,
    WEAPON_ID_USP = 16,
    WEAPON_ID_GLOCK18 = 17,
    WEAPON_ID_AWP = 18,
    WEAPON_ID_MP5 = 19,
    WEAPON_ID_M249 = 20,
    WEAPON_ID_M3 = 21,
    WEAPON_ID_M4A1 = 22,
    WEAPON_ID_TMP = 23,
    WEAPON_ID_G3SG1 = 24,
    WEAPON_ID_SG552 = 25,
    WEAPON_ID_DEAGLE = 26,
    WEAPON_ID_AK47 = 28,
    WEAPON_ID_P90 = 30

} WeaponId;

typedef enum WeaponType
{
    WEAPON_TYPE_UNKNOWN = 0,
    WEAPON_TYPE_PISTOL,
    WEAPON_TYPE_SMG,
    WEAPON_TYPE_RIFLE,
    WEAPON_TYPE_SHOTGUN,
    WEAPON_TYPE_SNIPER,
    WEAPON_TYPE_MACHINEGUN

} WeaponType;

typedef struct RecoilParams
{
    ConfigFloat up_base;
    ConfigFloat lateral_base;

    ConfigFloat up_modifier;
    ConfigFloat lateral_modifier;

    ConfigFloat up_max;
    ConfigFloat lateral_max;

    ConfigInt direction_change;
} RecoilParams;

typedef struct SpreadParams
{
    ConfigFloat spread;
} SpreadParams;

typedef struct WeaponRecoil
{
    float up_base;
    float lateral_base;

    float up_modifier;
    float lateral_modifier;

    float up_max;
    float lateral_max;

    int direction_change;
} WeaponRecoil;

typedef struct WeaponSpread
{
    float spread;
} WeaponSpread;

typedef struct WeaponParams
{
    int enabled;
    WeaponType type;

    WeaponRecoil recoil;
    WeaponSpread spread;
} WeaponParams;

WeaponType WeaponInfo_GetType(const char* name);
int WeaponInfo_GetId(const char* name);

#endif
