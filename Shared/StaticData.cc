#include <Shared/StaticData.hh>

#include <cstdint>
#include <cmath>

namespace app
{
    PetalData PETAL_DATA[PetalId::kMaxPetals] = {
        PetalData(PetalId::None),
        PetalData(PetalId::Basic).BaseStats(10.0f, 10.0f, 50), // for testing physcis *DO NOT FORGET TO CHANGE*
        PetalData(PetalId::Light).BaseStats(5.0f, 7.0f, 25).Count({1, 2, 2, 3, 3, 5, 5, 7}),
        PetalData(PetalId::Stinger).BaseStats(8.0f, 35.0f, 100).ClumpRadius(10.0f).Count({1, 1, 1, 1, 2, 3, 5, 5}),
        PetalData(PetalId::Missile).BaseStats(8.0f, 40.0f, 100).ShootDelay(13),
        PetalData(PetalId::Pollen).BaseStats(5.0f, 7.0f, 25).Count({1, 2, 2, 3, 3, 5, 5, 7}).ShootDelay(13),
        PetalData(PetalId::Rose).BaseStats(100.0f, 100.0f, 100).Heal(100.0f).ShootDelay(13)
    };

    MobData MOB_DATA[MobId::kMaxMobs] = {
        {MobId::BabyAnt, 14, 25, 10, {{1, LootTable(0.25)}, {2, LootTable(1)}}} // baby ant
    };

    uint32_t RARITY_COLORS[RarityId::kMaxRarities] = {0xff7eef6d, 0xffffe65d, 0xff4d52e3, 0xff861fde, 0xffde1f1f, 0xff1fdbde, 0xffff2b75, 0xff2bffa3};
    char const *RARITY_NAMES[RarityId::kMaxRarities] = {"Common", "Unusual", "Rare", "Epic", "Legendary", "Mythic", "Ultra", "Super"};

    char const *MOB_NAMES[MobId::kMaxMobs] = {"Baby Ant"};
    char const *PETAL_NAMES[PetalId::kMaxPetals] = {"", "Basic", "Light", "Stinger", "Missile", "Pollen", "Rose"};
    float MOB_SCALE_FACTOR[RarityId::kMaxRarities] = {
        1,
        1.1,
        1.3,
        1.6,
        3.0,
        5.0,
        20.0,
        30.0
    };

    float MOB_HEALTH_FACTOR[RarityId::kMaxRarities] = {
        1,
        1.6,
        2.5,
        4.0,
        25.0,
        50.0,
        1000.0,
        5000.0
    };

    float MOB_DAMAGE_FACTOR[RarityId::kMaxRarities] = {
        1,
        1.1,
        1.3,
        1.6,
        2.0,
        2.5,
        10.0,
        50.0
    };

    float PETAL_HEALTH_FACTOR[RarityId::kMaxRarities] = {
        1,
        2,
        4,
        8,
        16,
        32,
        64,
        128
    };

    float PETAL_DAMAGE_FACTOR[RarityId::kMaxRarities] = {
        1,
        2,
        4,
        8,
        16,
        32,
        64,
        128
    };

    std::vector<std::vector<float>> LootTable(float seed)
    {
        double const mobS[RarityId::kMaxRarities] = { 5, 20, 120, 3000, 60000, 3000000, 10000000, 300000000 };
        double const dropS[RarityId::kMaxRarities+1] = { 0, 3, 5, 8, 12, 15, 20, 35, 1e10 };
        std::vector<std::vector<float>> table(RarityId::kMaxRarities, std::vector<float>(RarityId::kMaxRarities + 1));
        for (uint32_t mob = 0; mob < RarityId::kMaxRarities; ++mob) {
            uint32_t cap = mob != 0 ? mob: 1;
            for (uint32_t drop = 0; drop <= cap; ++drop) {
                double start = std::exp(-dropS[drop]), end = std::exp(-dropS[drop+1]);
                if (drop == cap) end = 0;
                float ret1 = std::pow(1-seed*start,mobS[mob]);
                float ret2 = std::pow(1-seed*end,mobS[mob]);
                table[mob][drop] = ret2-ret1;
            }
        }
        return table;
    };
}