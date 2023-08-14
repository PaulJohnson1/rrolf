#include <Server/System/Drops.h>

#include <stdlib.h>

#include <Server/Simulation.h>

struct drop_pick_up_captures
{
    struct rr_simulation *simulation;
    EntityIdx self;
};

static void drop_pick_up(EntityIdx entity, void *_captures)
{
    struct drop_pick_up_captures *captures = _captures;
    struct rr_simulation *this = captures->simulation;
    EntityIdx drop_id = captures->self;
    struct rr_component_drop *drop = rr_simulation_get_drop(this, drop_id);

    struct rr_component_relations *flower_relations =
        rr_simulation_get_relations(this, entity);
    if (!rr_simulation_has_entity(this, flower_relations->owner))
        return;

    struct rr_component_player_info *player_info =
        rr_simulation_get_player_info(this, flower_relations->owner);
    if (rr_bitset_get(drop->picked_up_by, player_info->client_id))
        return;
    struct rr_component_physical *physical =
        rr_simulation_get_physical(this, drop_id);

    struct rr_component_physical *flower_physical =
        rr_simulation_get_physical(this, entity);

    struct rr_vector delta = {physical->x - flower_physical->x,
                              physical->y - flower_physical->y};
    if (rr_vector_get_magnitude(&delta) >
        physical->radius + player_info->modifiers.drop_pickup_radius)
        return;
    rr_bitset_set(drop->picked_up_by, player_info->client_id);

    for (struct rr_drop_picked_up *i = player_info->collected_this_run;
         i < player_info->collected_this_run_end; i++)
    {
        if (i->id == drop->id && i->rarity == drop->rarity)
        {
            ++i->count;
            return;
        }
    }

    // for loop didn't make the function return early so we must create the new
    // entry
    uint64_t size =
        player_info->collected_this_run_end - player_info->collected_this_run;
    player_info->collected_this_run =
        realloc(player_info->collected_this_run,
                (size + 1) * sizeof(struct rr_drop_picked_up));
    player_info->collected_this_run_end =
        player_info->collected_this_run + size + 1;
    player_info->collected_this_run[size].count = 1;
    player_info->collected_this_run[size].rarity = drop->rarity;
    player_info->collected_this_run[size].id = drop->id;
}

static void drop_despawn_tick(EntityIdx entity, void *_captures)
{
    struct rr_simulation *this = _captures;
    struct rr_component_drop *drop = rr_simulation_get_drop(this, entity);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(this, entity);
    if (drop->ticks_until_despawn == 0)
    {
        rr_simulation_request_entity_deletion(this, entity);
        return;
    }
    --drop->ticks_until_despawn;
    if (drop->ticks_until_despawn > 25 * 10 * (drop->rarity + 1) - 10)
        return;
    struct drop_pick_up_captures captures;
    captures.self = entity;
    captures.simulation = this;
    rr_simulation_for_each_flower(this, &captures, drop_pick_up);
}

void rr_system_drops_tick(struct rr_simulation *this)
{
    rr_simulation_for_each_drop(this, this, drop_despawn_tick);
}
