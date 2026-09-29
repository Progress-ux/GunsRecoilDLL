#pragma once

class CBaseEntity;
class CBasePlayerWeapon;

#include <extdll.h>

namespace weapon_id
{
    constexpr int Glock18 = 17;
    constexpr int USP     = 16;
    constexpr int AK47    = 28;
    constexpr int M4A1    = 22;
}

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
);

void GunsRecoil_OnKickBack(
    CBasePlayerWeapon* pThis,
    float& up_base,
    float& lateral_base,
    float& up_modifier,
    float& lateral_modifier,
    float& up_max,
    float& lateral_max,
    int& direction_change
);
