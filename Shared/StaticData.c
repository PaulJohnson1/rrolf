#include <Shared/StaticData.h>

#include <math.h>
#include <stdio.h>

struct rr_petal_data RR_PETAL_DATA[rr_petal_id_max] = {
    {rr_petal_id_no_petal, rr_rarity_id_common, 0.0f, 0.0f, 0.0f, 0, {0, 0, 0, 0, 0, 0, 0}},
    {rr_petal_id_basic, rr_rarity_id_common, 10.0f, 10.0f, 0.0f, 38, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_light, rr_rarity_id_common, 7.0f, 5.0f, 0.0f, 16, {1, 2, 2, 3, 3, 5, 5}},
    {rr_petal_id_rock, rr_rarity_id_unusual, 5.0f, 80.0f, 0.0f, 100, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_stinger, rr_rarity_id_unusual, 35.0f, 2.0f, 10.0f, 138, {1, 1, 1, 1, 1, 3, 5}},
    {rr_petal_id_faster, rr_rarity_id_rare, 7.0f, 5.0f, 15.0f, 20, {1, 1, 1, 1, 1, 2, 2}},
    {rr_petal_id_missile, rr_rarity_id_rare, 20.0f, 10.0f, 15.0f, 100, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_peas, rr_rarity_id_rare, 10.0f, 5.0f, 8.0f, 38, {4, 4, 4, 4, 4, 4, 5}},
    {rr_petal_id_leaf, rr_rarity_id_unusual, 7.0f, 7.0f, 8.0f, 25, {1, 1, 1, 1, 1, 2, 3}},
    {rr_petal_id_egg, rr_rarity_id_epic, 1.0f, 25.0f, 0.0f, 125, {4, 4, 4, 4, 4, 4, 5}},
    {rr_petal_id_magnet, rr_rarity_id_epic, 2.0f, 2.0f, 0.0f, 6, {1, 1, 1, 1, 1, 1, 1}}
};    

struct rr_mob_data RR_MOB_DATA[rr_mob_id_max] = {
    {rr_mob_id_triceratops, 15, 10, 30.0f, {}},
    {rr_mob_id_trex, 35, 15, 32.0f, {}},
    {rr_mob_id_stump, 50, 10, 26.0f, {}},
    {rr_mob_id_spinosaurus_head, 25, 10, 10.0f, {}},
    {rr_mob_id_spinosaurus_body, 25, 10, 10.0f, {}},
    {rr_mob_id_pteranodon, 30, 30, 26.0f, {}},
    {rr_mob_id_dakotaraptor, 30, 25, 30.0f, {}}};

float RR_PETAL_RARITY_SCALE[rr_rarity_id_max] = {1, 1.5, 2.5, 4, 7.5, 18, 40};

struct rr_mob_rarity_scale RR_MOB_RARITY_SCALING[rr_rarity_id_max] = {
    {1.0, 1.0, 1.0}, {2.5, 1.2, 1.2}, {7.5, 1.5, 1.6}, {25.0, 1.8, 2.0},
    {75, 2.2, 2.5}, {200, 2.8, 4}, {1000, 4.0, 6}};

uint32_t RR_RARITY_COLORS[rr_rarity_id_max] = {
    0xff7eef6d, 0xffffe65d, 0xff4d52e3, 0xff861fde,
    0xffde1f1f, 0xff1fdbde, 0xffff2b75};
char const *RR_RARITY_NAMES[rr_rarity_id_max] = {
    "Common", "Unusual", "Rare", "Epic", "Legendary", "Mythic", "Ultra"};
char const *RR_PETAL_NAMES[rr_petal_id_max] = {
    "emscripten", "Basic",   "Light", "Rock", "Stinger",
    "Faster", "Missile", "Peas",  "Leaf", "Egg", "Magnet.tm"};
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
    "Trademarked by the lobsters"};
char const *RR_MOB_NAMES[rr_mob_id_max] = {
    "Triceratops", "T-Rex",      "Stump",       "Spinosaurus",
    "Spinosaurus", "Pteranodon", "Dakotaraptor"};

double RR_DROP_RARITY_COEFFICIENTS[rr_rarity_id_max + 1] = {0,  1,  8,  12,
                                                            15, 25, 50, 5};
uint32_t RR_MOB_RARITY_COEFFICIENTS[rr_rarity_id_max] = {3, 4, 5, 5, 5, 5, 7};

static void init_rarity_coefficients()
{
    double sum = 1;
    for (uint64_t a = 1; a < rr_rarity_id_max; ++a)
    {
        sum += (RR_DROP_RARITY_COEFFICIENTS[a + 1] =
                    RR_DROP_RARITY_COEFFICIENTS[a] /
                    RR_DROP_RARITY_COEFFICIENTS[a + 1]);
        RR_MOB_RARITY_COEFFICIENTS[a] *= RR_MOB_RARITY_COEFFICIENTS[a - 1];
    }
    for (uint64_t a = 1; a <= rr_rarity_id_max; ++a)
        RR_DROP_RARITY_COEFFICIENTS[a] = RR_DROP_RARITY_COEFFICIENTS[a] / sum +
                                         RR_DROP_RARITY_COEFFICIENTS[a - 1];
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

        data->loot_table[mob][0] =
            pow(1 - seed, RR_MOB_RARITY_COEFFICIENTS[mob]);
        for (uint64_t drop = 0; drop <= cap; ++drop)
        {
            double start = RR_DROP_RARITY_COEFFICIENTS[drop];
            double end =
                drop == cap ? 1 : RR_DROP_RARITY_COEFFICIENTS[drop + 1];
            data->loot_table[mob][drop + 1] =
                pow(1 - (1 - end) * seed, RR_MOB_RARITY_COEFFICIENTS[mob]);
            printf("%f ", data->loot_table[mob][drop + 1] -
                              data->loot_table[mob][drop]);
        }
        for (uint64_t drop = 0; drop < RR_PETAL_DATA[id].min_rarity; ++drop)
            data->loot_table[mob][drop] = data->loot_table[mob][RR_PETAL_DATA[id].min_rarity];
    }
    printf("------------------------------------------\n");
}

static void init_loot_tables()
{
    init_loot_table(&RR_MOB_DATA[rr_mob_id_triceratops].loot[0],
                    rr_petal_id_light, 0.05);
    init_loot_table(&RR_MOB_DATA[rr_mob_id_triceratops].loot[1],
                    rr_petal_id_leaf, 0.15);

    init_loot_table(&RR_MOB_DATA[rr_mob_id_trex].loot[0], rr_petal_id_light,
                    0.25);

    init_loot_table(&RR_MOB_DATA[rr_mob_id_stump].loot[0], rr_petal_id_rock,
                    0.15);

    init_loot_table(&RR_MOB_DATA[rr_mob_id_pteranodon].loot[0],
                    rr_petal_id_missile, 0.25);
    init_loot_table(&RR_MOB_DATA[rr_mob_id_pteranodon].loot[1],
                    rr_petal_id_stinger, 0.1);
    
    init_loot_table(&RR_MOB_DATA[rr_mob_id_dakotaraptor].loot[0],
                    rr_petal_id_leaf, 0.2);
    init_loot_table(&RR_MOB_DATA[rr_mob_id_dakotaraptor].loot[1],
                    rr_petal_id_faster, 0.1);
    init_loot_table(&RR_MOB_DATA[rr_mob_id_dakotaraptor].loot[2],
                    rr_petal_id_egg, 0.01);
    init_loot_table(&RR_MOB_DATA[rr_mob_id_dakotaraptor].loot[3],
                    rr_petal_id_magnet, 0.02);
}

void rr_static_data_init()
{
    init_rarity_coefficients();
    init_loot_tables();
}
