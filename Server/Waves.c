#include <Server/Waves.h>

#include <math.h>
#include <stdlib.h>

#include <Server/Simulation.h>
#include <Shared/StaticData.h>
#include <Shared/Utilities.h>

uint32_t get_spawn_rarity(float seed)
{
    double rarity_seed = rr_frand();
    uint32_t rarity_cap = rr_rarity_id_rare + seed / 5;
    if (rarity_cap > rr_rarity_id_ultra)
        rarity_cap = rr_rarity_id_ultra;
    uint8_t rarity = 0;
    for (; rarity < rarity_cap; ++rarity)
        if (pow(1 - (1 - RR_MOB_WAVE_RARITY_COEFFICIENTS[rarity + 1]) * 0.3,
                pow(1.4, seed)) >= rarity_seed)
            return rarity;
    return rarity;
}

uint8_t get_spawn_id(uint8_t biome, struct rr_maze_grid *zone)
{
    double *table = biome == 0 ? RR_HELL_CREEK_MOB_ID_RARITY_COEFFICIENTS : RR_OCEAN_MOB_ID_RARITY_COEFFICIENTS;
    double seed = rr_frand();
    for (uint8_t id = 0; id < rr_mob_id_max - 1; ++id)
            if (seed <= table[id])
                return id;
    return rr_mob_id_max - 1;
}

int should_spawn_at(uint8_t id, uint8_t rarity)
{
    if (RR_MOB_DATA[id].min_rarity > rarity)
        return 0;
    return 1;
}