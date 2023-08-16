#include <Server/Waves.h>

#include <math.h>
#include <stdlib.h>

#include <Shared/StaticData.h>
#include <Shared/Utilities.h>

uint32_t get_points_from_wave(uint32_t wave, uint32_t player_count)
{
    return 20 + (wave - 1) * (5 + 12 * player_count);
}

uint8_t get_rarity_from_wave(uint32_t wave)
{
    double rarity_seed = rr_frand();
    uint8_t rarity_cap = rr_rarity_id_rare + ((wave - 1) / 6);
    if (rarity_cap > rr_rarity_id_ultra)
        rarity_cap = rr_rarity_id_ultra;
    uint8_t rarity = 0;
    for (; rarity < rarity_cap; ++rarity)
        if (pow(1 - (1 - RR_MOB_WAVE_RARITY_COEFFICIENTS[rarity + 1]) * 0.4,
                pow(1.4, wave)) > rarity_seed)
            return rarity;
    return rarity;
}

uint8_t get_id_from_wave(uint32_t wave, uint8_t special_wave_id)
{
    double seed = rr_frand();
    if (special_wave_id == 0)
    {
        for (uint8_t id = 0; id < rr_mob_id_max - 1; ++id)
            if (seed < RR_MOB_ID_RARITY_COEFFICIENTS[id])
                return id;
        return rr_mob_id_max - 1;
    }
    else if (special_wave_id == 1)
    {
        if (rr_frand() > 0.25)
            return rr_mob_id_pachycephalosaurus;
        else
            return rr_mob_id_ornithomimus;
    }
    else if (special_wave_id == 2)
        return rr_mob_id_triceratops;
    else if (special_wave_id == 3)
    {
        if (rr_frand() > 0.025)
            return rr_mob_id_pteranodon;
        else
            return rr_mob_id_meteor;
    }
    else if (special_wave_id == 4)
    {
        if (rr_frand() > 0.75)
            return rr_mob_id_fern;
        else
            return rr_mob_id_dakotaraptor;
    }
    else
    {
        if (rr_frand() > 0.25)
            return rr_mob_id_ankylosaurus;
        else
            return rr_mob_id_quetzalcoatlus;
    }
}

int should_spawn_at(uint32_t wave, uint8_t id, uint8_t rarity)
{
    if (id == rr_mob_id_trex && rarity < rr_rarity_id_unusual)
        return 0;
    if (id == rr_mob_id_dakotaraptor && rarity < rr_rarity_id_epic)
        return 0;
    if (id == rr_mob_id_triceratops && rarity < rr_rarity_id_unusual)
        return 0;
    if (id == rr_mob_id_meteor && rarity < rr_rarity_id_rare)
        return 0;
    if (id == rr_mob_id_quetzalcoatlus && rarity < rr_rarity_id_rare)
        return 0;
    return 1;
}