#include <Shared/StaticData.h>

struct rr_petal_data RR_PETAL_DATA[rr_petal_id_max] = {
    {rr_petal_id_no_petal, 0.0f,   0.0f,  0.0f,  0,   {}},
    {rr_petal_id_basic,    10.0f,  10.0f, 0.0f,  12,  {1, 1, 1, 1}},
    {rr_petal_id_light,    13.0f,  5.0f,  0.0f,  12,  {1, 2, 2, 3}},
    {rr_petal_id_stinger,  100.0f, 2.0f,  10.0f, 0, {1, 1, 1, 5}}
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