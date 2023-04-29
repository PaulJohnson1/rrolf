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
        constexpr uint32_t kMaxPetals = 4;
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
    };

    static constexpr PetalData PETAL_DATA[PetalId::kMaxPetals] = {
        {PetalId::None, 0, 0},
        {PetalId::Basic, 10.0f, 10.0f, 50}, // for testing physcis *DO NOT FORGET TO CHANGE*
        {PetalId::Light, 5.0f, 7.0f, 50, 0, {1, 2, 2, 3, 3, 5, 5}},
        {PetalId::Stinger, 8.0f, 35.0f, 100, 10, {1, 1, 1, 1, 1, 3, 5}}
    };

    static MobData MOB_DATA[MobId::kMaxMobs] = {
        {MobId::BabyAnt, 14, 25, 10, {{1, LootTable(0.25)}, {2, LootTable(1)}}} // baby ant
    };

    // 0xffff2b75, 0xff2bffa3 for ultra and super
    static constexpr uint32_t RARITY_COLORS[RarityId::kMaxRarities] = {0xff7eef6d, 0xffffe65d, 0xff4d52e3, 0xff861fde, 0xffde1f1f, 0xff1fdbde, 0xffff2b75};
    static constexpr char const *RARITY_NAMES[RarityId::kMaxRarities] = {"Common", "Unusual", "Rare", "Epic", "Legendary", "Mythic", "Ultra"};

    static constexpr char const *MOB_NAMES[MobId::kMaxMobs] = {"Baby Ant"};
    static constexpr char const *PETAL_NAMES[PetalId::kMaxPetals] = {"", "Basic", "Light", "Stinger"};


    static constexpr float MOB_SCALE_FACTOR[RarityId::kMaxRarities] = {
        1,
        1.1,
        1.3,
        1.6,
        3.0,
        5.0,
        25.0
    };

    static constexpr float MOB_HEALTH_FACTOR[RarityId::kMaxRarities] = {
        1,
        1.6,
        2.5,
        4.0,
        25.0,
        50.0,
        1000.0
    };

    static constexpr float MOB_DAMAGE_FACTOR[RarityId::kMaxRarities] = {
        1,
        1.1,
        1.3,
        1.6,
        2.0,
        2.5,
        10.0
    };

    static constexpr float PETAL_HEALTH_FACTOR[RarityId::kMaxRarities] = {
        1,
        2,
        4,
        8,
        16,
        32,
        64
    };

    static constexpr float PETAL_DAMAGE_FACTOR[RarityId::kMaxRarities] = {
        1,
        2,
        4,
        8,
        16,
        32,
        64
    };
}
