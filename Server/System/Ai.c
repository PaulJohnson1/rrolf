#include <Server/System/MapBoundary.h>

#include <assert.h>
#include <math.h>
#include <stdlib.h>

#include <Server/EntityAllocation.h>
#include <Server/Simulation.h>
#include <Shared/Entity.h>
#include <Shared/Vector.h>

static EntityIdx ai_get_nearest_target(EntityIdx entity,
                                       struct rr_simulation *simulation,
                                       float range)
{
    uint8_t team_id = rr_simulation_get_relations(simulation, entity)->team;
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);
    float closest_distance = range * range; // 1.5k is default range
    EntityIdx closest_flower = RR_NULL_ENTITY;
    if (team_id == rr_simulation_team_id_mobs)
    {
        for (uint64_t i = 0; i < simulation->flower_count; i++)
        {
            struct rr_component_physical *physical2 =
                rr_simulation_get_physical(simulation,
                                           simulation->flower_vector[i]);

            struct rr_vector delta = {physical->x, physical->y};
            struct rr_vector target_pos = {physical2->x, physical2->y};
            rr_vector_sub(&delta, &target_pos);

            float d = delta.x * delta.x + delta.y * delta.y;
            if (d < closest_distance)
            {
                closest_distance = d;
                closest_flower = physical2->parent_id;
            }
        }
    }
    for (uint64_t i = 0; i < simulation->mob_count; i++)
    {
        struct rr_component_relations *relations2 =
            rr_simulation_get_relations(simulation, simulation->mob_vector[i]);
        if (relations2->team == team_id)
            continue;
        struct rr_component_physical *physical2 =
            rr_simulation_get_physical(simulation, simulation->mob_vector[i]);

        struct rr_vector delta = {physical->x, physical->y};
        struct rr_vector target_pos = {physical2->x, physical2->y};
        rr_vector_sub(&delta, &target_pos);

        float d = delta.x * delta.x + delta.y * delta.y;
        if (d < closest_distance)
        {
            closest_distance = d;
            closest_flower = physical2->parent_id;
        }
    }

    return closest_flower;
}

static uint8_t check_if_aggro(struct rr_component_ai *ai,
                              struct rr_simulation *simulation)
{
    if (ai->target_entity == RR_NULL_ENTITY ||
        !rr_simulation_has_entity(simulation, ai->target_entity))
        ai->target_entity =
            ai_get_nearest_target(ai->parent_id, simulation, 1550);
    if (ai->target_entity != RR_NULL_ENTITY &&
        rr_simulation_has_entity(simulation, ai->target_entity))
    {
        if (ai->ai_state == rr_ai_state_idle ||
            ai->ai_state == rr_ai_state_idle_moving)
        {
            ai->ticks_until_next_action = 25;
            return 1;
        }
    }
    else if (!(ai->ai_state == rr_ai_state_idle ||
            ai->ai_state == rr_ai_state_idle_moving))
    {
        ai->target_entity = RR_NULL_ENTITY;
        ai->ai_state = rr_ai_state_idle;
        ai->ticks_until_next_action = rand() % 25 + 25;
    }
    return 0;
}

static void tick_idle(EntityIdx entity, struct rr_simulation *simulation)
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
    if (speed != 0)
        rr_vector_scale(&velocity, distance / speed);
    else
        rr_vector_set(&velocity, 0, 0);
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

    if (ai->ai_state == rr_ai_state_idle ||
        ai->ai_state == rr_ai_state_idle_moving)
    {
        if (rr_simulation_has_entity(simulation, ai->target_entity))
        {
            ai->ai_state = rr_ai_state_waiting_to_attack;
            ai->ticks_until_next_action = 25;
        }
    }
    if (ai->target_entity != RR_NULL_ENTITY &&
        !rr_simulation_has_entity(simulation, ai->target_entity))
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
    case rr_ai_state_waiting_to_attack:
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
        struct rr_vector prediction =
            predict(delta, physical2->velocity, ai->has_prediction * 15);
        rr_component_physical_set_angle(physical, rr_vector_theta(&prediction));
        break;
    }
    case rr_ai_state_attacking:
    {
        if (ai->ticks_until_next_action == 0)
        {
            ai->ai_state = rr_ai_state_waiting_to_attack;
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
        struct rr_vector prediction =
            predict(delta, physical2->velocity, ai->has_prediction * 15);
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
    if (check_if_aggro(ai, simulation))
        ai->ai_state = rr_ai_state_attacking;

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
        // struct rr_vector prediction = predict(delta, physical2->velocity, 4);
        float target_angle = rr_vector_theta(&delta);

        rr_component_physical_set_angle(
            physical, rr_angle_lerp(physical->angle, target_angle, 0.4));

        rr_vector_from_polar(&accel, 1.9, physical->angle);
        rr_vector_add(&physical->acceleration, &accel);
        ai->ticks_until_next_action = 2;
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

    if (ai->target_entity == RR_NULL_ENTITY ||
        !rr_simulation_has_entity(simulation, ai->target_entity))
        ai->target_entity = ai_get_nearest_target(entity, simulation, 1550);
    if (rr_simulation_has_entity(simulation, ai->target_entity) &&
        (ai->ai_state != rr_ai_state_attacking &&
         ai->ai_state != rr_ai_state_missile_shoot_delay))
    {
        ai->ai_state = rr_ai_state_attacking;
        ai->ticks_until_next_action = 50;
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
        struct rr_vector prediction =
            predict(delta, physical2->velocity,
                    ai->has_prediction * 20); // make this less op
        rr_component_physical_set_angle(physical, rr_vector_theta(&prediction));
        float distance = rr_vector_get_magnitude(&delta);
        if (distance > 500)
        {
            struct rr_vector accel;
            rr_vector_from_polar(&accel, 2.0f, physical->angle);
            rr_vector_add(&physical->acceleration, &accel);
            ai->ticks_until_next_action = 2;
        }
        else
        {
            ai->ai_state = rr_ai_state_missile_shoot_delay;
            ai->ticks_until_next_action = 25;
        }
        break;
    }
    case rr_ai_state_missile_shoot_delay:
    {
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
        struct rr_vector prediction =
            predict(delta, physical2->velocity,
                    ai->has_prediction * 20); // make this less op
        rr_component_physical_set_angle(physical, rr_vector_theta(&prediction));
        if (ai->ticks_until_next_action == 0)
        {
            ai->ai_state = rr_ai_state_attacking;
            ai->ticks_until_next_action = rand() % 25 + 38;

            struct rr_component_mob *mob =
                rr_simulation_get_mob(simulation, entity);
            // spawn a missile
            EntityIdx petal_id = rr_simulation_alloc_petal(
                simulation, physical->x, physical->y, rr_petal_id_missile,
                mob->rarity, mob->parent_id);
            struct rr_component_physical *physical2 =
                rr_simulation_get_physical(simulation, petal_id);
            struct rr_component_health *health =
                rr_simulation_get_health(simulation, petal_id);
            struct rr_component_projectile *projectile =
                rr_simulation_get_projectile(simulation, petal_id);

            rr_component_physical_set_angle(physical2, physical->angle);
            rr_component_physical_set_radius(
                physical2, 11 * RR_MOB_RARITY_SCALING[mob->rarity].radius);
            physical2->friction = 0.5f;
            physical2->mass = 1.0f;
            rr_vector_from_polar(&physical2->acceleration, 80, physical->angle);

            rr_component_petal_set_detached(
                rr_simulation_get_petal(simulation, petal_id), 1);

            rr_component_health_set_max_health(
                health, RR_MOB_DATA[mob->id].health *
                            RR_MOB_RARITY_SCALING[mob->rarity].health * 0.4);
            rr_component_health_set_health(
                health, RR_MOB_DATA[mob->id].health *
                            RR_MOB_RARITY_SCALING[mob->rarity].health * 0.4);
            health->damage = RR_MOB_DATA[mob->id].damage *
                             RR_MOB_RARITY_SCALING[mob->rarity].damage * 0.2f;
            rr_component_health_set_hidden(health, 1);

            projectile->ticks_until_death = 50;

            struct rr_vector recoil;

            rr_vector_from_polar(&recoil, -2,
                                 physical->angle); // recoil
            rr_vector_add(&physical->acceleration, &recoil);
        }
        break;
    }
    default:
        break;
    }
}

static void tick_ai_aggro_pachycephalosaurus(EntityIdx entity,
                                             struct rr_simulation *simulation)
{
    struct rr_component_ai *ai = rr_simulation_get_ai(simulation, entity);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);
    if (check_if_aggro(ai, simulation))
        ai->ai_state = rr_ai_state_waiting_to_attack;

    switch (ai->ai_state)
    {
    case rr_ai_state_recovering_after_charge:
    case rr_ai_state_idle:
        tick_idle(entity, simulation);
        break;

    case rr_ai_state_idle_moving:
        tick_idle_moving(entity, simulation);
        break;
    case rr_ai_state_waiting_to_attack:
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
        struct rr_vector prediction =
            predict(delta, physical2->velocity, ai->has_prediction * 15);
        rr_component_physical_set_angle(physical, rr_vector_theta(&prediction));
        break;
    }
    case rr_ai_state_attacking:
    {
        if (ai->ticks_until_next_action == 0)
        {
            ai->ai_state = rr_ai_state_waiting_to_attack;
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

        rr_vector_from_polar(&accel, 3.25, physical->angle);
        rr_vector_add(&physical->acceleration, &accel);
        break;
    }
    default:
        break;
    }
}

static void tick_ai_aggro_ankylosaurus(EntityIdx entity,
                                       struct rr_simulation *simulation)
{
    struct rr_component_ai *ai = rr_simulation_get_ai(simulation, entity);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);

    if (check_if_aggro(ai, simulation))
        ai->ai_state = rr_ai_state_chasing;
    if (ai->ai_state == rr_ai_state_attacking)
        physical->knockback_scale = 5.0f;
    else
        physical->knockback_scale = 1.0f;

    switch (ai->ai_state)
    {
    case rr_ai_state_recovering_after_charge:
    case rr_ai_state_idle:
        tick_idle(entity, simulation);
        break;
    case rr_ai_state_idle_moving:
        tick_idle_moving(entity, simulation);
        break;
    case rr_ai_state_chasing:
    {
        struct rr_vector accel;
        struct rr_component_physical *physical2 =
            rr_simulation_get_physical(simulation, ai->target_entity);

        struct rr_vector delta = {physical2->x, physical2->y};
        struct rr_vector target_pos = {physical->x, physical->y};
        rr_vector_sub(&delta, &target_pos);
        // struct rr_vector prediction = predict(delta, physical2->velocity, 4);
        float target_angle = rr_vector_theta(&delta);

        rr_component_physical_set_angle(
            physical, rr_angle_lerp(physical->angle, target_angle, 0.4));

        rr_vector_from_polar(&accel, 1.9, physical->angle);
        rr_vector_add(&physical->acceleration, &accel);
        ai->ticks_until_next_action = 2;
        if (rr_vector_get_magnitude(&delta) < 450)
        {
            ai->ai_state = rr_ai_state_waiting_to_attack;
            ai->ticks_until_next_action = 25;
        }
        break;
    }
    case rr_ai_state_waiting_to_attack:
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
        struct rr_vector prediction =
            predict(delta, physical2->velocity, ai->has_prediction * 15);
        rr_component_physical_set_angle(
            physical, rr_vector_theta(&prediction) +
                          sinf(ai->ticks_until_next_action) * 0.2);
        break;
    }
    case rr_ai_state_attacking:
    {
        if (ai->ticks_until_next_action == 0)
        {
            ai->ai_state = rr_ai_state_waiting_to_attack;
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
        struct rr_vector prediction =
            predict(delta, physical2->velocity, ai->has_prediction * 15);
        float target_angle = rr_vector_theta(&prediction);

        rr_component_physical_set_angle(physical, M_PI + target_angle);

        rr_vector_from_polar(&accel, 3.25, target_angle);
        rr_vector_add(&physical->acceleration, &accel);
        break;
    }
    default:
        break;
    }
}

static void tick_ai_aggro_meteor(EntityIdx entity,
                                       struct rr_simulation *simulation)
{
    struct rr_component_ai *ai = rr_simulation_get_ai(simulation, entity);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);

    switch (ai->ai_state)
    {
    case rr_ai_state_idle:
        ai->ai_state = rr_ai_state_idle_moving;
        float angle = rr_frand() * 2 * M_PI;
        rr_vector_from_polar(&physical->acceleration, 0.75, angle);
        break;
    case rr_ai_state_idle_moving:
    {
        float angle = rr_vector_theta(&physical->velocity);
        struct rr_vector position = {physical->x, physical->y};
        if (rr_vector_get_magnitude(&position) >= 1650.0f - physical->radius - 0.001)
        {
            float tangent = rr_vector_theta(&position);
            angle = tangent - (M_PI - (tangent - angle));
        }
        rr_vector_from_polar(&physical->acceleration, 0.75, angle);
        rr_vector_from_polar(&physical->velocity, 3, angle);
        rr_component_physical_set_angle(physical, physical->angle + 0.1);
        ai->ticks_until_next_action = 10;
        break;
    }
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
    struct rr_component_relations *relations =
        rr_simulation_get_relations(this, entity);
    if (relations->team == rr_simulation_team_id_players ||
        ai->ai_state == rr_ai_state_returning_to_owner)
    {
        struct rr_component_physical *flower_physical =
            rr_simulation_get_physical(this, relations->owner);
        float dx = flower_physical->x - physical->x;
        float dy = flower_physical->y - physical->y;
        if ((ai->ai_state == rr_ai_state_returning_to_owner &&
             dx * dx + dy * dy >
                 (250 + physical->radius) * (250 + physical->radius)))
        {
            struct rr_vector accel = {dx, dy};
            rr_vector_set_magnitude(&accel, 1.5);
            rr_vector_add(&physical->acceleration, &accel);
            rr_component_physical_set_angle(physical, rr_vector_theta(&accel));
            return;
        }
        else if (dx * dx + dy * dy >
                 (400 + physical->radius) * (400 + physical->radius))
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
    case rr_ai_aggro_type_pachycephalosaurus:
        tick_ai_aggro_pachycephalosaurus(entity, this);
        break;
    case rr_ai_aggro_type_t_rex:
        tick_ai_aggro_t_rex(entity, this);
        break;
    case rr_ai_aggro_type_pteranodon:
        tick_ai_aggro_pteranodon(entity, this);
        break;
    case rr_ai_aggro_type_ankylosaurus:
        tick_ai_aggro_ankylosaurus(entity, this);
        break;
    case rr_ai_aggro_type_meteor:
        tick_ai_aggro_meteor(entity, this);
        break;
    default:
        RR_UNREACHABLE("invalid ai aggro type state");
        break;
    }
    ai->ticks_until_next_action--;
}

void rr_system_ai_tick(struct rr_simulation *simulation)
{
    rr_simulation_for_each_ai(simulation, simulation, system_for_each);
}
