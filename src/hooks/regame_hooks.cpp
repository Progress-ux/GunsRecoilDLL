#include <extdll.h>

#include "abi/regamehookchain_abi.h"
#include "regame_hooks.h"

#include "util/logger.h"
#include "regame_context.h"

#include "core/guns_recoil.h"

namespace 
{
    regame::IReGameHookRegistry_CBaseEntity_FireBullets3* 
        g_fireBullets3 = nullptr;
    regame::IReGameHookRegistry_CBasePlayerWeapon_KickBack*
        g_kickBack = nullptr;

    void OnKickBack(
        regame::IReGameHook_CBasePlayerWeapon_KickBack* chain,
        CBasePlayerWeapon* pThis,
        float up_base,
        float lateral_base,
        float up_modifier,
        float lateral_modifier,
        float up_max,
        float lateral_max,
        int direction_change
    )
    {
        chain->callNext(
            pThis,
            up_base,
            lateral_base,
            up_modifier,
            lateral_modifier,
            up_max,
            lateral_max,
            direction_change
        );
    }

    Vector& OnFireBullets3(
        regame::IReGameHook_CBaseEntity_FireBullets3* chain,
        CBaseEntity* pThis,
        Vector& vecSrc,
        Vector& vecDirShooting,
        float vecSpread,
        float flDistance,
        int iPenetration,
        int iBulletType,
        int iDamage,
        float flRangeModifier,
        entvars_t* pevAttacker,
        bool bPistol,
        int shared_rand
    )
    {
        GunsRecoil_FireBullets3(
            pThis,
            vecSrc,
            vecDirShooting,
            vecSpread,
            flDistance,
            iPenetration,
            iBulletType,
            iDamage,
            flRangeModifier,
            pevAttacker,
            bPistol,
            shared_rand
        );
        return chain->callNext(
            pThis,
            vecSrc,
            vecDirShooting,
            vecSpread,
            flDistance,
            iPenetration,
            iBulletType,
            iDamage,
            flRangeModifier,
            pevAttacker,
            bPistol,
            shared_rand
        );
    }
} // namespace

bool RegisterKickBackHook()
{
    auto* hookchains = ReGameContext::Hookchains();
    if (!hookchains)
    {
        LH_ERROR("[RegisterKickBackHook] hookchains is nullptr!");
        return false;
    }

    g_kickBack = hookchains->CBasePlayerWeapon_KickBack();

    if (!g_kickBack)
    {
        LH_ERROR("[RegisterKickBackHook] registry is nullptr!");
        return false;
    }

    g_kickBack->registerHook(
        OnKickBack,
        regame::HC_PRIORITY_DEFAULT
    );

    LH_INFO("[RegisterKickBackHook] hook registered!");

    return true;
}

void UnregisterKickBackHook()
{
    if (!g_kickBack)
        return;

    g_kickBack->unregisterHook(OnKickBack);

    g_kickBack = nullptr;

    LH_INFO("[UnregisterKickBackHook] hook unregistered");
}

bool RegisterFireBullets3Hook()
{
    auto* hookchains = ReGameContext::Hookchains();
    if (!hookchains)
    {
        LH_ERROR("[RegisterFireBullets3Hook] hookchains is nullptr!");
        return false;
    }

    g_fireBullets3 = hookchains->CBaseEntity_FireBullets3();
    if (!g_fireBullets3)
    {
        LH_ERROR("[RegisterFireBullets3Hook] registry is nullptr!");
        return false;
    }

    g_fireBullets3->registerHook(
        OnFireBullets3,
        regame::HC_PRIORITY_DEFAULT
    );

    LH_INFO("[RegisterFireBullets3Hook] hook registered!");

    return true;
}

void UnregisterFireBullets3Hook()
{
    if (!g_fireBullets3)
        return;

    g_fireBullets3->unregisterHook(OnFireBullets3);

    g_fireBullets3 = nullptr;

    LH_INFO("[UnregisterFireBullets3Hook] hook unregistered");
}
