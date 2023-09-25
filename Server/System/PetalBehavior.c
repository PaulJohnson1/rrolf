#include <Server/System/System.h>

#include <math.h>
#include <stdio.h>

#include <Server/EntityAllocation.h>
#include <Server/EntityDetection.h>
#include <Server/Simulation.h>

#include <Shared/Entity.h>
#include <Shared/StaticData.h>
#include <Shared/Utilities.h>
#include <Shared/Vector.h>

struct uranium_captures
{
    struct rr_simulation *simulation;
    EntityIdx flower_id;
    float x;
    float y;
    float damage;
};

static void uranium_damage(EntityIdx mob, void *_captures)
{
    struct uranium_captures *captures = _captures;
    struct rr_simulation *simulation = captures->simulation;
    if (rr_simulation_get_relations(simulation, mob)->team ==
        rr_simulation_team_id_players)
        return;
    struct rr_component_health *health =
        rr_simulation_get_health(simulation, mob);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, mob);
    if ((physical->x - captures->x) * (physical->x - captures->x) +
            (physical->y - captures->y) * (physical->y - captures->y) <
        901 * 901)
    {
        rr_component_health_do_damage(simulation, health, captures->flower_id, captures->damage);
        // health->damage_paused = 5;
        struct rr_component_ai *ai = rr_simulation_get_ai(simulation, mob);
        if (ai->target_entity == RR_NULL_ENTITY)
            ai->target_entity = captures->flower_id;
    }
}

static void uranium_petal_system(struct rr_simulation *simulation,
                                 struct rr_component_petal *petal)
{
    if (petal->effect_delay == 0)
    {
        struct rr_component_relations *relations =
            rr_simulation_get_relations(simulation, petal->parent_id);
        struct rr_component_health *health =
            rr_simulation_get_health(simulation, petal->parent_id);
        struct rr_component_physical *physical =
            rr_simulation_get_physical(simulation, petal->parent_id);
        if (!rr_simulation_entity_alive(simulation, relations->owner))
            return;
        struct rr_component_physical *flower_physical =
            rr_simulation_get_physical(simulation, relations->owner);
        struct rr_component_health *flower_health =
            rr_simulation_get_health(simulation, relations->owner);
        rr_component_health_set_health(flower_health, flower_health->health -
                                                          health->damage);
        petal->effect_delay = 25;
        struct uranium_captures captures = {simulation, relations->owner,
                                            physical->x, physical->y,
                                            health->damage};
        rr_simulation_for_each_mob(simulation, &captures, uranium_damage);
    }
}

struct lightning_captures
{
    EntityIdx *chain;
    uint32_t length;
    float curr_x;
    float curr_y;
};

static uint8_t lightning_filter(struct rr_simulation *simulation, EntityIdx seeker, EntityIdx target, void *captures)
{
    struct lightning_captures *chain = captures;
    for (uint32_t i = 0; i < chain->length; ++i)
    {
        if (chain->chain[i] == target)
            return 0;
    }
    return 1;
}

static void lightning_petal_system(struct rr_simulation *simulation,
                                 struct rr_component_petal *petal)
{
    if (petal->effect_delay == 0)
    {
        struct rr_component_physical *petal_physical = rr_simulation_get_physical(simulation, petal->parent_id);
        struct rr_component_relations *relations = rr_simulation_get_relations(simulation, petal->parent_id);
        struct rr_simulation_animation *animation = &simulation->animations[simulation->animation_length++];
        animation->type = 1;
        EntityIdx chain[16] = {petal->parent_id};
        animation->points[0].x = petal_physical->x;
        animation->points[0].y = petal_physical->y;
        uint32_t chain_amount = petal->rarity + 1;   
        float damage = rr_simulation_get_health(simulation, petal->parent_id)->damage * 0.5; 
        EntityIdx target = RR_NULL_ENTITY;
        struct lightning_captures captures = {chain, 1, petal_physical->x, petal_physical->y};
        for (; captures.length < chain_amount + 1; ++captures.length)
        {
            target = rr_simulation_find_nearest_enemy_custom_pos(simulation, petal->parent_id, captures.curr_x, captures.curr_y, 400, &captures, lightning_filter);
            if (target == RR_NULL_ENTITY)
                break;
            if (rr_simulation_has_ai(simulation, target))
            {
                struct rr_component_ai *ai = rr_simulation_get_ai(simulation, target);
                if (ai->target_entity == RR_NULL_ENTITY)
                    ai->target_entity = relations->owner;
            }
            struct rr_component_physical *physical = rr_simulation_get_physical(simulation, target);
            struct rr_component_health *health = rr_simulation_get_health(simulation, target);
            rr_component_health_do_damage(simulation, health, petal->parent_id, damage);
            health->damage_paused = 5;
            physical->stun_ticks = 10;
            chain[captures.length] = target;
            animation->points[captures.length].x = physical->x;
            animation->points[captures.length].y = physical->y;
            captures.curr_x = physical->x;
            captures.curr_y = physical->y;
        }
        animation->length = captures.length;
        if (captures.length > 1)
            rr_simulation_request_entity_deletion(simulation, petal->parent_id);
        else
            --simulation->animation_length;
    }
    else
        --petal->effect_delay;
}

static void system_petal_detach(struct rr_simulation *simulation,
                                struct rr_component_petal *petal,
                                struct rr_component_player_info *player_info,
                                uint32_t outer_pos, uint32_t inner_pos,
                                struct rr_petal_data const *petal_data)
{
    rr_component_petal_set_detached(petal, 1);
    struct rr_component_player_info_petal *ppetal =
        &player_info->slots[outer_pos].petals[inner_pos];
    ppetal->simulation_id = RR_NULL_ENTITY;
    ppetal->cooldown_ticks = petal_data->cooldown;
}

static EntityIdx squad_has_dead_player(struct rr_simulation *simulation, uint8_t squad)
{
    for (uint32_t i = 0; i < simulation->player_info_count; ++i)
    {
        struct rr_component_player_info *pl = rr_simulation_get_player_info(simulation, simulation->player_info_vector[i]);
        if (pl->flower_id == RR_NULL_ENTITY && pl->squad == squad)
            return pl->parent_id; 
    }
    return RR_NULL_ENTITY;
}

static void system_flower_petal_movement_logic(
    struct rr_simulation *simulation, EntityIdx id,
    struct rr_component_player_info *player_info, uint32_t rotation_pos,
    uint32_t outer_pos, uint32_t inner_pos,
    struct rr_petal_data const *petal_data)
{
    struct rr_component_petal *petal = rr_simulation_get_petal(simulation, id);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, id);
    struct rr_component_physical *flower_physical =
        rr_simulation_get_physical(simulation, player_info->flower_id);
    struct rr_vector position_vector = {physical->x, physical->y};
    struct rr_vector flower_vector = {flower_physical->x, flower_physical->y};
    float curr_angle = player_info->global_rotation +
                       rotation_pos * 2 * M_PI / player_info->rotation_count;
    
    if (petal->effect_delay == 0)
    {
        switch (petal->id)
        {
        case rr_petal_id_shell:
        {
            if ((player_info->input & 1) == 0)
                break;
            system_petal_detach(simulation, petal, player_info, outer_pos,
                                inner_pos, petal_data);
            rr_vector_from_polar(&physical->acceleration, 15.0f,
                                    curr_angle);
            petal->effect_delay = 75;
            rr_simulation_get_health(simulation, id)->damage =
                25 * RR_PETAL_RARITY_SCALE[petal->rarity].damage;
            physical->friction = 0.5;
            physical->bearing_angle = curr_angle;
            break;
        }
        case rr_petal_id_peas:
        {
            if ((player_info->input & 1) == 0)
                break;
            system_petal_detach(simulation, petal, player_info, outer_pos,
                                inner_pos, petal_data);
            rr_vector_from_polar(&physical->acceleration, 4.0f,
                                    physical->angle);
            rr_vector_from_polar(&physical->velocity, 50.0f,
                                    physical->angle);
            petal->effect_delay = 15;
            uint32_t count = petal_data->count[petal->rarity];
            for (uint32_t i = 1; i < count; ++i)
            {
                EntityIdx new_petal = rr_simulation_alloc_petal(
                    simulation, physical->arena, physical->x, physical->y, petal->id, petal->rarity,
                    flower_physical->parent_id);
                struct rr_component_physical *new_physical =
                    rr_simulation_get_physical(simulation, new_petal);
                rr_component_physical_set_angle(
                    new_physical, physical->angle + i * 2 * M_PI / count);
                rr_vector_from_polar(&new_physical->acceleration, 4.0f,
                                        new_physical->angle);
                rr_vector_from_polar(&new_physical->velocity, 50.0f,
                                        new_physical->angle);
                rr_component_petal_set_detached(
                    rr_simulation_get_petal(simulation, new_petal), 1);
                rr_simulation_get_petal(simulation, new_petal)->effect_delay = 15;
            }
            break;
        }
        case rr_petal_id_azalea:
        {
            struct rr_component_health *flower_health =
                rr_simulation_get_health(simulation,
                                            player_info->flower_id);
            if (flower_health->health < flower_health->max_health)
            {
                struct rr_vector delta = {
                    (flower_vector.x - position_vector.x),
                    (flower_vector.y - position_vector.y)};
                if (rr_vector_get_magnitude(&delta) <
                    flower_physical->radius + physical->radius)
                {
                    // heal
                    rr_component_health_set_health(
                        flower_health,
                        flower_health->health +
                            10 * RR_PETAL_RARITY_SCALE[petal->rarity]
                                        .damage);
                    rr_simulation_request_entity_deletion(simulation, id);
                    return;
                }
                else
                {
                    rr_vector_scale(&delta, 0.4);
                    rr_vector_add(&physical->acceleration, &delta);
                    return;
                }
            }
            else
            {
                for (uint32_t i = 0; i < simulation->flower_count; ++i)
                {
                    EntityIdx potential = simulation->flower_vector[i];
                    struct rr_component_physical *target_physical =
                        rr_simulation_get_physical(simulation, potential);
                    struct rr_vector delta = {
                        (target_physical->x - position_vector.x),
                        (target_physical->y - position_vector.y)};
                    if (rr_vector_get_magnitude(&delta) > 200)
                        continue;
                    flower_health =
                        rr_simulation_get_health(simulation, potential);
                    if (flower_health->health == flower_health->max_health)
                        continue;
                    if (rr_vector_get_magnitude(&delta) <
                        target_physical->radius + physical->radius)
                    {
                        // heal
                        rr_component_health_set_health(
                            flower_health,
                            flower_health->health +
                                10 * RR_PETAL_RARITY_SCALE[petal->rarity]
                                            .damage);
                        rr_simulation_request_entity_deletion(simulation,
                                                                id);
                        return;
                    }
                    else
                    {
                        rr_vector_scale(&delta, 0.5);
                        rr_vector_add(&physical->acceleration, &delta);
                        return;
                    }
                }
            }
            break;
        }
        case rr_petal_id_web:
        {
            if ((player_info->input & 3) == 0)
                break;
            system_petal_detach(simulation, petal, player_info, outer_pos,
                                inner_pos, petal_data);
            if (player_info->input & 1)
            {
                rr_vector_from_polar(&physical->acceleration, 7.5f,
                                        curr_angle);
                rr_vector_from_polar(&physical->velocity, 50.0f,
                                        curr_angle);
            }
            petal->effect_delay = 20;
            break;
        }
        case rr_petal_id_seed:
        {
            if (petal->detached)
                return;
            if (squad_has_dead_player(simulation, player_info->squad))
            {
                petal->effect_delay =
                    6000 / RR_PETAL_RARITY_SCALE[petal->rarity].damage;
                rr_component_petal_set_detached(petal, 1);
            }
            break;
        }
        case rr_petal_id_gravel:
        {
            if ((player_info->input & 3) == 0)
                break;
            system_petal_detach(simulation, petal, player_info, outer_pos,
                                inner_pos, petal_data);
            petal->effect_delay = 125;
            physical->friction = 0.4;
            break;
        }
        default:
            break;
        }
    }
    else if (!petal->detached)
        --petal->effect_delay;
    else
        return;

    float holdingRadius = 75;
    uint8_t should_extend = player_info->input & 1 && !petal->no_rotation &&
        petal_data->id != rr_petal_id_uranium &&
        petal_data->id != rr_petal_id_magnet &&
        petal_data->id != rr_petal_id_bone;
    if (petal->id == rr_petal_id_gravel && petal->detached)
        should_extend = player_info->input & 1;
    if (should_extend)
        holdingRadius = 150;
    else if (player_info->input & 2)
        holdingRadius = 45;
    struct rr_vector chase_vector;
    rr_vector_from_polar(&chase_vector, holdingRadius, curr_angle);
    rr_vector_add(&chase_vector, &flower_vector);
    rr_vector_sub(&chase_vector, &position_vector);
    if (petal_data->clump_radius != 0.0f &&
        petal_data->count[petal->rarity] != 1)
    {
        curr_angle = 1.333 * curr_angle +
                     2 * M_PI * inner_pos / petal_data->count[petal->rarity];
        struct rr_vector clump_vector;
        rr_vector_from_polar(&clump_vector, petal_data->clump_radius,
                             curr_angle);
        rr_vector_add(&chase_vector, &clump_vector);
    }
    if (petal->id == rr_petal_id_light)
    {
        struct rr_vector random_vector;
        rr_vector_from_polar(&random_vector, 10.0f, rr_frand() * M_PI * 2);
        rr_vector_add(&chase_vector, &random_vector);
    }
    rr_component_physical_set_angle(
        physical, physical->angle + 0.04f * petal->spin_ccw * (1 - petal->no_rotation));
    physical->acceleration.x += 0.5f * chase_vector.x;
    physical->acceleration.y += 0.5f * chase_vector.y;
}

static void petal_modifiers(struct rr_simulation *simulation,
                            struct rr_component_player_info *player_info)
{
    struct rr_component_flower *flower =
        rr_simulation_get_flower(simulation, player_info->flower_id);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, player_info->flower_id);
    struct rr_component_health *health =
        rr_simulation_get_health(simulation, player_info->flower_id);
    rr_component_flower_set_face_flags(flower, player_info->input);
    // reset
    physical->acceleration_scale = 1;
    player_info->modifiers.drop_pickup_radius = 25;

    physical->aggro_range_multiplier = 1;
    health->damage_reduction = 0;
    uint8_t rot_count = 0;
    rr_component_player_info_set_camera_fov(player_info, RR_BASE_FOV);
    float to_rotate = 0.1;
    for (uint64_t outer = 0; outer < player_info->slot_count; ++outer)
    {
        struct rr_component_player_info_petal_slot *slot =
            &player_info->slots[outer];
        struct rr_petal_data const *data = &RR_PETAL_DATA[slot->id];
        if (data->id == rr_petal_id_leaf)
        {
            rr_component_health_set_health(
                health, health->health +
                            0.04 * RR_PETAL_RARITY_SCALE[slot->rarity].damage);
        }
        else if (data->id == rr_petal_id_light)
            to_rotate += (0.012 + 0.008 * slot->rarity);
        else if (data->id == rr_petal_id_feather)
        {
            float speed = 1 + 0.04 + 0.025 * slot->rarity;
            if (slot->rarity == rr_rarity_id_ultra)
                speed = 5;
            if (speed > physical->acceleration_scale)
                physical->acceleration_scale = speed;
        }
        else if (data->id == rr_petal_id_crest)
        {
            rr_component_flower_set_face_flags(flower, flower->face_flags | 8);
            if (physical->aggro_range_multiplier < 1.1 + (0.15 * slot->rarity))
                physical->aggro_range_multiplier = 1.1 + (0.15 * slot->rarity);
        }
        else if (data->id == rr_petal_id_droplet)
        {
           ++rot_count;
        }
        else if (data->id == rr_petal_id_third_eye)
        {
            rr_component_flower_set_face_flags(flower, flower->face_flags | 16);
            if (player_info->camera_fov > RR_BASE_FOV * (0.9 - 0.07 * slot->rarity))
            {   
                rr_component_player_info_set_camera_fov(player_info, RR_BASE_FOV * (0.9 - 0.07 * slot->rarity));
            }
        }
        else
            for (uint32_t inner = 0; inner < slot->count; ++inner)
            {
                if (slot->petals[inner].simulation_id == RR_NULL_ENTITY)
                    continue;
                if (data->id == rr_petal_id_magnet)
                {
                    if (player_info->modifiers.drop_pickup_radius < 75 + 30 * RR_PETAL_RARITY_SCALE[slot->rarity].health)
                        player_info->modifiers.drop_pickup_radius = 75 + 30 * RR_PETAL_RARITY_SCALE[slot->rarity].health;
                }
                if (data->id == rr_petal_id_bone)
                    health->damage_reduction +=
                        2.5 * RR_PETAL_RARITY_SCALE[slot->rarity].health;
            }
    }
    player_info->global_rotation += to_rotate * ((rot_count % 3) ? (rot_count % 3 == 2) ? 0 : -1 : 1);
}

static void rr_system_petal_reload_foreach_function(EntityIdx id,
                                                    void *simulation)
{
    struct rr_component_player_info *player_info =
        rr_simulation_get_player_info(simulation, id);
    if (player_info->flower_id == RR_NULL_ENTITY)
        return;
    petal_modifiers(simulation, player_info);
    uint32_t rotation_pos = 0;
    for (uint64_t outer = 0; outer < player_info->slot_count; ++outer)
    {
        struct rr_component_player_info_petal_slot *slot =
            &player_info->slots[outer];
        struct rr_petal_data const *data = &RR_PETAL_DATA[slot->id];
        uint8_t max_cd = 0;
        slot->count = slot->id == rr_petal_id_peas
                          ? 1
                          : RR_PETAL_DATA[slot->id].count[slot->rarity];
        for (uint64_t inner = 0; inner < slot->count; ++inner)
        {
            if (inner == 0 || data->clump_radius == 0)
                ++rotation_pos; // clump rotpos ++
            struct rr_component_player_info_petal *p_petal =
                &slot->petals[inner];
            if (p_petal->simulation_id != RR_NULL_ENTITY &&
                !rr_simulation_entity_alive(simulation,
                                           p_petal->simulation_id))
            {
                p_petal->simulation_id = RR_NULL_ENTITY;
                p_petal->cooldown_ticks = data->cooldown;
            }
            if (p_petal->simulation_id == RR_NULL_ENTITY)
            {
                float cd =
                    ((float)p_petal->cooldown_ticks / data->cooldown) * 255;
                if (cd > max_cd)
                {
                    if (cd > 255)
                        cd = 255;
                    max_cd = (uint8_t)cd;
                }
                if (--p_petal->cooldown_ticks <= 0)
                {
                    p_petal->simulation_id = rr_simulation_alloc_petal(
                        simulation, player_info->arena, player_info->camera_x, player_info->camera_y, slot->id, slot->rarity,
                        player_info->flower_id);
                }
            }
            else
            {
                if (rr_simulation_has_mob(simulation, p_petal->simulation_id))
                {
                    if (inner == 0 || data->clump_radius == 0)
                        --rotation_pos; // clump rotpos --
                    continue;           // player spawned mob
                }
                system_flower_petal_movement_logic(
                    simulation, p_petal->simulation_id, player_info,
                    rotation_pos - 1, outer, inner, data);
                if (data->id == rr_petal_id_egg)
                {
                    struct rr_component_petal *petal = rr_simulation_get_petal(
                        simulation, p_petal->simulation_id);
                    if (petal->effect_delay > 0)
                        continue;
                    rr_component_petal_set_detached(petal, 1);
                    struct rr_component_physical *petal_physical =
                        rr_simulation_get_physical(simulation,
                                                   p_petal->simulation_id);
                    rr_simulation_request_entity_deletion(
                        simulation, p_petal->simulation_id);
                    p_petal->simulation_id = RR_NULL_ENTITY;
                    if (petal->rarity == 0)
                        return;
                    uint8_t m_id, m_rar;
                    if (data->id == rr_petal_id_egg)
                    {
                        m_id = rr_mob_id_trex;
                        m_rar = petal->rarity ? petal->rarity - 1 : 0;
                    }
                    EntityIdx mob_id = p_petal->simulation_id =
                        rr_simulation_alloc_mob(simulation, petal_physical->arena, petal_physical->x, petal_physical->y, m_id, m_rar,
                                                rr_simulation_team_id_players);
                    struct rr_component_relations *relations =
                        rr_simulation_get_relations(simulation, mob_id);
                    rr_component_relations_set_owner(relations,
                                                     player_info->flower_id);
                    rr_simulation_get_mob(simulation, mob_id)->player_spawned = 1;
                }
            }
        }
        rr_component_player_info_set_slot_cd(player_info, outer, max_cd);
    }
    player_info->rotation_count = rotation_pos;
}

static void system_petal_misc_logic(EntityIdx id, void *_simulation)
{
    struct rr_simulation *simulation = _simulation;
    struct rr_component_petal *petal = rr_simulation_get_petal(simulation, id);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, id);
    struct rr_component_relations *relations =
        rr_simulation_get_relations(simulation, id);
    if (!rr_simulation_entity_alive(simulation, relations->owner))
    {
        rr_simulation_request_entity_deletion(simulation, id);
        return;
    }
    if (petal->detached == 0) // it's mob owned if this is true
    {
        if (petal->id == rr_petal_id_uranium)
            uranium_petal_system(simulation, petal);
        else if (petal->id == rr_petal_id_lightning)
            lightning_petal_system(simulation, petal);
        if (!rr_simulation_has_mob(simulation, relations->owner))
            return;
        if (--petal->effect_delay == 0)
            rr_simulation_request_entity_deletion(simulation, id);
        // check if owner is a mob
        return; // no logic yet
    }
    else
    {
        if (petal->id == rr_petal_id_shell)
        {
            if (relations->team == rr_simulation_team_id_players)
            {
                EntityIdx target = rr_simulation_find_nearest_enemy(simulation, id, 500, NULL, no_filter);
                if (target != RR_NULL_ENTITY)
                {
                    struct rr_component_physical *mob_physical = rr_simulation_get_physical(simulation, target);
                    struct rr_vector delta = {mob_physical->x - physical->x, mob_physical->y - physical->y};
                    physical->bearing_angle = rr_angle_lerp(physical->bearing_angle, rr_vector_theta(&delta), 0.01 * RR_PETAL_RARITY_SCALE[petal->rarity].damage);
                }
            }
            rr_component_physical_set_angle(
                physical, physical->angle + 0.12f * (float)petal->spin_ccw);
            rr_vector_from_polar(&physical->acceleration, 15.0f,
                                 physical->bearing_angle);
        }
        else if (petal->id == rr_petal_id_peas)
            rr_vector_from_polar(&physical->acceleration, 7.5f,
                                 physical->angle);
        else if (petal->id == rr_petal_id_seed)
        {
            EntityIdx player_info = rr_simulation_get_relations(simulation, relations->owner)->owner;
            if (!rr_simulation_entity_alive(simulation, player_info))
                rr_simulation_request_entity_deletion(simulation, id);
            if (!squad_has_dead_player(simulation, rr_simulation_get_player_info(simulation, player_info)->squad))
                rr_simulation_request_entity_deletion(simulation, id);
        }
        if (--petal->effect_delay <=
            0)
        {
            rr_simulation_request_entity_deletion(simulation, id);
            if (petal->id == rr_petal_id_seed)
            {
                EntityIdx player_info = rr_simulation_get_relations(simulation, relations->owner)->owner;
                EntityIdx to_rev = squad_has_dead_player(simulation, rr_simulation_get_player_info(simulation, player_info)->squad);
                if (to_rev == RR_NULL_ENTITY)
                    return;
                EntityIdx flower = rr_simulation_alloc_player(simulation, physical->arena, to_rev);
                struct rr_component_physical *flower_physical =
                    rr_simulation_get_physical(simulation, flower);
                rr_component_physical_set_x(flower_physical, physical->x);
                rr_component_physical_set_y(flower_physical, physical->y);
            }
        }
    }
}

void rr_system_petal_behavior_tick(struct rr_simulation *simulation)
{
    rr_simulation_for_each_player_info(simulation, simulation,
                                       rr_system_petal_reload_foreach_function);
    rr_simulation_for_each_petal(simulation, simulation,
                                 system_petal_misc_logic);
}
