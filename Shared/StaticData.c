#include <Shared/StaticData.h>

#include <stdio.h>
#include <math.h>

struct rr_petal_data RR_PETAL_DATA[rr_petal_id_max] = {
    {rr_petal_id_no_petal, 0.0f,   0.0f,  0.0f,  0,    {                  }},
    {rr_petal_id_basic,    10.0f,  10.0f, 0.0f,  37,   {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_light,    13.0f,  5.0f,  0.0f,  12,   {1, 2, 2, 3, 3, 5, 5}},
    {rr_petal_id_stinger,  120.0f, 2.0f,  10.0f, 100,  {1, 1, 1, 1, 1, 3, 5}},
    {rr_petal_id_faster,   10.0f,  5.0f,  25.0f, 25,   {1, 1, 1, 1, 1, 2, 2}},
    {rr_petal_id_missile,  75.0f,  5.0f,  15.0f, 100,  {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_peas,     75.0f,  5.0f,  8.0f,  100,  {4, 4, 4, 4, 4, 4, 4}},
};

struct rr_mob_data RR_MOB_DATA[rr_mob_id_max] = {
    {rr_mob_id_baby_ant,       1,  1, 17.5f, {}},
    {rr_mob_id_worker_ant,     1,  1, 17.5f, {}},
    {rr_mob_id_centipede_head, 10, 1, 35.0f, {}},
    {rr_mob_id_centipede_body, 10, 1, 35.0f, {}}
};

struct rr_mob_rarity_scale RR_MOB_RARITY_SCALING[rr_rarity_max] = {
    {1, 1, 1},
    {2, 2, 1.1},
    {6, 6, 1.3},
    {15, 15, 1.6},
    {50, 50, 2.5},
    {200, 200, 5.0},
    {1000, 1000, 20.0}
};

uint32_t RR_RARITY_COLORS[rr_rarity_max] = {0xff7eef6d, 0xffffe65d, 0xff4d52e3, 0xff861fde, 0xffde1f1f, 0xff1fdbde, 0xffff2b75};
char const *RR_RARITY_NAMES[rr_rarity_max] = {"Common", "Unusual", "Rare", "Epic", "Legendary", "Mythic", "Ultra"};

double RR_DROP_RARITY_COEFFICIENTS[rr_rarity_max + 1] = {0, 1, 5, 5, 7, 8, 30, 5};
uint32_t RR_MOB_RARITY_COEFFICIENTS[rr_rarity_max] = {5, 2, 3, 3, 3, 3, 15};

static void init_rarity_coefficients()
{
    double sum = 1;
    for (uint64_t a = 1; a < rr_rarity_max; ++a)
    {
        sum += (RR_DROP_RARITY_COEFFICIENTS[a + 1] = RR_DROP_RARITY_COEFFICIENTS[a] / RR_DROP_RARITY_COEFFICIENTS[a + 1]);
        RR_MOB_RARITY_COEFFICIENTS[a] *= RR_MOB_RARITY_COEFFICIENTS[a - 1];
    }
    for (uint64_t a = 1; a <= rr_rarity_max; ++a)
        RR_DROP_RARITY_COEFFICIENTS[a] = RR_DROP_RARITY_COEFFICIENTS[a] / sum + RR_DROP_RARITY_COEFFICIENTS[a - 1];
    RR_DROP_RARITY_COEFFICIENTS[rr_rarity_max] = 1;
}

static void init_loot_table(struct rr_loot_data *data, uint8_t id, float seed)
{
    printf("loot table with seed %f\n", seed);
    data->id = id;
    for (uint64_t mob = 0; mob < rr_rarity_max; ++mob)
    {
        uint64_t cap = mob != 0 ? mob : 1;
        data->loot_table[mob][0] = pow(1 - seed, RR_MOB_RARITY_COEFFICIENTS[mob]);
        for (uint64_t drop = 0; drop <= cap; ++drop)
        {
            float start = RR_DROP_RARITY_COEFFICIENTS[drop];
            float end = drop == cap ? 1 : RR_DROP_RARITY_COEFFICIENTS[drop + 1];
            data->loot_table[mob][drop + 1] = pow(1 - (1 - end) * seed, RR_MOB_RARITY_COEFFICIENTS[mob]) - pow(1 - (1 - start) * seed, RR_MOB_RARITY_COEFFICIENTS[mob]);
            printf("%f ", data->loot_table[mob][drop + 1]);
        }
        puts("");
    }
    printf("------------------------------------------\n");
}

static void init_loot_tables()
{
    init_loot_table(&RR_MOB_DATA[rr_mob_id_baby_ant].loot[0], rr_petal_id_basic, 0.25);
    init_loot_table(&RR_MOB_DATA[rr_mob_id_baby_ant].loot[1], rr_petal_id_light, 0.25);
    init_loot_table(&RR_MOB_DATA[rr_mob_id_baby_ant].loot[2], rr_petal_id_missile, 0.05);
    init_loot_table(&RR_MOB_DATA[rr_mob_id_baby_ant].loot[3], rr_petal_id_peas, 0.1);

    init_loot_table(&RR_MOB_DATA[rr_mob_id_worker_ant].loot[0], rr_petal_id_peas, 0.1);
    init_loot_table(&RR_MOB_DATA[rr_mob_id_worker_ant].loot[1], rr_petal_id_missile, 0.4);

    init_loot_table(&RR_MOB_DATA[rr_mob_id_centipede_head].loot[0], rr_petal_id_peas, 1);
    init_loot_table(&RR_MOB_DATA[rr_mob_id_centipede_head].loot[1], rr_petal_id_light, 0.75);

    init_loot_table(&RR_MOB_DATA[3].loot[0], rr_petal_id_peas, 0.5);
}

void rr_static_data_init()
{
    init_rarity_coefficients();
    init_loot_tables();
}
 