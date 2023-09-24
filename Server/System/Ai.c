#include <Server/System/MapBoundary.h>

#include <assert.h>
#include <math.h>
#include <stdlib.h>

#include <Server/EntityAllocation.h>
#include <Server/EntityDetection.h>
#include <Server/Simulation.h>
#include <Shared/Entity.h>
#include <Shared/Vector.h>


static uint8_t is_close_enough_to_parent(struct rr_simulation *simulation, EntityIdx seeker, EntityIdx target, void *captures)
{
    struct rr_component_physical *parent_physical = captures;
    struct rr_component_physical *physical = rr_simulation_get_physical(simulation, target);
    return ((physical->x - parent_physical->x) * (physical->x - parent_physical->x) + 
    (physical->y - parent_physical->y) * (physical->y - parent_physical->y) < 500 * 500);
}

static uint8_t has_new_target(struct rr_component_ai *ai,
                              struct rr_simulation *simulation)
{
    if (ai->target_entity == RR_NULL_ENTITY ||
        !rr_simulation_entity_alive(simulation, ai->target_entity))
    {
        struct rr_component_relations *relations = rr_simulation_get_relations(simulation, ai->parent_id);
        if (relations->team == rr_simulation_team_id_mobs)
            ai->target_entity = rr_simulation_find_nearest_enemy(simulation, ai->parent_id, 1500, NULL, no_filter);
        else
        {
            ai->target_entity = rr_simulation_find_nearest_enemy(simulation, ai->parent_id, 1500, rr_simulation_get_physical(simulation, relations->owner), is_close_enough_to_parent);
        }
    }
    if (ai->target_entity != RR_NULL_ENTITY &&
        rr_simulation_entity_alive(simulation, ai->target_entity))
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

static void tick_ai_passive_default(EntityIdx entity,
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
        break;
    }
}

static void tick_ai_neutral_default(EntityIdx entity,
                                struct rr_simulation *simulation, float speed)
{
    struct rr_component_ai *ai = rr_simulation_get_ai(simulation, entity);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);
    if (rr_simulation_entity_alive(simulation, ai->target_entity))
    {
        ai->ai_state = rr_ai_state_attacking;
        ai->ticks_until_next_action = 25;
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
        // struct rr_vector prediction = predict(delta, physical2->velocity, 4);
        float target_angle = rr_vector_theta(&delta);

        rr_component_physical_set_angle(
            physical, rr_angle_lerp(physical->angle, target_angle, 0.4));

        rr_vector_from_polar(&accel, speed, physical->angle);
        rr_vector_add(&physical->acceleration, &accel);
        ai->ticks_until_next_action = 2;
        break;
    }
    default:
        break;
    }
}

static void tick_ai_aggro_default(EntityIdx entity,
                                struct rr_simulation *simulation, float speed)
{
    struct rr_component_ai *ai = rr_simulation_get_ai(simulation, entity);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);
    if (has_new_target(ai, simulation))
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

        rr_vector_from_polar(&accel, speed, physical->angle);
        rr_vector_add(&physical->acceleration, &accel);
        ai->ticks_until_next_action = 2;
        break;
    }
    default:
        break;
    }
}

static void tick_ai_aggro_hornet(EntityIdx entity,
                                     struct rr_simulation *simulation)
{
    struct rr_component_ai *ai = rr_simulation_get_ai(simulation, entity);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);

    if (has_new_target(ai, simulation))
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
            rr_vector_from_polar(&accel, RR_BASE_PLAYER_SPEED, physical->angle);
            rr_vector_add(&physical->acceleration, &accel);
        }
        if (ai->ticks_until_next_action == 0)
        {
            ai->ticks_until_next_action = 50;

            struct rr_component_mob *mob =
                rr_simulation_get_mob(simulation, entity);
            // spawn a shell
            EntityIdx petal_id = rr_simulation_alloc_petal(
                simulation, physical->x, physical->y, rr_petal_id_missile,
                mob->rarity, mob->parent_id);
            struct rr_component_physical *physical2 =
                rr_simulation_get_physical(simulation, petal_id);
            struct rr_component_health *health =
                rr_simulation_get_health(simulation, petal_id);
            rr_component_physical_set_angle(physical2, physical->angle);
            rr_component_physical_set_radius(
                physical2, 11 * RR_MOB_RARITY_SCALING[mob->rarity].radius);
            physical2->friction = 0.6f;
            physical2->mass = 5.0f;
            physical2->bearing_angle = physical->angle;
            rr_vector_from_polar(&physical2->velocity, 50, physical->angle);

            rr_component_petal_set_detached(
                rr_simulation_get_petal(simulation, petal_id), 1);

            rr_component_health_set_max_health(
                health, 8 *
                            RR_MOB_RARITY_SCALING[mob->rarity].health);
            rr_component_health_set_health(
                health, health->max_health);
            health->damage = 8 * RR_MOB_RARITY_SCALING[mob->rarity].damage;
            rr_simulation_get_petal(simulation, petal_id)->effect_delay = 50;

            struct rr_vector recoil;

            rr_vector_from_polar(&recoil, -5,
                                 physical->angle); // recoil
            rr_vector_add(&physical->acceleration, &recoil);
        }
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
    if (physical->stun_ticks > 0)
        return;
    struct rr_component_relations *relations =
        rr_simulation_get_relations(this, entity);
    if (ai->target_entity != RR_NULL_ENTITY &&
        !rr_simulation_entity_alive(simulation, ai->target_entity))
    {
        ai->target_entity = RR_NULL_ENTITY;
        ai->ai_state = rr_ai_state_idle;
        ai->ticks_until_next_action = 25;
    }
    if ((mob->player_spawned ||
        ai->ai_state == rr_ai_state_returning_to_owner))
    {
        if (!rr_simulation_entity_alive(simulation, relations->owner))
        {
            rr_simulation_request_entity_deletion(simulation, entity);
            return;
        }
        struct rr_component_physical *flower_physical =
            rr_simulation_get_physical(this, relations->owner);
        float dx = flower_physical->x - physical->x;
        float dy = flower_physical->y - physical->y;
        if ((ai->ai_state == rr_ai_state_returning_to_owner &&
             dx * dx + dy * dy >
                 (250 + physical->radius) * (250 + physical->radius)))
        {
            struct rr_vector accel = {dx, dy};
            rr_vector_set_magnitude(&accel, 2.5);
            rr_vector_add(&physical->acceleration, &accel);
            rr_component_physical_set_angle(physical, rr_vector_theta(&accel));
            ai->target_entity = RR_NULL_ENTITY;
            return;
        }
        else if (dx * dx + dy * dy >
                 (400 + physical->radius) * (400 + physical->radius))
        {
            ai->ai_state = rr_ai_state_returning_to_owner;
            struct rr_vector accel = {dx, dy};
            rr_vector_set_magnitude(&accel, 2.5);
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

    switch (mob->id)
    {
        case rr_mob_id_baby_ant:
            tick_ai_passive_default(entity, this);
            break;
        case rr_mob_id_worker_ant:
            tick_ai_neutral_default(entity, this, RR_BASE_PLAYER_SPEED * 0.95);
            break;
        case rr_mob_id_soldier_ant:
            tick_ai_aggro_default(entity, this, RR_BASE_PLAYER_SPEED * 0.95);
            break;
        case rr_mob_id_bee:
            if (mob->rarity < rr_rarity_id_rare)
                tick_ai_passive_default(entity, this);
            else
                tick_ai_neutral_default(entity, this, RR_BASE_PLAYER_SPEED * 0.95);
            break;
        case rr_mob_id_hornet:
            tick_ai_aggro_hornet(entity, this);
            break;
        case rr_mob_id_spider:
            tick_ai_aggro_default(entity, this, RR_BASE_PLAYER_SPEED * 1.2);
            break;
        case rr_mob_id_centipede:
            if (mob->rarity < rr_rarity_id_epic)
                tick_ai_passive_default(entity, this);
            else
                tick_ai_neutral_default(entity, this, RR_BASE_PLAYER_SPEED * 0.95);
            break;
        case rr_mob_id_ladybug:
            if (mob->rarity < rr_rarity_id_epic)
                tick_ai_passive_default(entity, this);
            else
                tick_ai_neutral_default(entity, this, RR_BASE_PLAYER_SPEED * 0.95);
            break;
        case rr_mob_id_evil_centipede:
            tick_ai_aggro_default(entity, this, RR_BASE_PLAYER_SPEED * 0.9);
            break;
        default: 
            break;
    //default:
        //RR_UNREACHABLE("invalid ai aggro type state");
        //break;
    }
    ai->ticks_until_next_action--;
}

void rr_system_ai_tick(struct rr_simulation *simulation)
{
    rr_simulation_for_each_ai(simulation, simulation, system_for_each);
}
