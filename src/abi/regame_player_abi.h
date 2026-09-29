#pragma once 

#include <cstddef>

namespace regame
{
    constexpr std::size_t CBasePlayer_m_pActiveItem = 0x5E8;
    constexpr std::size_t CBasePlayerItem_m_iId     = 0xBC;

    inline void* GetActiveItem(void* player)
    {
        if (!player)
            return nullptr;

        return *reinterpret_cast<void**>(
            static_cast<std::byte*>(player) + CBasePlayer_m_pActiveItem
        );
    }

    inline int GetWeaponId(void* item)
    {
        if (!item)
            return 0;

        return *reinterpret_cast<int*>(
            static_cast<std::byte*>(item) + CBasePlayerItem_m_iId
        );
    }
}
