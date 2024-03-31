// Copyright (C) 2024  Paul Johnson

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.

// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

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
    EntityHash flower_id;
    uint8_t petal_rarity;
    float x;
    float y;
    float damage;
};

#ifdef RIVET_BUILD
#define URANIUM_RADIUS_FACTOR 1
#else
#define URANIUM_RADIUS_FACTOR 5
#endif

static void uranium_damage(EntityIdx mob, void *_captures)
{
    struct uranium_captures *captures = _captures;
    struct rr_simulation *simulation = captures->simulation;
    if (!rr_simulation_has_mob(simulation, mob))
        return;
    if (rr_simulation_get_relations(simulation, mob)->team ==
        rr_simulation_get_relations(simulation, captures->flower_id)->team)
        return;
    struct rr_component_health *health =
        rr_simulation_get_health(simulation, mob);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, mob);
    struct rr_vector delta = {physical->x - captures->x,
                              physical->y - captures->y};

    if (rr_vector_magnitude_cmp(&delta,
                                URANIUM_RADIUS_FACTOR *
                                    (100 + 75 * captures->petal_rarity)) == -1)
    {
        rr_component_health_do_damage(simulation, health, captures->flower_id,
                                      captures->damage);
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
        petal->effect_delay =
            RR_PETAL_DATA[rr_petal_id_uranium].secondary_cooldown;
        rr_component_health_set_flags(health, health->flags | 2);
        struct uranium_captures captures = {simulation,    relations->owner,
                                            petal->rarity, physical->x,
                                            physical->y,   health->damage};
        rr_spatial_hash_query(
            &rr_simulation_get_arena(simulation, physical->arena)->spatial_hash,
            physical->x, physical->y,
            URANIUM_RADIUS_FACTOR * (100 + 75 * captures.petal_rarity),
            URANIUM_RADIUS_FACTOR * (100 + 75 * captures.petal_rarity),
            &captures, uranium_damage);
    }
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
    ppetal->entity_hash = RR_NULL_ENTITY;
    ppetal->cooldown_ticks = petal_data->cooldown;
}

static EntityIdx squad_has_dead_player(struct rr_simulation *simulation,
                                       uint8_t squad)
{
    for (uint32_t i = 0; i < simulation->player_info_count; ++i)
    {
        struct rr_component_player_info *pl = rr_simulation_get_player_info(
            simulation, simulation->player_info_vector[i]);
        if (pl->flower_id == RR_NULL_ENTITY && pl->squad == squad)
            return pl->parent_id;
    }
    return RR_NULL_ENTITY;
}

static uint8_t is_close_enough_to_parent(struct rr_simulation *simulation,
                                         EntityIdx seeker, EntityIdx target,
                                         void *captures)
{
    struct rr_component_physical *parent_physical = captures;
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, target);
    return ((physical->x - parent_physical->x) *
                    (physical->x - parent_physical->x) +
                (physical->y - parent_physical->y) *
                    (physical->y - parent_physical->y) <
            250 * 250);
}

static uint8_t is_mob_and_damaged(struct rr_simulation *simulation,
                                  EntityIdx seeker, EntityIdx target,
                                  void *captures)
{
    if (!rr_simulation_has_mob(simulation, target))
        return 0;
    struct rr_component_health *health =
        rr_simulation_get_health(simulation, target);
    return health->max_health > health->health;
}

static uint8_t is_close_enough_and_angle(struct rr_simulation *simulation,
                                         EntityIdx seeker, EntityIdx target,
                                         void *captures)
{
    struct rr_component_physical *seeker_physical =
        rr_simulation_get_physical(simulation, seeker);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, target);
    struct rr_vector delta = {physical->x - seeker_physical->x,
                              physical->y - seeker_physical->y};
    if (rr_vector_magnitude_cmp(&delta, 750) == 1)
        return 0;
    return rr_angle_within(rr_vector_theta(&delta),
                           seeker_physical->bearing_angle, 1);
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
            petal->effect_delay = 75;
            physical->friction = 0.5;
            physical->bearing_angle = curr_angle;
            EntityIdx target = rr_simulation_find_nearest_enemy(
                simulation, id, 750, NULL, is_close_enough_and_angle);
            if (target != RR_NULL_ENTITY)
            {
                struct rr_component_physical *t_physical =
                    rr_simulation_get_physical(simulation, target);
                struct rr_vector delta = {t_physical->x - physical->x,
                                          t_physical->y - physical->y};
                physical->bearing_angle = rr_vector_theta(&delta);
            }
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
            rr_vector_from_polar(&physical->velocity, 50.0f, physical->angle);
            petal->effect_delay = 38;
            uint32_t count = petal_data->count[petal->rarity];
            for (uint32_t i = 1; i < count; ++i)
            {
                EntityIdx new_petal = rr_simulation_alloc_petal(
                    simulation, physical->arena, physical->x, physical->y,
                    petal->id, petal->rarity, flower_physical->parent_id);
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
                rr_simulation_get_petal(simulation, new_petal)->effect_delay =
                    38;
            }
            break;
        }
        case rr_petal_id_azalea:
        {
            struct rr_component_health *flower_health =
                rr_simulation_get_health(simulation, player_info->flower_id);
            float heal = 6 * RR_PETAL_RARITY_SCALE[petal->rarity].heal;
            if (flower_health->health < flower_health->max_health)
            {
                struct rr_vector delta = {
                    (flower_vector.x - position_vector.x),
                    (flower_vector.y - position_vector.y)};
                if (rr_vector_magnitude_cmp(&delta, flower_physical->radius +
                                                        physical->radius) == -1)
                {
                    rr_component_health_set_health(
                        flower_health, flower_health->health + heal);
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
                    if (rr_vector_magnitude_cmp(&delta, 200) == 1)
                        continue;
                    flower_health =
                        rr_simulation_get_health(simulation, potential);
                    if (flower_health->health == flower_health->max_health)
                        continue;
                    if (rr_vector_magnitude_cmp(&delta,
                                                target_physical->radius +
                                                    physical->radius) == -1)
                    {
                        rr_component_health_set_health(
                            flower_health, flower_health->health + heal);
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
                rr_vector_from_polar(&physical->acceleration, 7.5f, curr_angle);
                rr_vector_from_polar(&physical->velocity, 50.0f, curr_angle);
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
                    25 * RR_PETAL_RARITY_SCALE[petal->rarity].seed_cooldown;
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
        case rr_petal_id_mint:
        {
            EntityIdx mob_to_heal = rr_simulation_find_nearest_friend(
                simulation, id, 150, NULL, is_mob_and_damaged);
            if (mob_to_heal == RR_NULL_ENTITY)
                break;
            struct rr_component_physical *target_physical =
                rr_simulation_get_physical(simulation, mob_to_heal);
            struct rr_vector delta = {target_physical->x - physical->x,
                                      target_physical->y - physical->y};
            if (rr_vector_magnitude_cmp(&delta, target_physical->radius +
                                                    physical->radius) == -1)
            {
                struct rr_component_health *mob_health =
                    rr_simulation_get_health(simulation, mob_to_heal);
                float heal = 15 * RR_PETAL_RARITY_SCALE[petal->rarity].heal;
                rr_component_health_set_health(mob_health,
                                               mob_health->health + heal);
                rr_simulation_request_entity_deletion(simulation, id);
                return;
            }
            else
            {
                rr_vector_scale(&delta, 0.4);
                rr_vector_add(&physical->acceleration, &delta);
                return;
            }
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
        holdingRadius = 150 + player_info->modifiers.petal_extension;
    else if (player_info->input & 2)
        holdingRadius = 45;
    struct rr_vector chase_vector;
    rr_vector_from_polar(&chase_vector, holdingRadius, curr_angle);
    rr_vector_add(&chase_vector, &flower_vector);
    /*
    EntityIdx gravity_target = rr_simulation_find_nearest_enemy(simulation, id,
    50, flower_physical, is_close_enough_to_parent); if (gravity_target !=
    RR_NULL_ENTITY)
    {
        struct rr_component_physical *t_phys =
    rr_simulation_get_physical(simulation, gravity_target); chase_vector.x +=
    (t_phys->x - chase_vector.x) * 0.8; chase_vector.y += (t_phys->y -
    chase_vector.y) * 0.8;
    }
    */
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
        physical,
        physical->angle + 0.04f * petal->spin_ccw * (1 - petal->no_rotation));
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
    player_info->modifiers.petal_extension = 0;

    physical->aggro_range_multiplier = 1;
    health->damage_reduction = 0;
    uint8_t rot_count = 0;
    float bone_diminish_factor = 1;
    float feather_diminish_factor = 1.5;
    rr_component_player_info_set_camera_fov(player_info, RR_BASE_FOV);
    float to_rotate = 0.1;
    for (uint64_t outer = 0; outer < player_info->slot_count; ++outer)
    {
        struct rr_component_player_info_petal_slot *slot =
            &player_info->slots[outer];
        struct rr_petal_data const *data = &RR_PETAL_DATA[slot->id];
        if (data->id == rr_petal_id_leaf)
            rr_component_health_set_health(
                health, health->health +
                            0.05 * RR_PETAL_RARITY_SCALE[slot->rarity].heal);
        else if (data->id == rr_petal_id_light)
            to_rotate += (0.012 + 0.008 * slot->rarity);
        else if (data->id == rr_petal_id_feather)
        {
            physical->acceleration_scale +=
                (0.05 + 0.025 * slot->rarity) * feather_diminish_factor;
            feather_diminish_factor *= 0.5;
        }
        else if (data->id == rr_petal_id_crest)
        {
            rr_component_flower_set_face_flags(flower, flower->face_flags | 8);
            RR_SET_IF_LESS(player_info->camera_fov, 1 - 0.1 * slot->rarity)
        }
        else if (data->id == rr_petal_id_droplet)
            ++rot_count;
        else if (data->id == rr_petal_id_third_eye)
        {
            rr_component_flower_set_face_flags(flower, flower->face_flags | 16);
            RR_SET_IF_GREATER(player_info->modifiers.petal_extension,
                              35 * (slot->rarity - rr_rarity_id_epic))
        }
        else if (data->id == rr_petal_id_bone)
        {
            health->damage_reduction +=
                1.75 * RR_PETAL_RARITY_SCALE[slot->rarity].heal *
                bone_diminish_factor;
            bone_diminish_factor *= 0.5;
        }
        else
        {
            for (uint32_t inner = 0; inner < slot->count; ++inner)
            {
                if (slot->petals[inner].entity_hash == RR_NULL_ENTITY)
                    continue;
                if (data->id == rr_petal_id_magnet)
                    RR_SET_IF_GREATER(player_info->modifiers.drop_pickup_radius,
                                      50 + 180 * slot->rarity)
            }
        }
    }
    player_info->global_rotation +=
        to_rotate * ((rot_count % 3) ? (rot_count % 3 == 2) ? 0 : -1 : 1);
}

static void rr_system_petal_reload_foreach_function(EntityIdx id,
                                                    void *simulation)
{
    struct rr_component_player_info *player_info =
        rr_simulation_get_player_info(simulation, id);
    if (!rr_simulation_entity_alive(simulation, player_info->flower_id))
        return;
    struct rr_component_physical *flower_physical =
        rr_simulation_get_physical(simulation, player_info->flower_id);
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
            if (p_petal->entity_hash != RR_NULL_ENTITY &&
                !rr_simulation_entity_alive(simulation, p_petal->entity_hash))
            {
                p_petal->entity_hash = RR_NULL_ENTITY;
                p_petal->cooldown_ticks = data->cooldown;
            }
            if (p_petal->entity_hash == RR_NULL_ENTITY)
            {
                float cd = rr_fclamp(
                    255.0f * p_petal->cooldown_ticks / data->cooldown, 0, 255);
                if (cd > max_cd)
                    max_cd = cd;
                if (--p_petal->cooldown_ticks <= 0)
                    p_petal->entity_hash = rr_simulation_get_entity_hash(
                        simulation,
                        rr_simulation_alloc_petal(
                            simulation, player_info->arena, flower_physical->x,
                            flower_physical->y, slot->id, slot->rarity,
                            player_info->flower_id));
            }
            else
            {
                if (rr_simulation_get_physical(simulation, p_petal->entity_hash)
                        ->arena != player_info->arena)
                {
                    rr_simulation_request_entity_deletion(simulation,
                                                          p_petal->entity_hash);
                    continue;
                }
                if (rr_simulation_has_mob(simulation, p_petal->entity_hash))
                {
                    if (inner == 0 || data->clump_radius == 0)
                        --rotation_pos;
                    continue;
                }
                system_flower_petal_movement_logic(
                    simulation, p_petal->entity_hash, player_info,
                    rotation_pos - 1, outer, inner, data);
                if (data->id == rr_petal_id_egg)
                {
                    struct rr_component_petal *petal = rr_simulation_get_petal(
                        simulation, p_petal->entity_hash);
                    if (petal->effect_delay > 0)
                        continue;
                    rr_component_petal_set_detached(petal, 1);
                    struct rr_component_physical *petal_physical =
                        rr_simulation_get_physical(simulation,
                                                   p_petal->entity_hash);
                    rr_simulation_request_entity_deletion(simulation,
                                                          p_petal->entity_hash);
                    p_petal->entity_hash = RR_NULL_ENTITY;
                    if (petal->rarity == 0)
                        return;
                    uint8_t m_id, m_rar;
                    if (data->id == rr_petal_id_egg)
                    {
                        m_id = rr_mob_id_meteor;
                        m_rar = petal->rarity >= 1 ? petal->rarity - 1 : 0;
                    }
                    EntityIdx mob_id = rr_simulation_alloc_mob(
                        simulation, petal_physical->arena, petal_physical->x,
                        petal_physical->y, m_id, m_rar,
                        rr_simulation_get_relations(simulation,
                                                    player_info->flower_id)
                            ->team);
                    p_petal->entity_hash =
                        rr_simulation_get_entity_hash(simulation, mob_id);
                    struct rr_component_relations *relations =
                        rr_simulation_get_relations(simulation, mob_id);
                    rr_component_relations_set_owner(
                        relations, rr_simulation_get_entity_hash(
                                       simulation, player_info->flower_id));
                    rr_component_relations_update_root_owner(simulation,
                                                             relations);
                    rr_simulation_get_mob(simulation, mob_id)->player_spawned =
                        1;
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
            EntityHash player_info = relations->root_owner;
            if (!rr_simulation_entity_alive(simulation, player_info))
                rr_simulation_request_entity_deletion(simulation, id);
            if (!squad_has_dead_player(
                    simulation,
                    rr_simulation_get_player_info(simulation, player_info)
                        ->squad))
                rr_simulation_request_entity_deletion(simulation, id);
        }
        if (--petal->effect_delay <= 0)
        {
            rr_simulation_request_entity_deletion(simulation, id);
            if (petal->id == rr_petal_id_seed)
            {
                EntityIdx player_info =
                    rr_simulation_get_relations(simulation, relations->owner)
                        ->owner;
                EntityIdx to_rev = squad_has_dead_player(
                    simulation,
                    rr_simulation_get_player_info(simulation, player_info)
                        ->squad);
                if (to_rev == RR_NULL_ENTITY)
                    return;
                EntityIdx flower = rr_simulation_alloc_player(
                    simulation, physical->arena, to_rev);
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
