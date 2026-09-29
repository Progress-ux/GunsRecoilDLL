#include "core/guns_recoil.h"

#include "abi/regame_player_abi.h"

#include "config/config_manager.h"
#include "core/config.h"
#include "util/logger.h"
#include "vector.h"
#include "weapon/weapon_info.h"

#define APPLY_IF_SET(param, target) \
    if ((param).set)                \
        (target) = (param).value

void GunsRecoil_FireBullets3(
    CBaseEntity* pThis,
    Vector& vecSrc,
    Vector& vecDirShooting,
    float& vecSpread,
    float& flDistance,
    int& iPenetration,
    int& iBulletType,
    int& iDamage,
    float& flRangeModifier,
    entvars_t* pevAttacker,
    const bool& bPistol,
    const int& shared_rand
)
{
    const int weaponId = regame::GetWeaponId(
        regame::GetActiveItem(pThis)
    );

    const WeaponParams* params = 
        ConfigManager_GetWeaponParams(&g_config_manager, weaponId);

    if (!params)
    {
        LH_DEBUG("[OnKickBack] no config for weaponId=%d", weaponId);
        return;
    }

    APPLY_IF_SET(params->spread.spread, vecSpread);
}

void GunsRecoil_OnKickBack(
    CBasePlayerWeapon* pThis,
    float& up_base,
    float& lateral_base,
    float& up_modifier,
    float& lateral_modifier,
    float& up_max,
    float& lateral_max,
    int& direction_change
)
{
    const int weaponId = regame::GetWeaponId(pThis);

    const WeaponParams* params = 
        ConfigManager_GetWeaponParams(&g_config_manager, weaponId);

    if (!params)
    {
        LH_DEBUG("[OnKickBack] no config for weaponId=%d", weaponId);
        return;
    }

    APPLY_IF_SET(params->recoil.up_base, up_base);
    APPLY_IF_SET(params->recoil.lateral_base, lateral_base);
    APPLY_IF_SET(params->recoil.up_modifier, up_modifier);
    APPLY_IF_SET(params->recoil.lateral_modifier, lateral_modifier);
    APPLY_IF_SET(params->recoil.up_max, up_max);
    APPLY_IF_SET(params->recoil.lateral_max, lateral_max);
    APPLY_IF_SET(params->recoil.direction_change, direction_change);
}
