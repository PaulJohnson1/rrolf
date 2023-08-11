#include <Shared/StaticData.h>

#include <math.h>
#include <stdio.h>

// clang-format off
struct rr_petal_data RR_PETAL_DATA[rr_petal_id_max] = {
    {rr_petal_id_no_petal, rr_rarity_id_common, 0.0f, 0.0f, 0.0f, 0, 0, {0, 0, 0, 0, 0, 0, 0}},
    {rr_petal_id_basic, rr_rarity_id_common, 15.0f, 15.0f, 0.0f, 50, 0, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_pellet, rr_rarity_id_common, 12.0f, 5.0f, 0.0f, 13, 0, {1, 2, 2, 3, 3, 5, 5}},
    {rr_petal_id_rock, rr_rarity_id_common, 5.0f, 60.0f, 0.0f, 100, 0, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_stinger, rr_rarity_id_common, 50.0f, 5.0f, 10.0f, 150, 0, {1, 1, 1, 1, 1, 3, 5}},
    {rr_petal_id_light, rr_rarity_id_rare, 8.0f, 5.0f, 15.0f, 20, 0, {1, 1, 1, 1, 1, 2, 2}},
    {rr_petal_id_missile, rr_rarity_id_rare, 3.5f, 5.0f, 15.0f, 50, 13, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_peas, rr_rarity_id_rare, 15.0f, 5.0f, 8.0f, 13, 12, {4, 4, 4, 4, 4, 4, 5}},
    {rr_petal_id_leaf, rr_rarity_id_unusual, 5.0f, 10.0f, 8.0f, 20, 0, {1, 1, 1, 1, 1, 2, 2,}},
    {rr_petal_id_egg, rr_rarity_id_unusual, 1.0f, 20.0f, 0.0f, 12, 150, {2, 2, 2, 2, 2, 2, 2}},
    {rr_petal_id_magnet, rr_rarity_id_rare, 1.0f, 8.0f, 0.0f, 38, 0, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_uranium, rr_rarity_id_rare, 6.0f, 10.0f, 0.0f, 50, 0, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_feather, rr_rarity_id_common, 1.0f, 3.0f, 0.0f, 25, 0, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_azalea, rr_rarity_id_common, 5.0f, 5.0f, 0.0f, 100, 25, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_bone, rr_rarity_id_common, 5.0f, 25.0f, 0.0f, 68, 0, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_web, rr_rarity_id_rare, 5.0f, 5.0f, 0.0f, 63, 25, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_seed, rr_rarity_id_legendary, 1.0f, 20.0f, 0.0f, 63, 1, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_gravel, rr_rarity_id_unusual, 8.0f, 5.0f, 0.0f, 13, 13, {2, 2, 3, 3, 3, 3, 4}},
    {rr_petal_id_club, rr_rarity_id_common, 3.0f, 400.0f, 0.0f, 250, 0, {1, 1, 1, 1, 1, 1, 1}},
    {rr_petal_id_crest, rr_rarity_id_rare, 0.0f, 0.0f, 0.0f, 0, 0, {0, 0, 0, 0, 0, 0, 0}},
};    

struct rr_mob_data RR_MOB_DATA[rr_mob_id_max] = {
    {rr_mob_id_triceratops, 50, 15, 30.0f, {}},
    {rr_mob_id_trex, 30, 25, 32.0f, {}},
    {rr_mob_id_fern, 10, 5, 28.0f, {}},
    {rr_mob_id_stump, 50, 5, 26.0f, {}},
    {rr_mob_id_pteranodon, 35, 35, 26.0f, {}},
    {rr_mob_id_dakotaraptor, 35, 25, 30.0f, {}},
    {rr_mob_id_pachycephalosaurus, 20, 15, 25.0f, {}},
    {rr_mob_id_ornithomimus, 15, 10, 25.0f, {}},
    {rr_mob_id_ankylosaurus, 75, 10, 30.0f, {}},
    {rr_mob_id_meteor, 125, 15, 32.0f, {}}
};

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
    {12,  2.4, 1.8},
    {40,  3.6, 2.5},
    {80,  5.6, 4.0},
    {160, 12,  6.0},
};
// clang-format on

uint32_t RR_RARITY_COLORS[rr_rarity_id_max] = {
    0xff7eef6d, 0xffffe65d, 0xff4d52e3, 0xff861fde,
    0xffde1f1f, 0xff1fdbde, 0xffff2b75};
char const *RR_RARITY_NAMES[rr_rarity_id_max] = {
    "Common", "Uncommon", "Rare", "Epic", "Legendary", "Mythic", "Exotic"};
char const *RR_PETAL_NAMES[rr_petal_id_max] = {
    "Secret", "Basic", "Pellet", "Rock",   "Spikes",  "Light", "Missile",
    "Peas",   "Leaf",  "Egg",    "Magnet", "Uranium", "Feather", "Azalea",
    "Bone",   "Web",   "Seed",   "Gravel", "Club", "Crest"};
char const *RR_PETAL_DESCRIPTIONS[rr_petal_id_max] = {
    0,
    "It's just a petal",
    "Low damage, but there's lots",
    "Dwayne",
    "Ow that hurts",
    "Makes your petals lighter so you spin faster",
    "ICBM approved",
    "Splits in 4. Or maybe 5 if you're a pro",
    "Heals you gradually",
    "Spawns a pet dinosaur to protect you",
    "Increases loot pickup radius. Stacks because why not",
    "Does low damage to mobs in a large range. Does 2.5x damage to yourself",
    "It's so light it increases your movement speed. Does not stack",
    "It heals you.",
    "Gives the player armor. Stacks with itself",
    "Web",
    "What does this one do",
    "Tiny rocks that stay on the ground and trip dinos",
    "Heavy and sturdy",
    "Increases your FOV. Does not stack"
};

char const *RR_MOB_NAMES[rr_mob_id_max] = {"Triceratops",
                                           "T-Rex",
                                           "Fern",
                                           "Stump",
                                           "Pteranodon",
                                           "Dakotaraptor",
                                           "Pachycephalosaurus",
                                           "Ornithomimus",
                                           "Ankylosaurus",
                                           "Meteor"};

uint32_t RR_MOB_DIFFICULTY_COEFFICIENTS[rr_mob_id_max] = {9,  10, 2, 4, 20,
                                                          12, 9,  3, 10, 1};
double RR_MOB_ID_RARITY_COEFFICIENTS[rr_mob_id_max] = {30, 100, 15, 5, 30,
                                                       25, 45,  20, 25, 0.4};
double RR_MOB_WAVE_RARITY_COEFFICIENTS[rr_rarity_id_ultra + 2] = {
    0, 1, 5, 8, 15, 30, 75, 300};

double RR_DROP_RARITY_COEFFICIENTS[rr_rarity_id_ultra + 2] = {
    0, 1, 12.5, 18, 25, 150, 250, 50};
static double RR_MOB_LOOT_RARITY_COEFFICIENTS[rr_rarity_id_ultra + 1] = {
    3, 2, 7.5, 15, 20, 25, 50};

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
        printf("wave r: %.9f\n", RR_MOB_WAVE_RARITY_COEFFICIENTS[a]);
    }
    RR_DROP_RARITY_COEFFICIENTS[rr_rarity_id_ultra + 1] = 1;
    for (uint64_t mob = 1; mob < rr_mob_id_max; ++mob)
        RR_MOB_ID_RARITY_COEFFICIENTS[mob] +=
            RR_MOB_ID_RARITY_COEFFICIENTS[mob - 1];
    for (uint64_t mob = 0; mob < rr_mob_id_max; ++mob)
        RR_MOB_ID_RARITY_COEFFICIENTS[mob] /=
            RR_MOB_ID_RARITY_COEFFICIENTS[rr_mob_id_max - 1];
}

static void init_loot_table(struct rr_loot_data *data, uint8_t id, float seed)
{
    data->id = id;
    for (uint64_t mob = 0; mob <= rr_rarity_id_ultra; ++mob)
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
}

static void init_loot_tables()
{
    init_loot_table(&RR_MOB_DATA[rr_mob_id_triceratops].loot[0],
                    rr_petal_id_rock, 0.1);
    init_loot_table(&RR_MOB_DATA[rr_mob_id_triceratops].loot[1],
                    rr_petal_id_leaf, 0.15);

    init_loot_table(&RR_MOB_DATA[rr_mob_id_trex].loot[0], rr_petal_id_bone,
                    0.25);
    init_loot_table(&RR_MOB_DATA[rr_mob_id_trex].loot[1], rr_petal_id_stinger,
                    0.10);
    init_loot_table(&RR_MOB_DATA[rr_mob_id_trex].loot[2], rr_petal_id_egg,
                    0.05);

    init_loot_table(&RR_MOB_DATA[rr_mob_id_fern].loot[0], rr_petal_id_azalea,
                    0.10);
    init_loot_table(&RR_MOB_DATA[rr_mob_id_fern].loot[1], rr_petal_id_leaf,
                    0.25);
    init_loot_table(&RR_MOB_DATA[rr_mob_id_fern].loot[2], rr_petal_id_seed,
                    0.01);

    init_loot_table(&RR_MOB_DATA[rr_mob_id_stump].loot[0], rr_petal_id_peas,
                    0.2);
    init_loot_table(&RR_MOB_DATA[rr_mob_id_stump].loot[1], rr_petal_id_egg,
                    0.15);

    init_loot_table(&RR_MOB_DATA[rr_mob_id_pteranodon].loot[0],
                    rr_petal_id_missile, 0.25);

    init_loot_table(&RR_MOB_DATA[rr_mob_id_dakotaraptor].loot[0],
                    rr_petal_id_feather, 0.15);
    init_loot_table(&RR_MOB_DATA[rr_mob_id_dakotaraptor].loot[1],
                    rr_petal_id_crest, 0.05);

    init_loot_table(&RR_MOB_DATA[rr_mob_id_pachycephalosaurus].loot[0],
                    rr_petal_id_light, 0.05);
    init_loot_table(&RR_MOB_DATA[rr_mob_id_pachycephalosaurus].loot[1],
                    rr_petal_id_web, 0.1);
    init_loot_table(&RR_MOB_DATA[rr_mob_id_pachycephalosaurus].loot[2],
                    rr_petal_id_pellet, 0.1);

    init_loot_table(&RR_MOB_DATA[rr_mob_id_ornithomimus].loot[0],
                    rr_petal_id_pellet, 0.15);
    init_loot_table(&RR_MOB_DATA[rr_mob_id_ornithomimus].loot[1],
                    rr_petal_id_feather, 0.15);

    init_loot_table(&RR_MOB_DATA[rr_mob_id_ankylosaurus].loot[0],
                    rr_petal_id_club, 0.1);
    init_loot_table(&RR_MOB_DATA[rr_mob_id_ankylosaurus].loot[1],
                    rr_petal_id_gravel, 0.05);
    
    init_loot_table(&RR_MOB_DATA[rr_mob_id_meteor].loot[0],
                    rr_petal_id_magnet, 1);
    init_loot_table(&RR_MOB_DATA[rr_mob_id_meteor].loot[1],
                    rr_petal_id_uranium, 0.5);
}

void rr_static_data_init()
{
    init_game_coefficients();
    init_loot_tables();
}
