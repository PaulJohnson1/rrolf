#pragma once

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
        constexpr uint32_t kMaxRarities = 6;
    };

    namespace PetalId
    {
        constexpr uint32_t None = 0;
        constexpr uint32_t Basic = 1;
        constexpr uint32_t Light = 2;
        constexpr uint32_t kMaxPetals = 3;
    }

    struct MobData
    {
        uint32_t m_Id;
        float m_BaseSize;
        float m_BaseHealth;
        float m_BaseDamage;
    };

    struct PetalData
    {
        uint32_t m_Id;
        float m_BaseHealth;
        float m_BaseDamage;
        int32_t m_ReloadTicks;
        bool m_Clump = false;
        uint32_t m_Count[RarityId::kMaxRarities] = {1, 1, 1, 1, 1, 1};
    };

    static constexpr PetalData PETAL_DATA[PetalId::kMaxPetals] = {
        {PetalId::None, 0, 0, true},
        {PetalId::Basic, 10.0f, 10.0f, 50, true}, // for testing physcis *DO NOT FORGET TO CHANGE*
        {PetalId::Light, 7.0f, 5.0f, 50, false, {1, 2, 2, 3, 3, 5}}
    };

    static constexpr MobData MOB_DATA[MobId::kMaxMobs] = {
        {MobId::BabyAnt, 14, 25, 10} // baby ant
    };

    // 0xffff2b75, 0xff2bffa3 for ultra and super
    static constexpr uint32_t RARITY_COLORS[RarityId::kMaxRarities] = {0xff7eef6d, 0xffffe65d, 0xff4d52e3, 0xff861fde, 0xffde1f1f, 0xff1fdbde};
    static constexpr char const *RARITY_NAMES[RarityId::kMaxRarities] = {"Common", "Unusual", "Rare", "Epic", "Legendary", "Mythic"};

    static constexpr char const *MOB_NAMES[MobId::kMaxMobs] = {"Baby Ant"};


    static constexpr float MOB_SCALE_FACTOR[RarityId::kMaxRarities] = {
        1,
        1.1,
        1.3,
        1.6,
        3.0,
        5.0};

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
        2.5};
}
