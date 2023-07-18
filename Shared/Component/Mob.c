#include <Shared/Component/Mob.h>

#include <string.h>

#include <Shared/Entity.h>
#include <Shared/SimulationCommon.h>
#include <Shared/pb.h>

#ifdef RR_SERVER
#include <Shared/Utilities.h>
#include <math.h>

#include <Server/Simulation.h>
#include <Shared/StaticData.h>
#endif

#define FOR_EACH_PUBLIC_FIELD                                                  \
    X(id, uint8)                                                               \
    X(rarity, uint8)

enum
{
    state_flags_rarity = 0b000001,
    state_flags_id = 0b000010,
    state_flags_all = 0b000011
};

void rr_component_mob_init(struct rr_component_mob *this,
                           struct rr_simulation *simulation)
{
    memset(this, 0, sizeof *this);
}

void rr_component_mob_free(struct rr_component_mob *this,
                           struct rr_simulation *simulation)
{
#ifdef RR_SERVER
    struct rr_component_relations *relations =
        rr_simulation_get_relations(simulation, this->parent_id);
    if (relations->team != rr_simulation_team_id_mobs)
        return;
    //put it here please
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, this->parent_id);
    struct rr_component_arena *arena = rr_simulation_get_arena(simulation, 1);
    arena->mob_count--;
    arena->mob_counters[this->id * rr_rarity_id_max + this->rarity]--;
    uint8_t spawn_ids[4] = {};
    uint8_t spawn_rarities[4] = {};
    uint8_t count = 0;

    for (uint64_t i = 0; i < 4; ++i)
    {
        if (RR_MOB_DATA[this->id].loot[i].id == 0)
            continue;
        float seed = rr_frand();
        float *table = RR_MOB_DATA[this->id].loot[i].loot_table[this->rarity];
        uint8_t rarity = 0;
        for (; rarity <= rr_rarity_id_legendary; ++rarity)
            if ((seed <= table[rarity]))
                break;
        if (rarity == 0)
            continue;
        spawn_ids[count] = RR_MOB_DATA[this->id].loot[i].id;
        spawn_rarities[count] = rarity - 1;
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
        rr_component_physical_set_radius(drop_physical, 25);

        rr_component_drop_set_id(drop, spawn_ids[i]);
        rr_component_drop_set_rarity(drop, spawn_rarities[i]);

        rr_component_relations_set_team(relations,
                                        rr_simulation_team_id_players);

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
                            struct proto_bug *encoder, int is_creation)
{
    uint64_t state = this->protocol_state | (state_flags_all * is_creation);
    proto_bug_write_varuint(encoder, state, "mob component state");
#define X(NAME, TYPE) RR_ENCODE_PUBLIC_FIELD(NAME, TYPE);
    FOR_EACH_PUBLIC_FIELD
#undef X
}

RR_DEFINE_PUBLIC_FIELD(mob, uint8_t, id)
RR_DEFINE_PUBLIC_FIELD(mob, uint8_t, rarity)
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