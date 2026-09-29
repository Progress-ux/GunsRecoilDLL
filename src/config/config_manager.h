#ifndef GUNS_RECOIL_CONFIG_MANAGER_H
#define GUNS_RECOIL_CONFIG_MANAGER_H

#include "weapon/weapon_info.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ConfigManager
{
    WeaponParams weapon_params[WEAPON_MAX_ID];
} ConfigManager;

int ConfigManager_Load(
    ConfigManager* manager,
    const char* path
);

int ConfigManager_Reload(
    ConfigManager* manager,
    const char* path
);

const WeaponParams* ConfigManager_GetWeaponParams(
    const ConfigManager* manager,
    int weapon_id
);

#ifdef __cplusplus
}
#endif

#endif
