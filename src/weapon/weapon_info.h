#ifndef GUNS_RECOIL_WEAPON_INFO_H
#define GUNS_RECOIL_WEAPON_INFO_H

#define WEAPON_MAX_ID 32

#include "config/config_value.h"

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

typedef struct WeaponParams
{
    int enabled;
    WeaponType type;

    RecoilParams recoil;
    SpreadParams spread;
} WeaponParams;

#endif
