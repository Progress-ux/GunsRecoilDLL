#include "core/guns_recoil.h"

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
    LH_DEBUG("[GunsRecoil_FireBullets3] called!");
}
