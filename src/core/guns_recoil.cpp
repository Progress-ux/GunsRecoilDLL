#include "core/guns_recoil.h"

#include "abi/regame_player_abi.h"

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
            LH_DEBUG("[FireBullets3] Glock18");
            break;

        case weapon_id::USP:
            LH_DEBUG("[FireBullets3] USP");
            break;

        case weapon_id::AK47:
            LH_DEBUG("[FireBullets3] AK47");
            break;

        case weapon_id::M4A1:
            LH_DEBUG("[FireBullets3] M4A1");
            break;

        default:
            LH_DEBUG("[FireBullets3] unknown weapon id = %d", weaponId);
            break;
    }
}
