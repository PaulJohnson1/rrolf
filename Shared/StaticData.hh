#pragma once

namespace app
{
    // fake enum class
    namespace MobId
    {
        constexpr uint32_t BabyAnt = 0;
        constexpr uint32_t kMaxMobs = 1;
    };

    namespace RarityId
    {
        constexpr uint32_t Common = 0;
        constexpr uint32_t Unusual = 1;
        constexpr uint32_t Rare = 2;
        constexpr uint32_t Epic = 3;
        constexpr uint32_t Legendary = 4;
        constexpr uint32_t Mythic = 5;
        constexpr uint32_t kMaxRarities = 6;
    };
    
    struct MobData
    {
        // if we see -1 in the debugger something went wrong
        float m_BaseSize = -1.0f;
        float m_BaseHealth = -1.0f;
        float m_BaseDamage = -1.0f;
    };

    static constexpr MobData MOB_DATA[MobId::kMaxMobs] = {
        MobData{14, 10, 10} // baby ant
    };

    static constexpr float MOB_SCALE_FACTOR[RarityId::kMaxRarities] = {
        1,
        1.1,
        1.3,
        1.6,
        3.0,
        5.0
    };

    static constexpr float MOB_HEALTH_FACTOR[RarityId::kMaxRarities] = {
        1,
        1.6,
        2.5,
        4.0,
        25.0,
        50.0,
    };

    static constexpr float MOB_DAMAGE_FACTOR[RarityId::kMaxRarities] = {
        1,
        1.1,
        1.3,
        1.6,
        2.0,
        2.5
    };
}
