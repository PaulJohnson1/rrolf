#include <Server/Waves.h>

#include <math.h>
#include <stdlib.h>

#include <Shared/StaticData.h>
#include <Shared/Utilities.h>

uint8_t get_rarity_from_wave(uint32_t wave)
{
    float rarity_seed = rr_frand();
    uint8_t rarity_cap = rr_rarity_id_rare + ((wave - 1) / 4);
    if (rarity_cap > rr_rarity_id_ultra)
        rarity_cap = rr_rarity_id_max;
    uint8_t rarity = 0;
    for (; rarity < rarity_cap; ++rarity)
        if (pow(1 - (1 - RR_MOB_WAVE_RARITY_COEFFICIENTS[rarity + 1]) * 0.4, pow(1.3, wave)) >
            rarity_seed)
            break;
    return rarity;
}

uint8_t get_id_from_wave(uint32_t wave)
{
    uint8_t id = rand() % rr_mob_id_max;

    // pick another id since centipedes (spinosaurus doesn't work right now)
    if (id == rr_mob_id_spinosaurus_body)
        id = get_id_from_wave(wave);
    if (id == rr_mob_id_spinosaurus_head)
        id = get_id_from_wave(wave);
    if (id == rr_mob_id_stump && rand() % 4 != 0)
        id = get_id_from_wave(wave);
    if (id == rr_mob_id_fern && rand() % 5 != 0)
        id = get_id_from_wave(wave);

    return id;
}

int should_spawn_at(uint32_t wave, uint8_t id, uint8_t rarity)
{
    if (id == rr_mob_id_trex && rarity < rr_rarity_id_rare)
        return 0;
    if (id == rr_mob_id_pteranodon && rarity < rr_rarity_id_epic)
        return 0;
    if (id == rr_mob_id_dakotaraptor && rarity < rr_rarity_id_legendary)
        return 0;
    if (id == rr_mob_id_triceratops && rarity < rr_rarity_id_unusual)
        return 0;
    return 1;
}