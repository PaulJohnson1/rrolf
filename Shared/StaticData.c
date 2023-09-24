#include <Shared/StaticData.h>

#include <math.h>
#include <stdio.h>

#include <Shared/Utilities.h>

// clang-format off
struct rr_petal_data RR_PETAL_DATA[rr_petal_id_max] = {
    {rr_petal_id_no_petal, rr_rarity_id_common, 0.0f, 0.0f, 0.0f, 0, 0, {0, 0, 0, 0, 0, 0, 0}},
    {rr_petal_id_basic, rr_rarity_id_common, 10.0f, 10.0f, 0.0f, 50, 0, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_light, rr_rarity_id_common, 7.0f, 5.0f, 0.0f, 12, 0, {1, 2, 2, 3, 3, 5, 5}},
    {rr_petal_id_leaf, rr_rarity_id_common, 8.0f, 6.0f, 0.0f, 25, 0, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_stinger, rr_rarity_id_common, 35.0f, 2.0f, 10.0f, 87, 0, {1, 1, 1, 1, 1, 3, 5}},
    {rr_petal_id_missile, rr_rarity_id_common, 20.0f, 10.0f, 0.0f, 50, 12, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_faster, rr_rarity_id_common, 8.0f, 8.0f, 0.0f, 50, 0, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_web, rr_rarity_id_common, 5.0f, 10.0f, 0.0f, 75, 12, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_antennae, rr_rarity_id_common, 0.0f, 0.0f, 0.0f, 0, 0, {0, 0, 0, 0, 0, 0, 0}},
    {rr_petal_id_peas, rr_rarity_id_common, 10.0f, 5.0f, 8.0f, 12, 12, {4, 4, 4, 4, 4, 5, 5}},
    {rr_petal_id_rose, rr_rarity_id_common, 5.0f, 5.0f, 0.0f, 75, 25, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_iris, rr_rarity_id_common, 5.0f, 5.0f, 0.0f, 75, 0, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_grapes, rr_rarity_id_common, 2.0f, 5.0f, 8.0f, 12, 12, {4, 4, 4, 4, 4, 5, 5}},
};    

char const *RR_PETAL_NAMES[rr_petal_id_max] = {
    "Secret", "Basic", "Light", "Leaf", "Stinger", "Missile", "Faster",
    "Web", "Antennae", "Peas", "Rose","Iris","Grapes"};
char const *RR_PETAL_DESCRIPTIONS[rr_petal_id_max] = {
    0,
    "It's just a petal",
    "Low damage, but there's lots",
    "Heal you passively",
    "Ow",
    "Pew",
    "So light it makes your petals spin faster",
    "Spider",
    "Sense things from farther away",
    "4-5 in 1",
    "Heals you",
    "Poisonous",
    "4-5+poison in 1"
};

struct rr_mob_data RR_MOB_DATA[rr_mob_id_max] = {
    {rr_mob_id_baby_ant, rr_rarity_id_common, 10, 10, 14, {{rr_petal_id_light, 0.1},{rr_petal_id_leaf, 0.2}}},
    {rr_mob_id_worker_ant, rr_rarity_id_common, 10, 15, 16, {{rr_petal_id_light, 0.1}}},
    {rr_mob_id_soldier_ant, rr_rarity_id_common, 15, 20, 16, {{rr_petal_id_light, 0.15}}},
    {rr_mob_id_bee, rr_rarity_id_common, 10, 30, 25, {{rr_petal_id_stinger, 0.25},{rr_petal_id_light, 0.1}}},
    {rr_mob_id_hornet, rr_rarity_id_common, 40, 30, 25, {{rr_petal_id_antennae, 0.25},{rr_petal_id_missile, 0.2}}},
    {rr_mob_id_spider, rr_rarity_id_common, 25, 25, 15, {{rr_petal_id_faster, 0.25},{rr_petal_id_web, 0.2}, {rr_petal_id_iris, 0.1}}},
    {rr_mob_id_centipede, rr_rarity_id_common, 30, 10, 35, {{rr_petal_id_peas, 0.25},{rr_petal_id_leaf, 0.2}}},
    {rr_mob_id_ladybug, rr_rarity_id_common, 30, 10, 25, {{rr_petal_id_rose, 0.25},{rr_petal_id_light, 0.1}}},
    {rr_mob_id_evil_centipede, rr_rarity_id_common, 30, 20, 35, {{rr_petal_id_grapes, 0.25},{rr_petal_id_iris, 0.1}}}
};

char const *RR_MOB_NAMES[rr_mob_id_max] = {"Baby Ant","Worker Ant","Soldier Ant",
"Bee","Hornet","Spider","Centipede","Ladybug","Evil Centipede"};
// zeach's numbers from the pinned screenshot of the old scaling
struct rr_petal_rarity_scale RR_PETAL_RARITY_SCALE[rr_rarity_id_max] = {
    {1,   1},
    {1.5, 1.8},
    {2.4, 3.0},
    {3.5, 4.5},
    {5.6, 7.2},
    {8.0, 16.0},
    {15.0, 40.0},
};

struct rr_mob_rarity_scale RR_MOB_RARITY_SCALING[rr_rarity_id_max] = {
    {1.0, 1.0, 1.0},
    {2.5, 1.3, 1.2},
    {5.6, 1.6, 1.5}, 
    {15,  2.5, 1.8},
    {50,  4.0, 2.5},
    {100, 6.2, 4.0},
    {150, 12,  6.0},
};
// clang-format on

uint32_t RR_RARITY_COLORS[rr_rarity_id_max] = {
    0xff7eef6d, 0xffffe65d, 0xff4d52e3, 0xff861fde,
    0xffde1f1f, 0xff1fdbde, 0xffff2b75};
char const *RR_RARITY_NAMES[rr_rarity_id_max] = {
    "Common", "Uncommon", "Rare", "Epic", "Legendary", "Mythic", "Exotic"};

uint32_t RR_MOB_DIFFICULTY_COEFFICIENTS[rr_mob_id_max] = {2, 2, 3, 1,3,3,3,3};
double RR_HELL_CREEK_MOB_ID_RARITY_COEFFICIENTS[rr_mob_id_max] = {1,1,1,1,1,1,1,1};

double RR_OCEAN_MOB_ID_RARITY_COEFFICIENTS[rr_mob_id_max] = {0};
                                            
double RR_MOB_WAVE_RARITY_COEFFICIENTS[rr_rarity_id_ultra + 2] = {
    0, 1, 5, 8, 15, 30, 100, 500};

double RR_DROP_RARITY_COEFFICIENTS[rr_rarity_id_ultra + 2] = {
    0, 1, 12, 20, 25, 150, 250, 50};
double RR_MOB_LOOT_RARITY_COEFFICIENTS[rr_rarity_id_ultra + 1] = {
    3, 3, 5, 16, 20, 25, 50};

static void init_game_coefficients()
{
    double sum = 1;
    double sum2 = 1;
    for (uint64_t a = 1; a <= rr_rarity_id_ultra; ++a)
    {
        sum += (RR_DROP_RARITY_COEFFICIENTS[a + 1] =
                    RR_DROP_RARITY_COEFFICIENTS[a] /
                    RR_DROP_RARITY_COEFFICIENTS[a + 1]);
        sum2 += (RR_MOB_WAVE_RARITY_COEFFICIENTS[a + 1] =
                     RR_MOB_WAVE_RARITY_COEFFICIENTS[a] /
                     RR_MOB_WAVE_RARITY_COEFFICIENTS[a + 1]);
        RR_MOB_LOOT_RARITY_COEFFICIENTS[a] *=
            RR_MOB_LOOT_RARITY_COEFFICIENTS[a - 1];
    }
    for (uint64_t a = 1; a <= rr_rarity_id_ultra + 1; ++a)
    {
        RR_DROP_RARITY_COEFFICIENTS[a] = RR_DROP_RARITY_COEFFICIENTS[a] / sum +
                                         RR_DROP_RARITY_COEFFICIENTS[a - 1];
        RR_MOB_WAVE_RARITY_COEFFICIENTS[a] =
            RR_MOB_WAVE_RARITY_COEFFICIENTS[a] / sum2 +
            RR_MOB_WAVE_RARITY_COEFFICIENTS[a - 1];
    }
    RR_DROP_RARITY_COEFFICIENTS[rr_rarity_id_ultra + 1] = 1;
    for (uint64_t mob = 1; mob < rr_mob_id_max; ++mob)
    {
        RR_HELL_CREEK_MOB_ID_RARITY_COEFFICIENTS[mob] +=
            RR_HELL_CREEK_MOB_ID_RARITY_COEFFICIENTS[mob - 1];
        RR_OCEAN_MOB_ID_RARITY_COEFFICIENTS[mob] +=
            RR_OCEAN_MOB_ID_RARITY_COEFFICIENTS[mob - 1];
    }
    for (uint64_t mob = 0; mob < rr_mob_id_max; ++mob)
    {
        RR_HELL_CREEK_MOB_ID_RARITY_COEFFICIENTS[mob] /=
            RR_HELL_CREEK_MOB_ID_RARITY_COEFFICIENTS[rr_mob_id_max - 1];
        RR_OCEAN_MOB_ID_RARITY_COEFFICIENTS[mob] /=
            RR_OCEAN_MOB_ID_RARITY_COEFFICIENTS[rr_mob_id_max - 1];
    }
}

void rr_static_data_init()
{
    init_game_coefficients();
}

double xp_to_reach_level(uint32_t level)
{
    //xp it takes from level - 1 to level
    if (level <= 60)
        return level * pow(1.18, level);
    double base = level * pow(1.18, 60);
    for (uint32_t i = 60; i < level; ++i)
    {
        base *= rr_fclamp(1.18 - 0.01 * (i - 60), 1.1, 1.18);
    }
    return base;
}
