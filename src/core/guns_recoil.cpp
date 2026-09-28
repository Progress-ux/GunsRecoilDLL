#include "core/guns_recoil.h"

#include "abi/regame_player_abi.h"

#include "config/config_manager.h"
#include "core/config.h"
#include "core/recoil_math.h"
#include "util/logger.h"
#include "weapon/weapon_info.h"

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

    switch (weaponId)
    {
        case weapon_id::Glock18:
            recoil::ApplyVertical(vecDirShooting, 1.0f);
            break;

        case weapon_id::USP:
            recoil::ApplyVertical(vecDirShooting, 1.0f);
            break;

        case weapon_id::AK47:
            recoil::ApplyVertical(vecDirShooting, 1.0f);
            break;

        case weapon_id::M4A1:
            recoil::ApplyVertical(vecDirShooting, 1.0f);
            break;

        default:
            LH_DEBUG("[FireBullets3] unknown weapon id = %d", weaponId);
            break;
    }
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
    LH_DEBUG("[OnKickBack] weaponId: %d", weaponId);

    const WeaponParams* params = 
        ConfigManager_GetWeaponParams(&g_config_manager, weaponId);

    if (!params)
    {
        LH_DEBUG("[OnKickBack] no config for weaponId=%d", weaponId);
        return;
    }

    up_base          = params->recoil.up_base;
    lateral_base     = params->recoil.lateral_base;
    up_modifier      = params->recoil.up_modifier;
    lateral_modifier = params->recoil.lateral_modifier;
    up_max           = params->recoil.up_max;
    lateral_max      = params->recoil.lateral_max;
    direction_change = params->recoil.direction_change;
}
