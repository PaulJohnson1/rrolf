#include <Server/Waves.h>

#include <math.h>
#include <stdlib.h>

#include <Server/Simulation.h>
#include <Shared/StaticData.h>
#include <Shared/Utilities.h>

uint32_t get_spawn_rarity(float difficulty)
{
    if (difficulty < 1)
        difficulty = 1;
    double rarity_seed = rr_frand();
    uint32_t rarity_cap = rr_rarity_id_common + (difficulty + 7) / 8;
    if (rarity_cap > rr_rarity_id_ultimate)
        rarity_cap = rr_rarity_id_ultimate;
    uint32_t rarity = rarity_cap >= 2 ? rarity_cap - 2 : 0;
    for (; rarity < rarity_cap; ++rarity)
        if (pow(1 - (1 - RR_MOB_WAVE_RARITY_COEFFICIENTS[rarity + 1]) * 0.3,
                pow(1.5, difficulty)) >= rarity_seed)
            break;
    return rarity;
}

uint8_t get_spawn_id(uint8_t biome, struct rr_maze_grid *zone)
{
    double *table = biome == 0 ? RR_HELL_CREEK_MOB_ID_RARITY_COEFFICIENTS : RR_GARDEN_MOB_ID_RARITY_COEFFICIENTS;
    double seed = rr_frand();
    uint8_t id = 0;
    for (; id < rr_mob_id_max - 1; ++id)
            if (seed <= table[id])
                break;
    return id;
}

int should_spawn_at(uint8_t id, uint8_t rarity)
{
    return rarity >= RR_MOB_DATA[id].min_rarity && rarity <= RR_MOB_DATA[id].max_rarity;
}