#ifndef GUNS_RECOIL_WEAPON_INFO_H
#define GUNS_RECOIL_WEAPON_INFO_H

#define WEAPON_MAX_ID 32

typedef enum WeaponType
{
    WEAPON_TYPE_UNKNOWN = 0,
    WEAPON_TYPE_PISTOL,
    WEAPON_TYPE_RIFLE,
    WEAPON_TYPE_SHOTGUN
} WeaponType;

typedef struct RecoilParams
{
    float up_base;
    float lateral_base;

    float up_modifier;
    float lateral_modifier;

    float up_max;
    float lateral_max;

    int direction_change;
} RecoilParams;

typedef struct SpreadParams
{
    float spread;
} SpreadParams;

typedef struct WeaponParams
{
    int enabled;
    WeaponType type;

    RecoilParams recoil;
    SpreadParams spread;
} WeaponParams;

#endif
