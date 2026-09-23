#include "core/guns_recoil.h"

#include "abi/regame_player_abi.h"

#include "core/recoil_math.h"
#include "util/logger.h"

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
