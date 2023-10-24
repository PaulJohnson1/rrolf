#include <Server/Waves.h>

#include <math.h>
#include <stdlib.h>

#include <Server/Simulation.h>
#include <Shared/StaticData.h>
#include <Shared/Utilities.h>

uint32_t get_spawn_rarity(float difficulty)
{
    double rarity_seed = rr_frand();
    uint32_t rarity_cap = rr_rarity_id_unusual + (difficulty - 1) / 8;
    if (rarity_cap > rr_rarity_id_ultra)
        rarity_cap = rr_rarity_id_ultra;
    uint8_t rarity = 0;
    for (; rarity < rarity_cap; ++rarity)
        if (pow(1 - (1 - RR_MOB_WAVE_RARITY_COEFFICIENTS[rarity + 1]) * 0.3,
                pow(1.45, difficulty)) >= rarity_seed)
            return rarity;
    return rarity;
}

float get_spawn_time(struct rr_maze_grid *grid)
{
    return ((float) grid->max_points) / (grid->max_points - grid->grid_points) * (12 - grid->player_count) * 22.5;
}

uint8_t get_spawn_id(uint8_t biome, struct rr_maze_grid *zone)
{
    double *table = biome == 0 ? RR_HELL_CREEK_MOB_ID_RARITY_COEFFICIENTS : RR_GARDEN_MOB_ID_RARITY_COEFFICIENTS;
    double seed = rr_frand();
    for (uint8_t id = 0; id < rr_mob_id_max - 1; ++id)
            if (seed <= table[id])
                return id;
    return rr_mob_id_max - 1;
}

int should_spawn_at(uint8_t id, uint8_t rarity)
{
    return rarity >= RR_MOB_DATA[id].min_rarity;
}