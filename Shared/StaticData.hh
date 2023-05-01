#pragma once

#include <cmath>
#include <cstdint>
#include <vector>

namespace app
{
    // fake enum class (less type casting)
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
        constexpr uint32_t Ultra = 6;
        constexpr uint32_t kMaxRarities = 7;
    };

    namespace PetalId
    {
        constexpr uint32_t None = 0;
        constexpr uint32_t Basic = 1;
        constexpr uint32_t Light = 2;
        constexpr uint32_t Stinger = 3;
        constexpr uint32_t Missile = 4;
        constexpr uint32_t kMaxPetals = 5;
    };

    std::vector<std::vector<float>> LootTable(float);
    
    struct LootInstance
    {
        uint32_t m_Id;
        std::vector<std::vector<float>> m_Table;
    };

    struct MobData
    {
        uint32_t m_Id;
        float m_BaseSize;
        float m_BaseHealth;
        float m_BaseDamage;
        std::vector<LootInstance> m_Loot;
    };

    struct PetalData
    {
        uint32_t m_Id;
        float m_BaseHealth;
        float m_BaseDamage;
        int32_t m_ReloadTicks;
        float m_ClumpRadius = 0; //0 = no clump
        uint32_t m_Count[RarityId::kMaxRarities] = {1, 1, 1, 1, 1, 1, 1};
        uint32_t m_ShootDelay = 0;
    };

    extern PetalData PETAL_DATA[PetalId::kMaxPetals];

    extern MobData MOB_DATA[MobId::kMaxMobs];

    // 0xffff2b75, 0xff2bffa3 for ultra and super
    extern uint32_t RARITY_COLORS[RarityId::kMaxRarities];
    extern char const *RARITY_NAMES[RarityId::kMaxRarities];

    extern char const *MOB_NAMES[MobId::kMaxMobs];
    extern char const *PETAL_NAMES[PetalId::kMaxPetals];


    extern float MOB_SCALE_FACTOR[RarityId::kMaxRarities];

    extern float MOB_HEALTH_FACTOR[RarityId::kMaxRarities];

    extern float MOB_DAMAGE_FACTOR[RarityId::kMaxRarities];

    extern float PETAL_HEALTH_FACTOR[RarityId::kMaxRarities];

    extern float PETAL_DAMAGE_FACTOR[RarityId::kMaxRarities];
}
