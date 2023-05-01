#include <Shared/StaticData.hh>

#include <cstdint>
#include <cmath>

namespace app
{
    std::vector<std::vector<float>> LootTable(float seed)
    {
        double const mobS[RarityId::kMaxRarities] = { 5, 20, 120, 3000, 60000, 3000000, 10000000 };
        double const dropS[RarityId::kMaxRarities+1] = { 0, 3, 5, 8, 10, 12, 15, INFINITY };
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