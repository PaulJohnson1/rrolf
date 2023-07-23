#include <Server/System/CollisionResolution.h>

#include <Server/System/CollisionDetection.h>

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

    exclude(drop, drop);
    exclude(drop, petal);
    exclude(drop, flower);
    exclude(drop, mob);
    uint8_t team1 = rr_simulation_get_relations(this, a)->team;
    uint8_t team2 = rr_simulation_get_relations(this, b)->team;
    if (team1 != team2)
        return 1; // only drop doesn't care about team
    exclude(petal, petal);
    exclude(petal, flower);
    exclude(petal, mob);
    exclude(flower, mob);
#undef exclude

    return 1;
}

struct colliding_with_captures
{
    struct rr_simulation *simulation;
    struct rr_component_physical *physical;
};

// that's for the casting which is not impm
static void colliding_with_function(uint64_t i, void *_captures)
{
    struct colliding_with_captures *captures = _captures;
    struct rr_simulation *this = captures->simulation;
    struct rr_component_physical *physical1 = captures->physical;
    EntityIdx entity1 = physical1->parent_id;
    EntityIdx entity2 = i;

    if (!should_entities_collide(this, entity1, entity2))
        return;

    struct rr_component_physical *physical2 =
        rr_simulation_get_physical(captures->simulation, entity2);

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
        rr_component_physical_set_x(
            physical1, physical1->x - overlap * delta.x / distance * v1_Coeff);
        rr_component_physical_set_y(
            physical1, physical1->y - overlap * delta.y / distance * v1_Coeff);
        rr_component_physical_set_x(
            physical2, physical2->x + overlap * delta.x / distance * v2_Coeff);
        rr_component_physical_set_y(
            physical2, physical2->y + overlap * delta.y / distance * v2_Coeff);
    }

    {
        float v2_Coeff = 2.0f * physical1->mass / (physical1->mass + physical2->mass);
        float v1_Coeff = 2.0f * physical2->mass / (physical1->mass + physical2->mass);
        float v_SharedCoeff = (physical1->mass - physical2->mass) / (physical1->mass + physical2->mass);

        // struct rr_vector delta = (ball2Position - ball1Position).Normalize();
        rr_vector_normalize(&delta);
        float scale1 = (physical1->velocity.x * delta.x + physical1->velocity.y * delta.y);
        float scale2 = (physical2->velocity.x * delta.x + physical2->velocity.y * delta.y);
        struct rr_vector parallel1 = {delta.x * scale1, delta.y * scale1};
        struct rr_vector perp1 = {physical1->velocity.x - parallel1.x, physical1->velocity.y - parallel1.y};
        struct rr_vector parallel2 = {delta.x * scale2, delta.y * scale2};
        struct rr_vector perp2 = {physical2->velocity.x - parallel2.x, physical2->velocity.y - parallel2.y};
        float restitution = 0.2f;
        if (scale2 * v1_Coeff + scale1 * v_SharedCoeff > 0)
            rr_vector_set(&physical1->velocity,
                            (parallel2.x * v1_Coeff + parallel1.x * v_SharedCoeff) * restitution + perp1.x,
                            (parallel2.y * v1_Coeff + parallel1.y * v_SharedCoeff) * restitution + perp1.y);
        if (scale1 * v1_Coeff - scale2 * v_SharedCoeff < 0)
            rr_vector_set(&physical2->velocity,
                        (parallel1.x * v1_Coeff - parallel2.x * v_SharedCoeff) * restitution + perp2.x,
                        (parallel1.y * v1_Coeff - parallel2.y * v_SharedCoeff) * restitution + perp2.y);
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
