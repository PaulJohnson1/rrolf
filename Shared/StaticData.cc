#include <Shared/StaticData.hh>

#include <cstdint>
#include <cmath>

namespace app
{
    std::vector<std::vector<float>> LootTable(float seed)
    {
        double const mobS[RarityId::kMaxRarities] = { 60000,15000,2500,100,5,0.1 };
        double const dropS[RarityId::kMaxRarities+1] = { 0,0.6932697314296992,0.9705776240015788,0.9983084132587667,0.9999722606141981,0.9999999914034552,1 };
        std::vector<std::vector<float>> table(RarityId::kMaxRarities, std::vector<float>(RarityId::kMaxRarities + 1));
        for (uint32_t mob = 0; mob < RarityId::kMaxRarities; ++mob) {
            uint32_t cap = mob != 0 ? mob: 1;
            for (uint32_t drop = 0; drop <= cap; ++drop) {
                double start = dropS[drop], end = dropS[drop+1];
                if (drop == cap) end = 1;
                float ret1 = std::pow(seed*start+(1-seed),300000/mobS[mob]);
                float ret2 = std::pow(seed*end+(1-seed),300000/mobS[mob]);
                table[mob][drop] = ret2-ret1;
            }
        }
        return table;
    };
}