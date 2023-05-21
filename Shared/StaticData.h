#pragma once

#include <stdint.h>

enum rr_rarities
{
    common = 0,
    unusual = 1,
    rare = 2,
    epic = 3
};

enum rr_petal_id
{
    no_petal = 0,
    basic = 1,
    light = 2,
    max_petals = 3
};

struct rr_petal_data
{
    uint8_t id;
    float health;
    float damage;
    uint32_t cooldown;
};

void rr_set_petal_data(uint32_t, float, float, uint32_t);
extern struct rr_petal_data PETAL_DATA[max_petals];