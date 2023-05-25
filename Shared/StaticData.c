#include <Shared/StaticData.h>

struct rr_petal_data RR_PETAL_DATA[rr_petal_id_max] = {
    {rr_petal_id_no_petal, 0, 0, 0, 0.0f, {}},
    {rr_petal_id_basic, 10, 10, 12, 0.0f, {1, 1, 1, 1}},
    {rr_petal_id_light, 7, 5, 12, 0.0f, {1, 2, 2, 3}},
    {rr_petal_id_stinger, 35, 8, 100, 10.0f, {1, 1, 1, 3}}
};

struct rr_mob_data RR_MOB_DATA[rr_mob_id_max] = {
    {rr_mob_id_baby_ant, 1, 1, 17.5}
};

struct rr_mob_rarity_scale RR_MOB_RARITY_SCALING[rr_rarity_max] = {
    {1, 1, 1},
    {10, 1, 1.1},
    {100, 1, 1.3},
    {1000, 1, 1.6}
};