#include <Server/System/MapBoundary.h>

#include <assert.h>
#include <math.h>
#include <stdlib.h>

#include <Server/Simulation.h>
#include <Shared/Entity.h>
#include <Shared/Vector.h>

static EntityIdx flowers[8] = {0};
static EntityIdx mobs[1024] = {0};
static uint64_t flowers_size = 0;
static uint64_t mobs_size = 0;

void tick_idle(EntityIdx entity, struct rr_simulation *simulation)
{
    struct rr_component_ai *ai = rr_simulation_get_ai(simulation, entity);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);

    if (ai->ticks_until_next_action == 0)
    {
        ai->ticks_until_next_action = rand() % 33 + 25;
        ai->ai_state = rr_ai_state_idle_moving;
        rr_component_physical_set_angle(
            physical, physical->angle + (rr_frand() - 0.5) * M_PI);
    }
}

static struct rr_vector predict(struct rr_vector delta,
                                struct rr_vector velocity, float speed)
{
    float distance = rr_vector_get_magnitude(&delta);
    rr_vector_scale(&velocity, distance / speed);
    rr_vector_add(&delta, &velocity);
    return delta;
}

static void tick_idle_move(EntityIdx entity, struct rr_simulation *simulation)
{
    struct rr_component_ai *ai = rr_simulation_get_ai(simulation, entity);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);

    struct rr_vector accel;
    rr_vector_from_polar(&accel, 0.5f, physical->angle);
    rr_vector_add(&physical->acceleration, &accel);
}

static void tick_idle_moving(EntityIdx entity, struct rr_simulation *simulation)
{
    struct rr_component_ai *ai = rr_simulation_get_ai(simulation, entity);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);

    if (ai->ticks_until_next_action == 0)
    {
        ai->ticks_until_next_action = rand() % 50 + 25;
        ai->ai_state = rr_ai_state_idle;
    }
    struct rr_vector accel;
    rr_vector_from_polar(&accel, 1.0f, physical->angle);
    rr_vector_add(&physical->acceleration, &accel);
}

static EntityIdx ai_get_nearest_target(EntityIdx entity,
                                       struct rr_simulation *simulation, float range)
{
    uint8_t team_id = rr_simulation_get_relations(simulation, entity)->team;
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);
    float closest_distance = range * range; // 1.5k is default range
    EntityIdx closest_flower = RR_NULL_ENTITY;
    if (team_id == rr_simulation_team_id_mobs)
    {
        for (uint64_t i = 0; i < flowers_size; i++)
        {
            struct rr_component_physical *physical2 =
                rr_simulation_get_physical(simulation, flowers[i]);

            struct rr_vector delta = {physical->x, physical->y};
            struct rr_vector target_pos = {physical2->x, physical2->y};
            rr_vector_sub(&delta, &target_pos);

            float d = delta.x * delta.x + delta.y * delta.y;
            if (d < closest_distance)
            {
                closest_distance = d;
                closest_flower = flowers[i];
            }
        }
    }
    for (uint64_t i = 0; i < mobs_size; i++)
    {
        struct rr_component_relations *relations2 =
            rr_simulation_get_relations(simulation, mobs[i]);
        if (relations2->team == team_id)
            continue;
        struct rr_component_physical *physical2 =
            rr_simulation_get_physical(simulation, mobs[i]);

        struct rr_vector delta = {physical->x, physical->y};
        struct rr_vector target_pos = {physical2->x, physical2->y};
        rr_vector_sub(&delta, &target_pos);

        float d = delta.x * delta.x + delta.y * delta.y;
        if (d < closest_distance)
        {
            closest_distance = d;
            closest_flower = mobs[i];
        }
    }

    return closest_flower;
}

static void tick_ai_aggro_default(EntityIdx entity,
                                  struct rr_simulation *simulation)
{
    struct rr_component_ai *ai = rr_simulation_get_ai(simulation, entity);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);
    switch (ai->ai_state)
    {
    case rr_ai_state_idle:
        tick_idle(entity, simulation);
        break;
    case rr_ai_state_idle_moving:
        tick_idle_moving(entity, simulation);
        break;
    default:
        RR_UNREACHABLE("tick_ai_aggro_default reached invalid state");
        break;
    }
}

static void tick_ai_aggro_triceratops(EntityIdx entity,
                                      struct rr_simulation *simulation)
{
    struct rr_component_ai *ai = rr_simulation_get_ai(simulation, entity);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);
    
    if (ai->ai_state == rr_ai_state_idle || ai->ai_state == rr_ai_state_idle_moving)
    {
        if (rr_simulation_has_entity(simulation, ai->target_entity))
        {
            ai->ai_state = rr_ai_state_waiting_to_charge;
            ai->ticks_until_next_action = 25;
        }
    }
    if (ai->target_entity != RR_NULL_ENTITY && !rr_simulation_has_entity(simulation, ai->target_entity))
        ai->target_entity = RR_NULL_ENTITY;

    switch (ai->ai_state)
    {
    case rr_ai_state_recovering_after_charge:
    case rr_ai_state_idle:
        tick_idle(entity, simulation);
        break;

    case rr_ai_state_idle_moving:
        tick_idle_moving(entity, simulation);
        break;
    case rr_ai_state_waiting_to_charge:
    {
        if (ai->ticks_until_next_action == 0)
        {
            ai->ai_state = rr_ai_state_attacking;
            ai->ticks_until_next_action = rand() % 25 + 33;
            break;
        }

        if (ai->target_entity == RR_NULL_ENTITY)
        {
            ai->ai_state = rr_ai_state_idle_moving;
            ai->ticks_until_next_action = 25;
            break;
        }

        struct rr_component_physical *physical2 =
            rr_simulation_get_physical(simulation, ai->target_entity);

        struct rr_vector delta = {physical2->x, physical2->y};
        struct rr_vector target_pos = {physical->x, physical->y};
        rr_vector_sub(&delta, &target_pos);
        struct rr_vector prediction = predict(delta, physical2->velocity, 15);
        rr_component_physical_set_angle(physical, rr_vector_theta(&prediction));
        break;
    }
    case rr_ai_state_attacking:
    {
        if (ai->ticks_until_next_action == 0)
        {
            ai->ai_state = rr_ai_state_waiting_to_charge;
            ai->ticks_until_next_action = rand() % 25 + 25;
            break;
        }

        if (ai->target_entity == RR_NULL_ENTITY)
        {
            ai->ai_state = rr_ai_state_idle_moving;
            ai->ticks_until_next_action = 25;
            break;
        }

        struct rr_vector accel;
        struct rr_component_physical *physical2 =
            rr_simulation_get_physical(simulation, ai->target_entity);

        struct rr_vector delta = {physical2->x, physical2->y};
        struct rr_vector target_pos = {physical->x, physical->y};
        rr_vector_sub(&delta, &target_pos);
        struct rr_vector prediction = predict(delta, physical2->velocity, 15);
        float target_angle = rr_vector_theta(&prediction);

        rr_component_physical_set_angle(
            physical, rr_angle_lerp(physical->angle, target_angle, 0.05));

        rr_vector_from_polar(&accel, 3.25, physical->angle);
        rr_vector_add(&physical->acceleration, &accel);
        break;
    }
    default:
        break;
    }
}

static void tick_ai_aggro_t_rex(EntityIdx entity,
                                      struct rr_simulation *simulation)
{
    struct rr_component_ai *ai = rr_simulation_get_ai(simulation, entity);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);
    if (ai->target_entity == RR_NULL_ENTITY || !rr_simulation_has_entity(simulation, ai->target_entity))
        ai->target_entity = ai_get_nearest_target(entity, simulation, 500);
    if (ai->target_entity != RR_NULL_ENTITY && rr_simulation_has_entity(simulation, ai->target_entity))
    {
        ai->ai_state = rr_ai_state_attacking;
        ai->ticks_until_next_action = 25;
    }
    else if (ai->ai_state == rr_ai_state_attacking || ai->target_entity != RR_NULL_ENTITY)
    {
        ai->target_entity = RR_NULL_ENTITY;
        ai->ai_state = rr_ai_state_idle;
        ai->ticks_until_next_action = rand() % 25 + 25;
    }
    
    switch (ai->ai_state)
    {
    case rr_ai_state_idle:
        tick_idle(entity, simulation);
        break;

    case rr_ai_state_idle_moving:
        tick_idle_moving(entity, simulation);
        break;
    case rr_ai_state_attacking:
    {
        struct rr_vector accel;
        struct rr_component_physical *physical2 =
            rr_simulation_get_physical(simulation, ai->target_entity);

        struct rr_vector delta = {physical2->x, physical2->y};
        struct rr_vector target_pos = {physical->x, physical->y};
        rr_vector_sub(&delta, &target_pos);
        //struct rr_vector prediction = predict(delta, physical2->velocity, 4);
        float target_angle = rr_vector_theta(&delta);

        rr_component_physical_set_angle(
            physical, rr_angle_lerp(physical->angle, target_angle, 0.4));

        rr_vector_from_polar(&accel, 1.95, physical->angle);
        rr_vector_add(&physical->acceleration, &accel);
        break;
    }
    default:
        break;
    }
}

static void tick_ai_aggro_pteranodon(EntityIdx entity,
                                     struct rr_simulation *simulation)
{
    struct rr_component_ai *ai = rr_simulation_get_ai(simulation, entity);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);

    if (ai->target_entity == RR_NULL_ENTITY || !rr_simulation_has_entity(simulation, ai->target_entity))
        ai->target_entity = ai_get_nearest_target(entity, simulation, 500);
    if (rr_simulation_has_entity(simulation, ai->target_entity) &&
        (ai->ai_state != rr_ai_state_attacking &&
         ai->ai_state != rr_ai_state_missile_shoot_delay))
    {
        ai->ai_state = rr_ai_state_attacking;
        ai->ticks_until_next_action = 100;
    }

    switch (ai->ai_state)
    {
    case rr_ai_state_idle:
        tick_idle(entity, simulation);
        break;

    case rr_ai_state_idle_moving:
        tick_idle_moving(entity, simulation);
        break;
    case rr_ai_state_attacking:
        if (ai->ticks_until_next_action == 0)
        {
            ai->ai_state = rr_ai_state_missile_shoot_delay;
            ai->ticks_until_next_action = 10;
        }

        if (!rr_simulation_has_entity(simulation, ai->target_entity))
        {
            ai->ai_state = rr_ai_state_idle;
            ai->ticks_until_next_action = 50;
            break;
        }
        struct rr_component_physical *physical2 =
            rr_simulation_get_physical(simulation, ai->target_entity);

        struct rr_vector delta = {physical2->x, physical2->y};
        struct rr_vector target_pos = {physical->x, physical->y};
        rr_vector_sub(&delta, &target_pos);
        struct rr_vector prediction = predict(delta, physical2->velocity, 20);
        rr_component_physical_set_angle(physical, rr_vector_theta(&prediction));
        float distance = rr_vector_get_magnitude(&delta);
        if (distance > 500)
        {
            struct rr_vector accel;
            rr_vector_from_polar(&accel, 2.0f, physical->angle);
            rr_vector_add(&physical->acceleration, &accel);
        }
        break;

    case rr_ai_state_missile_shoot_delay:
        if (ai->ticks_until_next_action == 0)
        {
            ai->ai_state = rr_ai_state_attacking;
            ai->ticks_until_next_action = rand() % 50 + 75;

            struct rr_component_mob *mob =
                rr_simulation_get_mob(simulation, entity);
            // spawn a missile
            EntityIdx petal_id = rr_simulation_alloc_entity(simulation);
            struct rr_component_physical *physical2 =
                rr_simulation_add_physical(simulation, petal_id);
            struct rr_component_petal *petal =
                rr_simulation_add_petal(simulation, petal_id);
            struct rr_component_relations *relations =
                rr_simulation_add_relations(simulation, petal_id);
            struct rr_component_health *health =
                rr_simulation_add_health(simulation, petal_id);
            struct rr_component_projectile *projectile =
                rr_simulation_add_projectile(simulation, petal_id);

            rr_component_physical_set_x(physical2, physical->x);
            rr_component_physical_set_y(physical2, physical->y);
            rr_component_physical_set_angle(physical2, physical->angle);
            rr_component_physical_set_radius(
                physical2, 11 * RR_MOB_RARITY_SCALING[mob->rarity].radius);
            physical2->friction = 0.5f;
            physical2->mass = 1.0f;
            rr_vector_from_polar(&physical2->acceleration, 80, physical->angle);

            rr_component_relations_set_team(
                relations,
                rr_simulation_get_relations(simulation, entity)->team);
            rr_component_relations_set_owner(relations, ai->parent_id);
            rr_component_petal_set_id(petal, rr_petal_id_missile);
            rr_component_petal_set_rarity(petal, mob->rarity);
            petal->detached = 1;

            rr_component_health_set_max_health(
                health, RR_MOB_DATA[mob->id].health *
                            RR_MOB_RARITY_SCALING[mob->rarity].health * 0.1);
            rr_component_health_set_health(
                health, RR_MOB_DATA[mob->id].health *
                            RR_MOB_RARITY_SCALING[mob->rarity].health * 0.1);
            health->damage = RR_MOB_DATA[mob->id].damage *
                             RR_MOB_RARITY_SCALING[mob->rarity].damage * 0.25f;
            rr_component_health_set_hidden(health, 1);

            projectile->ticks_until_death = 50;

            ai->ticks_until_next_action = 50;

            struct rr_vector recoil;

            rr_vector_from_polar(&recoil, -2,
                                 physical->angle); // recoil
            rr_vector_add(&physical->acceleration, &recoil);
        }
        break;

    default:
        break;
    }
}

static void system_for_each(EntityIdx entity, void *simulation)
{
    struct rr_simulation *this = simulation;

    if (rr_simulation_has_centipede(this, entity) &&
        rr_simulation_get_centipede(this, entity)->parent_node !=
            RR_NULL_ENTITY)
        return;
    if (rr_simulation_get_health(this, entity)->health < 0.0001f)
        return;

    struct rr_component_ai *ai = rr_simulation_get_ai(this, entity);
    struct rr_component_mob *mob = rr_simulation_get_mob(this, entity);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(this, entity);
    struct rr_component_relations *relations = rr_simulation_get_relations(this, entity);
    if (relations->team == rr_simulation_team_id_players || ai->ai_state == rr_ai_state_returning_to_owner)
    {
        struct rr_component_physical *flower_physical = rr_simulation_get_physical(this, relations->owner);
        float dx = flower_physical->x - physical->x;
        float dy = flower_physical->y - physical->y;
        if ((ai->ai_state == rr_ai_state_returning_to_owner && dx * dx + dy * dy > (250 + physical->radius) * (250 + physical->radius)))
        {
            struct rr_vector accel = {dx, dy};
            rr_vector_set_magnitude(&accel, 1.5);
            rr_vector_add(&physical->acceleration, &accel);
            rr_component_physical_set_angle(physical, rr_vector_theta(&accel));
            return;
        }
        else if (dx * dx + dy * dy > (400 + physical->radius) * (400 + physical->radius))
        {
            ai->ai_state = rr_ai_state_returning_to_owner;
            struct rr_vector accel = {dx, dy};
            rr_vector_set_magnitude(&accel, 1.5);
            rr_vector_add(&physical->acceleration, &accel);
            rr_component_physical_set_angle(physical, rr_vector_theta(&accel));
            return;
        }
        else if (ai->ai_state == rr_ai_state_returning_to_owner)
        {
            ai->ai_state = rr_ai_state_idle;
            ai->ticks_until_next_action = rand() % 25 + 25;
        }
    }

    switch (ai->ai_aggro_type)
    {
    case rr_ai_aggro_type_none:
        break;
    case rr_ai_aggro_type_default:
        tick_ai_aggro_default(entity, this);
        break;
    case rr_ai_aggro_type_triceratops:
        tick_ai_aggro_triceratops(entity, this);
        break;
    case rr_ai_aggro_type_t_rex:
        tick_ai_aggro_t_rex(entity, this);
        break;
    case rr_ai_aggro_type_pteranodon:
        tick_ai_aggro_pteranodon(entity, this);
        break;
    default:
        RR_UNREACHABLE("invalid ai aggro type state");
        break;
    }
    ai->ticks_until_next_action--;
}

static void cache_flower_id(EntityIdx id, void *x) { flowers[flowers_size++] = id; }
static void cache_mob_id(EntityIdx id, void *x) { mobs[mobs_size++] = id; }

void rr_system_ai_tick(struct rr_simulation *simulation)
{
    // cache flower ids
    flowers_size = 0;
    mobs_size = 0;
    rr_simulation_for_each_flower(simulation, 0, cache_flower_id);
    rr_simulation_for_each_mob(simulation, 0, cache_mob_id);
    rr_simulation_for_each_ai(simulation, simulation, system_for_each);
}
