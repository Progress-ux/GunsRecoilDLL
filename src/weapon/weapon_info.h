#ifndef GUNS_RECOIL_WEAPON_INFO_H
#define GUNS_RECOIL_WEAPON_INFO_H

#define WEAPON_MAX_ID 32

#include "config/config_value.h"

typedef enum WeaponId
{
    WEAPON_ID_UNKNOWN = 0,

    WEAPON_ID_M4A1 = 22,
    WEAPON_ID_AK47 = 28,

} WeaponId;

typedef enum WeaponType
{
    WEAPON_TYPE_UNKNOWN = 0,
    WEAPON_TYPE_PISTOL,
    WEAPON_TYPE_RIFLE,
    WEAPON_TYPE_SHOTGUN
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

int WeaponInfo_GetId(const char* name);

#endif
