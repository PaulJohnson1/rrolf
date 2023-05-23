#include <Shared/StaticData.h>

struct rr_petal_data PETAL_DATA[rr_petal_id_max] = {
    {rr_petal_id_no_petal, 0, 0, 0},
    {rr_petal_id_basic, 10, 10, 12},
    {rr_petal_id_light, 7, 5, 12}
};

float rr_mob_rarity_scaling[rr_rarity_max] = {
    1,
    1.1,
    1.3,
    1.6
};
