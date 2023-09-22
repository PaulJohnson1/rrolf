#include <Server/System/System.h>

#include <stdio.h>
#include <string.h>

#include <Server/Simulation.h>
#include <Shared/Bitset.h>

static uint8_t should_entities_collide(struct rr_simulation *this, EntityIdx a,
                                       EntityIdx b)
{
#define exclude(component_a, component_b)                                      \
    if (rr_simulation_has_##component_a(this, a) &&                            \
        rr_simulation_has_##component_b(this, b))                              \
        return 0;                                                              \
    if (rr_simulation_has_##component_a(this, b) &&                            \
        rr_simulation_has_##component_b(this, a))                              \
        return 0;

    exclude(drop, petal);
    exclude(drop, flower);
    exclude(arena, petal);
    exclude(arena, mob);
    uint8_t team1 = rr_simulation_get_relations(this, a)->team;
    uint8_t team2 = rr_simulation_get_relations(this, b)->team;
    if (team1 != team2)
        return 1; // only drop doesn't care about team

#undef exclude

    return 1;
}

struct colliding_with_captures
{
    struct rr_simulation *simulation;
    struct rr_component_physical *physical;
};

static void web_logic(struct rr_simulation *this, EntityIdx entity1,
                      EntityIdx entity2)
{
    if (rr_simulation_get_relations(this, entity2)->team ==
        rr_simulation_get_relations(this, entity1)->team)
        return;
    if (!(rr_simulation_has_mob(this, entity2) || rr_simulation_has_flower(this, entity2)))
        return;
    rr_simulation_get_physical(this, entity2)->webbed = 1;
}

// that's for the casting which is not impm
static void colliding_with_function(uint64_t i, void *_captures)
{
    struct colliding_with_captures *captures = _captures;
    struct rr_simulation *this = captures->simulation;
    struct rr_component_physical *physical1 = captures->physical;
    EntityIdx entity1 = physical1->parent_id;
    EntityIdx entity2 = i;
    struct rr_component_physical *physical2 =
        rr_simulation_get_physical(captures->simulation, entity2);

    if (!should_entities_collide(this, entity1, entity2))
        return;
    if (rr_simulation_has_arena(this, entity1))
    {
        physical2->arena = entity1;
        struct rr_spawn_zone *respawn_zone = &rr_simulation_get_arena(this, entity1)->respawn_zone;
        rr_component_physical_set_x(physical2, respawn_zone->x + respawn_zone->w * rr_frand());
        rr_component_physical_set_y(physical2, respawn_zone->y + respawn_zone->h * rr_frand());
        rr_vector_set(&physical2->velocity, 0, 0);
        rr_vector_set(&physical2->collision_velocity, 0, 0);
        return;
    }
    else if (rr_simulation_has_arena(this, entity2))
    {
        physical1->arena = entity2;
        struct rr_spawn_zone *respawn_zone = &rr_simulation_get_arena(this, entity2)->respawn_zone;
        rr_component_physical_set_x(physical1, respawn_zone->x + respawn_zone->w * rr_frand());
        rr_component_physical_set_y(physical1, respawn_zone->y + respawn_zone->h * rr_frand());
        rr_vector_set(&physical1->velocity, 0, 0);
        rr_vector_set(&physical2->collision_velocity, 0, 0);
        return;
    }

    if (rr_simulation_has_web(this, entity1))
        return web_logic(this, entity1, entity2);
    else if (rr_simulation_has_web(this, entity2))
        return web_logic(this, entity2, entity1);

    

    struct rr_vector position1 = {physical1->x, physical1->y};
    struct rr_vector position2 = {physical2->x, physical2->y};
    struct rr_vector delta = {physical1->x - physical2->x,
                              physical1->y - physical2->y};
    float distance = rr_vector_get_magnitude(&delta);
    if (distance == 0)
        return;
    {
        float overlap = (distance - physical1->radius - physical2->radius);
        float v2_Coeff = physical1->mass / (physical1->mass + physical2->mass);
        float v1_Coeff = physical2->mass / (physical1->mass + physical2->mass);
        physical1->collision_velocity.x -= overlap * delta.x / distance * v1_Coeff;
        physical1->collision_velocity.y -= overlap * delta.y / distance * v1_Coeff;
        physical2->collision_velocity.x += overlap * delta.x / distance * v2_Coeff;
        physical2->collision_velocity.y += overlap * delta.y / distance * v2_Coeff;
    }

    {
        #define KNOCKBACK_CONST (25.0f / 2)
        float coeff = (physical2->mass) / (physical1->mass + physical2->mass);
        rr_vector_normalize(&delta);
        physical1->collision_velocity.x += coeff * KNOCKBACK_CONST * delta.x * physical2->knockback_scale;
        physical1->collision_velocity.y += coeff * KNOCKBACK_CONST * delta.y * physical2->knockback_scale;
        physical2->collision_velocity.x += (coeff - 1) * KNOCKBACK_CONST * delta.x * physical1->knockback_scale;
        physical2->collision_velocity.y += (coeff - 1) * KNOCKBACK_CONST * delta.y * physical1->knockback_scale;
        #undef KNOCKBACK_CONST
    }
}

static void system_for_each_function(EntityIdx entity, void *_captures)
{
    struct rr_simulation *this = _captures;

    struct rr_component_physical *physical =
        rr_simulation_get_physical(this, entity);
    // if (!physical->has_collisions)
    //     return;

    struct colliding_with_captures captures;
    captures.physical = physical;
    captures.simulation = this;

    for (uint64_t i = 0; i < physical->colliding_with_size; ++i)
    {
        colliding_with_function(physical->colliding_with[i], &captures);
    }

    // rr_bitset_for_each_bit(physical->collisions, physical->collisions +
    // (RR_BITSET_ROUND(RR_MAX_ENTITY_COUNT)), &captures,
    // colliding_with_function);
}

void rr_system_collision_resolution_tick(struct rr_simulation *this)
{
    rr_simulation_for_each_physical(this, this, system_for_each_function);
}
