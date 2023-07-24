#include <Shared/StaticData.h>

#include <math.h>
#include <stdio.h>

// clang-format off
struct rr_petal_data RR_PETAL_DATA[rr_petal_id_max] = {
    {rr_petal_id_no_petal, rr_rarity_id_common, 0.0f, 0.0f, 0.0f, 0, 0, {0, 0, 0, 0, 0, 0, 0}},
    {rr_petal_id_basic, rr_rarity_id_common, 10.0f, 10.0f, 0.0f, 38, 0, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_light, rr_rarity_id_common, 12.0f, 5.0f, 0.0f, 16, 0, {1, 2, 2, 3, 3, 5, 5}},
    {rr_petal_id_rock, rr_rarity_id_common, 5.0f, 55.0f, 0.0f, 100, 0, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_stinger, rr_rarity_id_common, 35.0f, 5.0f, 10.0f, 125, 0, {1, 1, 1, 1, 1, 3, 5}},
    {rr_petal_id_faster, rr_rarity_id_rare, 7.0f, 5.0f, 15.0f, 20, 0, {1, 1, 1, 1, 1, 2, 2}},
    {rr_petal_id_missile, rr_rarity_id_rare, 25.0f, 5.0f, 15.0f, 68, 12, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_peas, rr_rarity_id_rare, 15.0f, 2.0f, 8.0f, 50, 12, {4, 4, 4, 4, 4, 4, 5}},
    {rr_petal_id_leaf, rr_rarity_id_unusual, 7.0f, 10.0f, 8.0f, 25, 0, {1, 1, 1, 1, 1, 2, 3}},
    {rr_petal_id_egg, rr_rarity_id_epic, 1.0f, 20.0f, 0.0f, 12, 125, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_magnet, rr_rarity_id_rare, 1.0f, 8.0f, 0.0f, 38, 0, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_uranium, rr_rarity_id_rare, 4.0f, 10.0f, 0.0f, 50, 0, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_speed, rr_rarity_id_common, 1.0f, 3.0f, 0.0f, 25, 0, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_azalea, rr_rarity_id_common, 5.0f, 10.0f, 0.0f, 88, 25, {1, 1, 1, 1, 1, 1, 1}}
};    

struct rr_mob_data RR_MOB_DATA[rr_mob_id_max] = {
    {rr_mob_id_triceratops, 75, 5, 30.0f, {}},
    {rr_mob_id_trex, 40, 20, 32.0f, {}},
    {rr_mob_id_fern, 10, 5, 32.0f, {}},
    {rr_mob_id_stump, 50, 5, 26.0f, {}},
    {rr_mob_id_spinosaurus_head, 25, 10, 10.0f, {}},
    {rr_mob_id_spinosaurus_body, 25, 10, 10.0f, {}},
    {rr_mob_id_pteranodon, 35, 40, 26.0f, {}},
    {rr_mob_id_dakotaraptor, 35, 30, 30.0f, {}}};

// zeach's numbers from the pinned screenshot of the old scaling
struct rr_petal_rarity_scale RR_PETAL_RARITY_SCALE[rr_rarity_id_max] = {
    {1,   1},
    {1.3, 1.5},
    {1.8, 2.2},
    {2.4, 2.9},
    {3.2, 3.6},
    {4.0, 9.0},
    {10,  25.0}
};

struct rr_mob_rarity_scale RR_MOB_RARITY_SCALING[rr_rarity_id_max] = {
    {1.0, 1.0, 1.0},
    {1.6, 1.1, 1.2},
    {2.5, 1.3, 1.6}, 
    {4,   1.6, 2.0},
    {25,  2,   3},
    {50,  2.5, 5},
    {200, 10,  8}};
// clang-format on

uint32_t RR_RARITY_COLORS[rr_rarity_id_max] = {
    0xff7eef6d, 0xffffe65d, 0xff4d52e3, 0xff861fde,
    0xffde1f1f, 0xff1fdbde, 0xffff2b75};
char const *RR_RARITY_NAMES[rr_rarity_id_max] = {
    "Common", "Uncommon", "Rare", "Epic", "Legendary", "Mythic", "Common"};
char const *RR_PETAL_NAMES[rr_petal_id_max] = {
    "Secret", "Basic", "Light", "Rock", "Stinger", "Faster",
    "Missile",    "Peas",  "Leaf",  "Egg",  "Magnet", "Uranium", "Speed", "Azalea"};
char const *RR_PETAL_DESCRIPTIONS[rr_petal_id_max] = {
    0,
    "It's just a petal",
    "No fee, I'm traveling light",
    "Dwayne",
    "Ow that hurts",
    "Gotta go fast",
    "ICBM approved",
    "Where are the zombies?",
    "Probably the most normal petal there is. Oh wait",
    "It's egg",
    "Increases loot pickup radius. Stacks because why not",
    "Does low damage to mobs in a large range. Does 2.5x damage to yourself",
    "Increases your movement speed. Does not stack",
    "Lazy dev got off his couch and added a heal petal. Check it out"
};
char const *RR_MOB_NAMES[rr_mob_id_max] = {
    "Triceratops", "T-Rex", "Fern", "Stump", "Spinosaurus",
    "Spinosaurus", "Pteranodon", "Dakotaraptor"};

double RR_DROP_RARITY_COEFFICIENTS[rr_rarity_id_max + 1] = {0,  1,  10,  12,
                                                            16, 25, 45, 5};
uint32_t RR_MOB_LOOT_RARITY_COEFFICIENTS[rr_rarity_id_max] = {3, 4, 5, 5,
                                                              5, 5, 7};

double RR_MOB_WAVE_RARITY_COEFFICIENTS[rr_rarity_id_max + 1] = {0,  1,  8,  10,
                                                                12, 15, 18, 25};

uint32_t RR_MOB_DIFFICULTY_COEFFICIENTS[rr_mob_id_max] = {15, 30, 1, 1,
                                                          1,  40, 25};
double RR_MOB_SPAWN_RARITY_COEFFICIENTS[rr_mob_id_max] = {1, 1, 1, 1, 1, 1, 1};

static void init_rarity_coefficients()
{
    double sum = 1;
    double sum2 = 1;
    for (uint64_t a = 1; a < rr_rarity_id_max; ++a)
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
    for (uint64_t a = 1; a <= rr_rarity_id_max; ++a)
    {
        RR_DROP_RARITY_COEFFICIENTS[a] = RR_DROP_RARITY_COEFFICIENTS[a] / sum +
                                         RR_DROP_RARITY_COEFFICIENTS[a - 1];
        RR_MOB_WAVE_RARITY_COEFFICIENTS[a] =
            RR_MOB_WAVE_RARITY_COEFFICIENTS[a] / sum2 +
            RR_MOB_WAVE_RARITY_COEFFICIENTS[a - 1];
    }
    RR_DROP_RARITY_COEFFICIENTS[rr_rarity_id_max] = 1;
}

static void init_loot_table(struct rr_loot_data *data, uint8_t id, float seed)
{
    printf("loot table with seed %f\n", seed);
    data->id = id;
    for (uint64_t mob = 0; mob < rr_rarity_id_max; ++mob)
    {
        uint64_t cap = mob;
        if (mob < rr_rarity_id_mythic)
            cap = mob;
        else
            cap = mob - 1;

        for (uint64_t drop = 0; drop <= cap + 1; ++drop)
        {
            double end =
                drop == cap + 1 ? 1 : RR_DROP_RARITY_COEFFICIENTS[drop];
            if (cap < RR_PETAL_DATA[id].min_rarity)
                end = 1;
            else if (drop < RR_PETAL_DATA[id].min_rarity)
                end = RR_DROP_RARITY_COEFFICIENTS[RR_PETAL_DATA[id].min_rarity];
            data->loot_table[mob][drop] =
                pow(1 - (1 - end) * seed, RR_MOB_LOOT_RARITY_COEFFICIENTS[mob]);
        }
    }
    printf("------------------------------------------\n");
}

static void init_loot_tables()
{
    init_loot_table(&RR_MOB_DATA[rr_mob_id_triceratops].loot[0],
                    rr_petal_id_light, 0.15);
    init_loot_table(&RR_MOB_DATA[rr_mob_id_triceratops].loot[1], rr_petal_id_faster,
                    0.05);
    init_loot_table(&RR_MOB_DATA[rr_mob_id_triceratops].loot[2], rr_petal_id_speed,
                    0.1);

    init_loot_table(&RR_MOB_DATA[rr_mob_id_trex].loot[0], rr_petal_id_rock,
                    0.25);
    init_loot_table(&RR_MOB_DATA[rr_mob_id_trex].loot[1], rr_petal_id_stinger,
                    0.10);

    init_loot_table(&RR_MOB_DATA[rr_mob_id_fern].loot[0],
                    rr_petal_id_azalea, 0.10);
    init_loot_table(&RR_MOB_DATA[rr_mob_id_fern].loot[1],
                    rr_petal_id_leaf, 0.25);
    
    init_loot_table(&RR_MOB_DATA[rr_mob_id_stump].loot[0], rr_petal_id_peas,
                    0.15);
    init_loot_table(&RR_MOB_DATA[rr_mob_id_stump].loot[1], rr_petal_id_egg,
                    0.015);

    init_loot_table(&RR_MOB_DATA[rr_mob_id_pteranodon].loot[0],
                    rr_petal_id_missile, 0.25);

    init_loot_table(&RR_MOB_DATA[rr_mob_id_dakotaraptor].loot[0],
                    rr_petal_id_uranium, 0.01);
    init_loot_table(&RR_MOB_DATA[rr_mob_id_dakotaraptor].loot[1],
                    rr_petal_id_magnet, 0.015);
}

void rr_static_data_init()
{
    init_rarity_coefficients();
    init_loot_tables();
}
