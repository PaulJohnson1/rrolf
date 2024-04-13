#include <Server/MobAi/Ai.h>

#include <math.h>

#include <Server/EntityAllocation.h>
#include <Server/EntityDetection.h>
#include <Server/Simulation.h>

void tick_ai_hybrid_default(EntityIdx entity, struct rr_simulation *simulation,
                            float speed, uint8_t rarity)
{
    struct rr_component_ai *ai = rr_simulation_get_ai(simulation, entity);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);
    struct rr_component_mob *mob = rr_simulation_get_mob(simulation, entity);
    uint8_t aggro = mob->rarity >= rarity;
    if ((aggro && has_new_target(ai, simulation)) || (!aggro &&
        rr_simulation_entity_alive(simulation, ai->target_entity) && ai_is_passive(ai)))
    {
        ai->ai_state = rr_ai_state_attacking;
        if (!aggro)
            ai->ticks_until_next_action = 25;
    }
    if (!aggro)
        mob->force_despawn = 1;

    switch (ai->ai_state)
    {
    case rr_ai_state_idle:
        tick_idle(entity, simulation);
        break;

    case rr_ai_state_idle_moving:
        tick_idle_move_default(entity, simulation);
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

void tick_ai_hybrid_triceratops(EntityIdx entity,
                                struct rr_simulation *simulation, uint8_t rarity)
{
    struct rr_component_ai *ai = rr_simulation_get_ai(simulation, entity);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);
    struct rr_component_mob *mob = rr_simulation_get_mob(simulation, entity);
    uint8_t aggro = mob->rarity >= rarity;
    if ((aggro && has_new_target(ai, simulation)) || (!aggro &&
        rr_simulation_entity_alive(simulation, ai->target_entity) && ai_is_passive(ai)))
    {
        ai->ai_state = rr_ai_state_waiting_to_attack;
        ai->ticks_until_next_action = 18;
    }
    if (!aggro)
        mob->force_despawn = 1;

    switch (ai->ai_state)
    {
    case rr_ai_state_idle:
        tick_idle(entity, simulation);
        break;

    case rr_ai_state_idle_moving:
        tick_idle_move_default(entity, simulation);
        break;
    case rr_ai_state_waiting_to_attack:
    {
        if (ai->ticks_until_next_action == 0)
        {
            ai->ai_state = rr_ai_state_attacking;
            ai->ticks_until_next_action = rand() % 25 + 63;
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
            ai->ticks_until_next_action = rand() % 12 + 12;
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
            physical, rr_angle_lerp(physical->angle, target_angle, 0.25));

        rr_vector_from_polar(&accel, RR_PLAYER_SPEED * 1.3, physical->angle);
        rr_vector_add(&physical->acceleration, &accel);
        break;
    }
    default:
        break;
    }
}

void tick_ai_hybrid_trex(EntityIdx entity, struct rr_simulation *simulation,
                         uint8_t rarity)
{
    struct rr_component_ai *ai = rr_simulation_get_ai(simulation, entity);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);
    struct rr_component_mob *mob = rr_simulation_get_mob(simulation, entity);
    uint8_t aggro = mob->rarity >= rarity;
    if ((aggro && has_new_target(ai, simulation)) || (!aggro &&
        rr_simulation_entity_alive(simulation, ai->target_entity) && ai_is_passive(ai)))
    {
        ai->ai_state = rr_ai_state_attacking;
        ai->ticks_until_next_action = 300;
    }
    if (!aggro)
        mob->force_despawn = 1;

    switch (ai->ai_state)
    {
    case rr_ai_state_idle:
        tick_idle(entity, simulation);
        break;

    case rr_ai_state_idle_moving:
        tick_idle_move_default(entity, simulation);
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

        rr_vector_from_polar(&accel, RR_PLAYER_SPEED * 1.05, physical->angle);
        rr_vector_add(&physical->acceleration, &accel);
        if (ai->ticks_until_next_action == 0)
        {
            if (rr_simulation_get_mob(simulation, entity)->rarity >=
                rr_rarity_id_exotic)
                ai->ai_state = rr_ai_state_exotic_special;
            ai->ticks_until_next_action = 15;
        }
        break;
    }
    case rr_ai_state_exotic_special:
    {
        if (ai->ticks_until_next_action == 0)
        {
            struct rr_component_mob *mob =
                rr_simulation_get_mob(simulation, entity);
            float angle = rr_frand() * M_PI + M_PI / 2;
            rr_simulation_alloc_mob(
                simulation, physical->arena,
                physical->x + physical->radius * cosf(angle),
                physical->y + physical->radius * sinf(angle), rr_mob_id_trex,
                mob->rarity - 2, rr_simulation_team_id_mobs);
            rr_simulation_alloc_mob(
                simulation, physical->arena,
                physical->x + physical->radius * cosf(2 * M_PI - angle),
                physical->y + physical->radius * sinf(2 * M_PI - angle),
                rr_mob_id_trex, mob->rarity - 2, rr_simulation_team_id_mobs);
            ai->ai_state = rr_ai_state_attacking;
            ai->ticks_until_next_action = 300;
        }
        break;
    }
    default:
        break;
    }
}

void tick_ai_hybrid_pteranodon(EntityIdx entity,
                               struct rr_simulation *simulation, uint8_t rarity)
{
    struct rr_component_ai *ai = rr_simulation_get_ai(simulation, entity);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);
    struct rr_component_mob *mob = rr_simulation_get_mob(simulation, entity);
    uint8_t aggro = mob->rarity >= rarity;
    if ((aggro && has_new_target(ai, simulation)) || (!aggro &&
        rr_simulation_entity_alive(simulation, ai->target_entity) && ai_is_passive(ai)))
        ai->ai_state = rr_ai_state_attacking;
    if (!aggro)
        mob->force_despawn = 1;

    switch (ai->ai_state)
    {
    case rr_ai_state_idle:
        tick_idle(entity, simulation);
        break;
    case rr_ai_state_idle_moving:
        tick_idle_move_default(entity, simulation);
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
                    (ai->has_prediction ||
                     rr_simulation_get_mob(simulation, entity)->rarity >=
                         rr_rarity_id_exotic) *
                        20); // make this less op
        rr_component_physical_set_angle(physical, rr_vector_theta(&prediction));
        if (rr_vector_magnitude_cmp(&delta, 500) == 1)
        {
            struct rr_vector accel;
            rr_vector_from_polar(&accel, RR_PLAYER_SPEED, physical->angle);
            rr_vector_add(&physical->acceleration, &accel);
        }
        if (ai->ticks_until_next_action == 0)
        {
            if (rr_simulation_get_mob(simulation, entity)->rarity >=
                    rr_rarity_id_exotic &&
                rr_frand() < 0.2)
            {
                ai->ai_state = rr_ai_state_exotic_special;
                ai->ticks_until_next_action = 75;
                break;
            }
            ai->ticks_until_next_action = 50;

            struct rr_component_mob *mob =
                rr_simulation_get_mob(simulation, entity);
            // spawn a shell
            EntityIdx petal_id = rr_simulation_alloc_petal(
                simulation, physical->arena, physical->x, physical->y,
                rr_petal_id_shell, mob->rarity, mob->parent_id);
            struct rr_component_physical *physical2 =
                rr_simulation_get_physical(simulation, petal_id);
            struct rr_component_health *health =
                rr_simulation_get_health(simulation, petal_id);
            rr_component_physical_set_angle(physical2, physical->angle);
            rr_component_physical_set_radius(
                physical2, 10 * RR_MOB_RARITY_SCALING[mob->rarity].radius);
            physical2->friction = 0.45f;
            physical2->mass = 5.0f;
            physical2->knockback_scale = 25;
            physical2->bearing_angle = physical->angle;
            rr_vector_from_polar(&physical2->velocity, 100, physical->angle);
            rr_component_petal_set_detached(
                rr_simulation_get_petal(simulation, petal_id), 1);
            rr_component_health_set_max_health(
                health, 5 * RR_MOB_RARITY_SCALING[mob->rarity].health);
            rr_component_health_set_health(health, health->max_health);
            health->damage = 10 * RR_MOB_RARITY_SCALING[mob->rarity].damage;
            rr_simulation_get_petal(simulation, petal_id)->effect_delay = 50;
            struct rr_vector recoil;
            rr_vector_from_polar(&recoil, -5,
                                 physical->angle); // recoil
            rr_vector_add(&physical->acceleration, &recoil);
        }
        break;
    }
    case rr_ai_state_exotic_special:
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
        if (ai->ticks_until_next_action < 50)
        {
            struct rr_vector accel;
            rr_vector_from_polar(&accel, RR_PLAYER_SPEED * 2, physical->angle);
            rr_vector_add(&physical->acceleration, &accel);
        }
        if (ai->ticks_until_next_action == 0)
        {
            ai->ai_state = rr_ai_state_attacking;
            ai->ticks_until_next_action = 50;
        }
        break;
    }
    default:
        break;
    }
}

void tick_ai_hybrid_pachycephalosaurus(EntityIdx entity,
                                       struct rr_simulation *simulation,
                                       uint8_t rarity)
{
    struct rr_component_ai *ai = rr_simulation_get_ai(simulation, entity);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);
    struct rr_component_mob *mob = rr_simulation_get_mob(simulation, entity);
    uint8_t aggro = mob->rarity >= rarity;
    if ((aggro && has_new_target(ai, simulation)) || (!aggro &&
        rr_simulation_entity_alive(simulation, ai->target_entity) && ai_is_passive(ai)))
        ai->ai_state = rr_ai_state_attacking;
    if (!aggro)
        mob->force_despawn = 1;

    switch (ai->ai_state)
    {
    case rr_ai_state_idle:
        tick_idle(entity, simulation);
        break;

    case rr_ai_state_idle_moving:
        tick_idle_move_default(entity, simulation);
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

        rr_component_physical_set_angle(physical, target_angle);

        rr_vector_from_polar(&accel, RR_PLAYER_SPEED, physical->angle);
        rr_vector_add(&physical->acceleration, &accel);
        ai->ticks_until_next_action = 25;
        if (rr_vector_magnitude_cmp(&delta, 350) == -1)
            ai->ai_state = rr_ai_state_charging;
        break;
    }
    case rr_ai_state_charging:
    {
        struct rr_vector accel;
        struct rr_component_physical *physical2 =
            rr_simulation_get_physical(simulation, ai->target_entity);

        rr_vector_from_polar(&accel, RR_PLAYER_SPEED * 1.8, physical->angle);
        rr_vector_add(&physical->acceleration, &accel);
        if (ai->ticks_until_next_action == 0)
        {
            ai->ticks_until_next_action = 25;
            ai->ai_state = rr_ai_state_attacking;
        }
        break;
    }
    default:
        break;
    }
}

void tick_ai_hybrid_ornithomimus(EntityIdx entity,
                                 struct rr_simulation *simulation, uint8_t rarity)
{
    struct rr_component_ai *ai = rr_simulation_get_ai(simulation, entity);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);
    struct rr_component_mob *mob = rr_simulation_get_mob(simulation, entity);
    uint8_t aggro = mob->rarity >= rarity;
    if ((aggro && has_new_target(ai, simulation)) || (!aggro &&
        rr_simulation_entity_alive(simulation, ai->target_entity) && ai_is_passive(ai)))
    {
        ai->ai_state = rr_ai_state_attacking;
        ai->ticks_until_next_action = -1;
    }
    if (!aggro)
        mob->force_despawn = 1;

    switch (ai->ai_state)
    {
    case rr_ai_state_idle:
        tick_idle(entity, simulation);
        break;

    case rr_ai_state_idle_moving:
        tick_idle_move_default(entity, simulation);
        break;
    case rr_ai_state_attacking:
    {
        struct rr_vector accel;
        struct rr_component_physical *physical2 =
            rr_simulation_get_physical(simulation, ai->target_entity);

        struct rr_vector delta = {physical2->x, physical2->y};
        struct rr_vector target_pos = {physical->x, physical->y};
        rr_vector_sub(&delta, &target_pos);
        if (aggro)
            physical->bearing_angle = rr_vector_theta(&delta);
        else
            physical->bearing_angle = rr_vector_theta(&delta) + M_PI;

        tick_idle_move_sinusoid(entity, simulation, RR_PLAYER_SPEED);
        break;
    }
    default:
        break;
    }
}

void tick_ai_hybrid_ankylosaurus(EntityIdx entity,
                                 struct rr_simulation *simulation, uint8_t rarity)
{
    struct rr_component_ai *ai = rr_simulation_get_ai(simulation, entity);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);
    struct rr_component_mob *mob = rr_simulation_get_mob(simulation, entity);
    uint8_t aggro = mob->rarity >= rarity;
    if ((aggro && has_new_target(ai, simulation)) || (!aggro &&
        rr_simulation_entity_alive(simulation, ai->target_entity) && ai_is_passive(ai)))
    {
        ai->ai_state = rr_ai_state_attacking;
        ai->ticks_until_next_action = 10;
    }
    if (!aggro)
        mob->force_despawn = 1;
    physical->knockback_scale = 1;

    switch (ai->ai_state)
    {
    case rr_ai_state_idle:
        tick_idle(entity, simulation);
        break;

    case rr_ai_state_idle_moving:
        tick_idle_move_default(entity, simulation);
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

        rr_component_physical_set_angle(physical, target_angle);

        rr_vector_from_polar(&accel, RR_PLAYER_SPEED * 1.1, physical->angle);
        rr_vector_add(&physical->acceleration, &accel);
        ai->ticks_until_next_action = 10;
        if (rr_vector_magnitude_cmp(&delta, 100 + physical->radius) == -1)
        {
            ai->ai_state = (rr_simulation_get_mob(simulation, entity)->rarity >=
                                rr_rarity_id_exotic &&
                            rr_frand() < 0.2)
                               ? rr_ai_state_exotic_special
                               : rr_ai_state_charging;
            ai->ticks_until_next_action = 25;
        }
        break;
    }
    case rr_ai_state_charging:
    {
        physical->knockback_scale = 25;
        struct rr_vector accel;
        struct rr_component_physical *physical2 =
            rr_simulation_get_physical(simulation, ai->target_entity);

        struct rr_vector delta = {physical2->x, physical2->y};
        struct rr_vector target_pos = {physical->x, physical->y};
        rr_vector_sub(&delta, &target_pos);
        float target_angle = rr_vector_theta(&delta);

        rr_component_physical_set_angle(physical, target_angle);

        rr_vector_from_polar(&accel, RR_PLAYER_SPEED * 1.8, physical->angle);
        rr_vector_add(&physical->acceleration, &accel);
        if (ai->ticks_until_next_action == 0)
        {
            ai->ticks_until_next_action = 10;
            ai->ai_state = rr_ai_state_attacking;
        }
        break;
    }
    case rr_ai_state_exotic_special:
    {
        physical->knockback_scale = 125;
        struct rr_vector accel;
        struct rr_component_physical *physical2 =
            rr_simulation_get_physical(simulation, ai->target_entity);

        struct rr_vector delta = {physical2->x, physical2->y};
        struct rr_vector target_pos = {physical->x, physical->y};
        rr_vector_sub(&delta, &target_pos);
        float target_angle = rr_vector_theta(&delta);

        rr_component_physical_set_angle(physical, target_angle + M_PI);

        rr_vector_from_polar(&accel, RR_PLAYER_SPEED * 3.0, physical->angle);
        rr_vector_add(&physical->acceleration, &accel);
        if (ai->ticks_until_next_action == 0)
        {
            ai->ticks_until_next_action = 10;
            ai->ai_state = rr_ai_state_attacking;
        }
        break;
    }
    default:
        break;
    }
}

void tick_ai_hybrid_quetzalcoaltus(EntityIdx entity,
                                   struct rr_simulation *simulation, uint8_t rarity)
{
    struct rr_component_ai *ai = rr_simulation_get_ai(simulation, entity);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);
    struct rr_component_mob *mob = rr_simulation_get_mob(simulation, entity);
    uint8_t aggro = mob->rarity >= rarity;
    if ((aggro && has_new_target(ai, simulation)) || (!aggro &&
        rr_simulation_entity_alive(simulation, ai->target_entity) && ai_is_passive(ai)))
        ai->ai_state = rr_ai_state_attacking;
    if (!aggro)
        mob->force_despawn = 1;

    switch (ai->ai_state)
    {
    case rr_ai_state_idle:
        tick_idle(entity, simulation);
        break;
    case rr_ai_state_idle_moving:
        tick_idle_move_default(entity, simulation);
        break;
    case rr_ai_state_attacking:
    {
        struct rr_component_physical *physical2 =
            rr_simulation_get_physical(simulation, ai->target_entity);

        struct rr_vector delta = {physical2->x, physical2->y};
        struct rr_vector target_pos = {physical->x, physical->y};
        rr_vector_sub(&delta, &target_pos);
        rr_component_physical_set_angle(physical, rr_vector_theta(&delta));
        if (ai->ticks_until_next_action == 0)
        {
            ai->ticks_until_next_action = 20;

            rr_vector_from_polar(&delta, RR_PLAYER_SPEED * 18, physical->angle);
            rr_vector_add(&physical->acceleration, &delta);
        }
        break;
    }
    default:
        break;
    }
}
