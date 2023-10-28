#include <Shared/Component/Mob.h>

#include <string.h>

#include <Shared/Entity.h>
#include <Shared/SimulationCommon.h>
#include <Shared/pb.h>

#ifdef RR_SERVER
#include <math.h>
#include <stdio.h>

#include <Server/EntityAllocation.h>
#include <Server/Simulation.h>

#include <Shared/Utilities.h>
#include <Shared/StaticData.h>
#endif

#define FOR_EACH_PUBLIC_FIELD                                                  \
    X(id, uint8)                                                               \
    X(rarity, uint8)                                                           \
    X(flags, uint8)

enum
{
    state_flags_rarity = 0b000001,
    state_flags_id = 0b000010,
    state_flags_flags = 0b000100,
    state_flags_all = 0b000111
};

void rr_component_mob_init(struct rr_component_mob *this,
                           struct rr_simulation *simulation)
{
    memset(this, 0, sizeof *this);
    RR_SERVER_ONLY(this->ticks_to_despawn = 120 * 25;)
}

void rr_component_mob_free(struct rr_component_mob *this,
                           struct rr_simulation *simulation)
{
#ifdef RR_SERVER
    struct rr_component_relations *relations =
        rr_simulation_get_relations(simulation, this->parent_id);
    if (this->player_spawned)
        return;
    this->zone->grid_points -= RR_MOB_DIFFICULTY_COEFFICIENTS[this->id];
    // put it here please
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, this->parent_id);
    struct rr_component_arena *arena = rr_simulation_get_arena(simulation, physical->arena);
    --arena->mob_count;
    if (this->no_drop)
        return;
    uint8_t spawn_ids[4] = {};
    uint8_t spawn_rarities[4] = {};
    uint8_t count = 0;
    uint8_t can_be_picked_up_by[RR_BITSET_ROUND(RR_SQUAD_COUNT)];

    if (rr_simulation_has_arena(simulation, this->parent_id) && rr_simulation_get_arena(simulation, this->parent_id)->player_entered)
        rr_bitset_set(can_be_picked_up_by, rr_simulation_get_arena(simulation, this->parent_id)->first_squad_to_enter);
    else 
        for (uint32_t i = 0; i < RR_SQUAD_COUNT; ++i)
            rr_bitset_maybe_set(can_be_picked_up_by, i, this->squad_damage_counter[i] > RR_MOB_DATA[this->id].health * RR_MOB_RARITY_SCALING[this->rarity].health * 0.2);

    for (uint64_t i = 0; i < 4; ++i)
    {
        if (RR_MOB_DATA[this->id].loot[i].id == 0)
            break;
        uint8_t id = RR_MOB_DATA[this->id].loot[i].id;
        float seed = rr_frand();
        float s2 = RR_MOB_DATA[this->id].loot[i].seed;
        uint8_t drop;
        uint8_t cap = this->rarity >= rr_rarity_id_exotic ? this->rarity - 1 : this->rarity;

        for (drop = 0; drop <= cap + 1; ++drop)
        {
            double end =
                drop == cap + 1 ? 1 : RR_DROP_RARITY_COEFFICIENTS[drop];
            if (cap < RR_PETAL_DATA[id].min_rarity)
                end = 1;
            else if (drop < RR_PETAL_DATA[id].min_rarity)
                end = RR_DROP_RARITY_COEFFICIENTS[RR_PETAL_DATA[id].min_rarity];
            if (seed <= pow(1 - (1 - end) * s2, RR_MOB_LOOT_RARITY_COEFFICIENTS[this->rarity]))
                break;
        }
        if (drop == 0)
            continue;
        spawn_ids[count] = RR_MOB_DATA[this->id].loot[i].id;
        spawn_rarities[count] = drop - 1;
        ++count;
    }
    for (uint8_t i = 0; i < count; ++i)
    {
        EntityIdx entity = rr_simulation_alloc_entity(simulation);
        struct rr_component_physical *drop_physical =
            rr_simulation_add_physical(simulation, entity);
        struct rr_component_drop *drop =
            rr_simulation_add_drop(simulation, entity);
        struct rr_component_relations *relations =
            rr_simulation_add_relations(simulation, entity);
        rr_component_physical_set_x(drop_physical, physical->x);
        rr_component_physical_set_y(drop_physical, physical->y);
        rr_component_physical_set_radius(drop_physical, 20);

        rr_component_drop_set_id(drop, spawn_ids[i]);
        rr_component_drop_set_rarity(drop, spawn_rarities[i]);

        rr_component_relations_set_team(relations, rr_simulation_team_id_players);
        drop->ticks_until_despawn = 25 * 10 * (spawn_rarities[i] + 1);
        memcpy(drop->can_be_picked_up_by, can_be_picked_up_by, sizeof can_be_picked_up_by);
        drop_physical->arena = physical->arena;
        if (count != 1)
        {
            float angle = M_PI * 2 * i / count;
            rr_vector_from_polar(&drop_physical->velocity, 25, angle);
            drop_physical->friction = 0.75;
        }
    }
#endif
}

#ifdef RR_SERVER
void rr_component_mob_write(struct rr_component_mob *this,
                            struct proto_bug *encoder, int is_creation,
                            struct rr_component_player_info *client)
{
    uint64_t state = this->protocol_state | (state_flags_all * is_creation);
    proto_bug_write_varuint(encoder, state, "mob component state");
#define X(NAME, TYPE) RR_ENCODE_PUBLIC_FIELD(NAME, TYPE);
    FOR_EACH_PUBLIC_FIELD
#undef X
}

RR_DEFINE_PUBLIC_FIELD(mob, uint8_t, id)
RR_DEFINE_PUBLIC_FIELD(mob, uint8_t, rarity)
RR_DEFINE_PUBLIC_FIELD(mob, uint8_t, flags)
#endif

#ifdef RR_CLIENT
void rr_component_mob_read(struct rr_component_mob *this,
                           struct proto_bug *encoder)
{
    uint64_t state = proto_bug_read_varuint(encoder, "mob component state");
#define X(NAME, TYPE) RR_DECODE_PUBLIC_FIELD(NAME, TYPE);
    FOR_EACH_PUBLIC_FIELD
#undef X
}
#endif