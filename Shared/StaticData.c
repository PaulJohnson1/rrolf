#include <Shared/StaticData.h>

#include <math.h>
#include <stdio.h>

struct rr_petal_data RR_PETAL_DATA[rr_petal_id_max] = {
    {rr_petal_id_no_petal, 0.0f, 0.0f, 0.0f, 0, {0, 0, 0, 0, 0, 0, 0}},
    {rr_petal_id_basic, 10.0f, 10.0f, 0.0f, 37, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_light, 7.0f, 5.0f, 0.0f, 12, {1, 2, 2, 3, 3, 5, 5}},
    {rr_petal_id_rock, 5.0f, 80.0f, 0.0f, 100, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_stinger, 35.0f, 2.0f, 10.0f, 113, {1, 1, 1, 1, 1, 3, 5}},
    {rr_petal_id_faster, 7.0f, 5.0f, 15.0f, 20, {1, 1, 1, 1, 1, 2, 2}},
    {rr_petal_id_missile, 20.0f, 10.0f, 15.0f, 75, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_peas, 10.0f, 5.0f, 8.0f, 25, {4, 4, 4, 4, 4, 4, 5}},
    {rr_petal_id_leaf, 7.0f, 7.0f, 8.0f, 25, {1, 1, 1, 1, 1, 2, 3}},
    {rr_petal_id_egg, 1.0f, 25.0f, 0.0f, 100, {4, 4, 4, 4, 4, 4, 5}}};

struct rr_mob_data RR_MOB_DATA[rr_mob_id_max] = {
    {rr_mob_id_triceratops, 25, 10, 30.0f, {}},
    {rr_mob_id_trex, 62.5, 10, 32.0f, {}},
    {rr_mob_id_stump, 100, 10, 26.0f, {}},
    {rr_mob_id_spinosaurus_head, 25, 10, 10.0f, {}},
    {rr_mob_id_spinosaurus_body, 25, 10, 10.0f, {}},
    {rr_mob_id_pteranodon, 37.5, 50, 26.0f, {}},
    {rr_mob_id_dakotaraptor, 35, 40, 30.0f, {}}};

float RR_PETAL_RARITY_SCALE[rr_rarity_id_max] = {1, 2, 4, 8, 16, 48, 196};

struct rr_mob_rarity_scale RR_MOB_RARITY_SCALING[rr_rarity_id_max] = {
    {1.0, 1.0, 1.0}, {2.5, 1.6, 1.2}, {8.0, 3.0, 1.6}, {25.0, 7.5, 2.0},
    {75, 20.0, 2.5}, {250, 50.0, 4},  {1000, 200, 6}};

uint32_t RR_RARITY_COLORS[rr_rarity_id_max] = {
    0xff7eef6d, 0xffffe65d, 0xff4d52e3, 0xff861fde,
    0xffde1f1f, 0xff1fdbde, 0xffff2b75};
char const *RR_RARITY_NAMES[rr_rarity_id_max] = {
    "Common", "Unusual", "Rare", "Epic", "Legendary", "Mythic", "Ultra"};
char const *RR_PETAL_NAMES[rr_petal_id_max] = {
    0,        "Basic",   "Light", "Rock", "Stinger",
    "Faster", "Missile", "Peas",  "Leaf", "Egg"};
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
    "It's egg"};
char const *RR_MOB_NAMES[rr_mob_id_max] = {
    "Triceratops", "T-Rex",      "Stump",       "Spinosaurus",
    "Spinosaurus", "Pteranodon", "Dakotaraptor"};

double RR_DROP_RARITY_COEFFICIENTS[rr_rarity_id_max + 1] = {0,  1,  5,  10,
                                                            15, 20, 50, 5};
uint32_t RR_MOB_RARITY_COEFFICIENTS[rr_rarity_id_max] = {3, 5, 5, 5, 5, 7, 7};

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
        if (mob == 0)
            cap = 0;
        else if (mob <= rr_rarity_id_mythic)
            cap = mob - 1;
        else
            cap = rr_rarity_id_ultra;
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
        puts("");
    }
    printf("------------------------------------------\n");
}

static void init_loot_tables()
{
    init_loot_table(&RR_MOB_DATA[rr_mob_id_triceratops].loot[0],
                    rr_petal_id_light, 0.25);
    init_loot_table(&RR_MOB_DATA[rr_mob_id_triceratops].loot[1],
                    rr_petal_id_leaf, 0.25);

    init_loot_table(&RR_MOB_DATA[rr_mob_id_trex].loot[0], rr_petal_id_light,
                    0.25);

    init_loot_table(&RR_MOB_DATA[rr_mob_id_stump].loot[0], rr_petal_id_rock,
                    0.25);

    init_loot_table(&RR_MOB_DATA[rr_mob_id_spinosaurus_head].loot[0],
                    rr_petal_id_peas, 0.1);
    init_loot_table(&RR_MOB_DATA[rr_mob_id_spinosaurus_head].loot[1],
                    rr_petal_id_light, 0.05);
    init_loot_table(&RR_MOB_DATA[rr_mob_id_spinosaurus_head].loot[2],
                    rr_petal_id_leaf, 0.05);

    init_loot_table(&RR_MOB_DATA[rr_mob_id_spinosaurus_body].loot[0],
                    rr_petal_id_peas, 0.1);
    init_loot_table(&RR_MOB_DATA[rr_mob_id_spinosaurus_body].loot[1],
                    rr_petal_id_leaf, 0.05);

    init_loot_table(&RR_MOB_DATA[rr_mob_id_pteranodon].loot[0],
                    rr_petal_id_missile, 1);

    init_loot_table(&RR_MOB_DATA[rr_mob_id_dakotaraptor].loot[0],
                    rr_petal_id_stinger, 0.0005);
    init_loot_table(&RR_MOB_DATA[rr_mob_id_dakotaraptor].loot[1],
                    rr_petal_id_stinger, 0.0006);
    init_loot_table(&RR_MOB_DATA[rr_mob_id_dakotaraptor].loot[2],
                    rr_petal_id_stinger, 0.0007);
    init_loot_table(&RR_MOB_DATA[rr_mob_id_dakotaraptor].loot[3],
                    rr_petal_id_stinger, 0.0008);
}

void rr_static_data_init()
{
    init_rarity_coefficients();
    init_loot_tables();
}
