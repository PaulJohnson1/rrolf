#include <Server/System/PetalBehavior.h>

#include <math.h>
#include <stdio.h>

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
    if (rr_simulation_get_relations(simulation, mob)->team == rr_simulation_team_id_players)
        return;
    struct rr_component_health *health =
        rr_simulation_get_health(simulation, mob);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, mob);
    if ((physical->x - captures->x) * (physical->x - captures->x) +
            (physical->y - captures->y) * (physical->y - captures->y) <
        901 * 901)
    {
        rr_component_health_do_damage(health, captures->damage);
        rr_component_physical_set_server_animation_tick(physical, 5);
        // health->damage_paused = 5;
        struct rr_component_ai *ai = rr_simulation_get_ai(simulation, mob);
        if (ai->target_entity == RR_NULL_ENTITY)
            ai->target_entity = captures->flower_id;
    }
}

static void uranium_petal_system(struct rr_simulation *simulation,
                                 struct rr_component_petal *petal)
{
    if (--petal->effect_delay == 0)
    {
        struct rr_component_relations *relations =
            rr_simulation_get_relations(simulation, petal->parent_id);
        struct rr_component_health *health =
            rr_simulation_get_health(simulation, petal->parent_id);
        struct rr_component_physical *physical =
            rr_simulation_get_physical(simulation, petal->parent_id);
        struct rr_component_health *flower_health =
            rr_simulation_get_health(simulation, relations->owner);
        struct rr_component_physical *flower_physical =
            rr_simulation_get_physical(simulation, relations->owner);
        rr_component_health_set_health(flower_health, flower_health->health -
                                                          health->damage * 2.5);
        rr_component_physical_set_server_animation_tick(flower_physical, 5);
        petal->effect_delay = 25;
        struct uranium_captures captures = {simulation, relations->owner,
                                            physical->x, physical->y,
                                            health->damage};
        rr_simulation_for_each_mob(simulation, &captures, uranium_damage);
    }
}

static void system_petal_detach(struct rr_simulation *simulation,
                                struct rr_component_petal *petal,
                                struct rr_component_player_info *player_info,
                                uint32_t outer_pos, uint32_t inner_pos,
                                struct rr_petal_data const *petal_data)
{
    petal->detached = 1;
    struct rr_component_player_info_petal *ppetal =
        &player_info->slots[outer_pos].petals[inner_pos];
    ppetal->simulation_id = RR_NULL_ENTITY;
    ppetal->cooldown_ticks = petal_data->cooldown;
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
    uint8_t is_projectile = rr_simulation_has_projectile(simulation, id);
    if (is_projectile)
    {
        struct rr_component_projectile *projectile =
            rr_simulation_get_projectile(simulation, id);
        if (petal->effect_delay <= 0)
        {
            switch (petal->id)
            {
            case rr_petal_id_missile:
                if ((player_info->input & 1) == 0)
                    break;
                system_petal_detach(simulation, petal, player_info, outer_pos,
                                    inner_pos, petal_data);
                rr_vector_from_polar(&physical->acceleration, 10.0f,
                                     physical->angle);
                rr_vector_from_polar(&physical->velocity, 50.0f,
                                     physical->angle);
                projectile->ticks_until_death = 75;
                break;
            case rr_petal_id_peas:
                if ((player_info->input & 1) == 0)
                    break;
                system_petal_detach(simulation, petal, player_info, outer_pos,
                                    inner_pos, petal_data);
                rr_vector_from_polar(&physical->acceleration, 7.5f,
                                     physical->angle);
                rr_vector_from_polar(&physical->velocity, 80.0f,
                                     physical->angle);
                projectile->ticks_until_death = 25;
                break;
            case rr_petal_id_azalea:
            {
                struct rr_component_health *flower_health = rr_simulation_get_health(simulation, player_info->flower_id);
                if (flower_health->health < flower_health->max_health)
                {
                    struct rr_vector delta = {(flower_vector.x - position_vector.x), (flower_vector.y - position_vector.y)};
                    if (rr_vector_get_magnitude(&delta) < flower_physical->radius + physical->radius)
                    {
                        //heal
                        rr_component_health_set_health(flower_health, flower_health->health + 10 * RR_PETAL_RARITY_SCALE[petal->rarity].damage);
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
                        struct rr_component_physical *target_physical =  rr_simulation_get_physical(simulation, potential);
                        struct rr_vector delta = {(target_physical->x - position_vector.x), (target_physical->y - position_vector.y)};
                        if (rr_vector_get_magnitude(&delta) > 200)
                            continue;
                        flower_health = rr_simulation_get_health(simulation, potential);
                        if (flower_health->health == flower_health->max_health)
                            continue;
                        if (rr_vector_get_magnitude(&delta) < target_physical->radius + physical->radius)
                        {
                            //heal
                            rr_component_health_set_health(flower_health, flower_health->health + 10 * RR_PETAL_RARITY_SCALE[petal->rarity].damage);
                            rr_simulation_request_entity_deletion(simulation, id);
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
                if ((player_info->input & 3) == 0)
                    break;
                system_petal_detach(simulation, petal, player_info, outer_pos,
                                    inner_pos, petal_data);
                if (player_info->input & 1)
                {
                    rr_vector_from_polar(&physical->acceleration, 10.0f,
                                        physical->angle);
                    rr_vector_from_polar(&physical->velocity, 50.0f,
                                        physical->angle);
                }
                projectile->ticks_until_death = 20;
                break;
            default:
                break;
            }
        }
        else
            --petal->effect_delay;
    }

    float holdingRadius = 75;
    if (player_info->input & 1 && !is_projectile &&
        petal_data->id != rr_petal_id_uranium && petal_data->id != rr_petal_id_magnet && petal_data->id != rr_petal_id_bone)
        holdingRadius = 150;
    else if (player_info->input & 2)
        holdingRadius = 45;
    float curr_angle = player_info->global_rotation +
                       rotation_pos * 2 * M_PI / player_info->rotation_count;
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
    if (petal->id == rr_petal_id_faster)
    {
        struct rr_vector random_vector;
        rr_vector_from_polar(&random_vector, 10.0f, rr_frand() * M_PI * 2);
        rr_vector_add(&chase_vector, &random_vector);
    }
    if (!is_projectile)
        rr_component_physical_set_angle(
            physical, physical->angle + 0.04f * (float)petal->spin_ccw);
    else
        rr_component_physical_set_angle(physical, curr_angle);
    physical->acceleration.x += 0.6f * chase_vector.x;
    physical->acceleration.y += 0.6f * chase_vector.y;
}

static void petal_modifiers(struct rr_simulation *simulation, struct rr_component_player_info *player_info)
{
    struct rr_component_flower *flower =
        rr_simulation_get_flower(simulation, player_info->flower_id);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, player_info->flower_id);
    struct rr_component_health *health =
        rr_simulation_get_health(simulation, player_info->flower_id);
    rr_component_flower_set_face_flags(flower, player_info->input);
    //reset
    physical->acceleration_scale = 1;
    player_info->modifiers.drop_pickup_radius = 25;
    health->damage_reduction = 0;
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
        else if (data->id == rr_petal_id_faster)
            player_info->global_rotation += (0.008 + 0.004 * slot->rarity);
        else if (data->id == rr_petal_id_speed)
        {
            float speed = 1 + 0.05 + 0.035 * slot->rarity;
            if (speed > physical->acceleration_scale)
                physical->acceleration_scale = speed;
        }
        else
            for (uint32_t inner = 0; inner < slot->count; ++inner)
            {
                if (slot->petals[inner].simulation_id == RR_NULL_ENTITY)
                    continue;
                if (data->id == rr_petal_id_magnet)
                {
                    player_info->modifiers.drop_pickup_radius +=
                        -25 + data->id * 25;
                }
                if (data->id == rr_petal_id_bone)
                    health->damage_reduction += 2.5 * RR_PETAL_RARITY_SCALE[slot->rarity].health;
            }
    }
}

static void rr_system_petal_reload_foreach_function(EntityIdx id,
                                                    void *simulation)
{
    struct rr_component_player_info *player_info =
        rr_simulation_get_player_info(simulation, id);
    if (player_info->flower_id == RR_NULL_ENTITY)
    {
        for (uint64_t outer = 0; outer < player_info->slot_count; ++outer)
        {
            struct rr_component_player_info_petal_slot *slot =
                &player_info->slots[outer];
            struct rr_petal_data const *data = &RR_PETAL_DATA[slot->id];
            for (uint64_t inner = 0; inner < slot->count; ++inner)
            {
                if (slot->petals[inner].simulation_id != RR_NULL_ENTITY)
                {
                    rr_simulation_request_entity_deletion(simulation, slot->petals[inner].simulation_id);
                    slot->petals[inner].simulation_id = RR_NULL_ENTITY;
                }
                slot->petals[inner].cooldown_ticks = data->cooldown;
            }
        }
        return;
    }
    petal_modifiers(simulation, player_info);
    uint32_t rotation_pos = 0;
    for (uint64_t outer = 0; outer < player_info->slot_count; ++outer)
    {
        struct rr_component_player_info_petal_slot *slot =
            &player_info->slots[outer];
        struct rr_petal_data const *data = &RR_PETAL_DATA[slot->id];
        uint8_t max_cd = 0;
        for (uint64_t inner = 0; inner < slot->count; ++inner)
        {
            if (inner == 0 || data->clump_radius == 0)
                ++rotation_pos; // clump rotpos ++
            struct rr_component_player_info_petal *p_petal =
                &slot->petals[inner];
            if (p_petal->simulation_id != RR_NULL_ENTITY &&
                (!rr_simulation_has_entity(simulation,
                                           p_petal->simulation_id) ||
                 !rr_simulation_get_physical(simulation, p_petal->simulation_id)
                      ->has_deletion_animation))
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
                    max_cd = (uint8_t) cd;
                }
                if (--p_petal->cooldown_ticks <= 0)
                {
                    p_petal->simulation_id =
                        rr_simulation_alloc_entity(simulation);
                    struct rr_component_physical *physical =
                        rr_simulation_add_physical(simulation,
                                                   p_petal->simulation_id);
                    struct rr_component_petal *petal = rr_simulation_add_petal(
                        simulation, p_petal->simulation_id);
                    struct rr_component_relations *relations =
                        rr_simulation_add_relations(simulation,
                                                    p_petal->simulation_id);
                    struct rr_component_health *health =
                        rr_simulation_add_health(simulation,
                                                 p_petal->simulation_id);
                    rr_component_physical_set_radius(physical, 10);
                    rr_component_physical_set_x(physical,
                                                player_info->camera_x);
                    rr_component_physical_set_y(physical,
                                                player_info->camera_y);
                    rr_component_physical_set_angle(physical,
                                                    rr_frand() * M_PI * 2);
                    physical->mass = 5;
                    physical->friction = 0.75;

                    rr_component_petal_set_id(petal, data->id);
                    rr_component_petal_set_rarity(petal, slot->rarity);

                    rr_component_relations_set_owner(
                        relations,
                        player_info
                            ->flower_id); // flower owns petal, not player
                    rr_component_relations_set_team(
                        relations, rr_simulation_team_id_players);

                    float scale_h = RR_PETAL_RARITY_SCALE[slot->rarity].health;
                    float scale_d = RR_PETAL_RARITY_SCALE[slot->rarity].damage;

                    rr_component_health_set_max_health(health,
                                                       scale_h * data->health);
                    rr_component_health_set_health(health,
                                                   scale_h * data->health);
                    rr_component_health_set_hidden(health, 1);
                    health->damage = scale_d * data->damage / slot->count;

                    if (data->secondary_cooldown > 0)
                    {
                        struct rr_component_projectile *projectile =
                            rr_simulation_add_projectile(
                                simulation, p_petal->simulation_id);
                        petal->effect_delay = data->secondary_cooldown;
                    }
                    else if (slot->id == rr_petal_id_uranium)
                    {
                        petal->effect_delay = 25;
                    }
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
                    rotation_pos, outer, inner, data);
                if (data->id == rr_petal_id_egg)
                {
                    struct rr_component_petal *petal = rr_simulation_get_petal(
                        simulation, p_petal->simulation_id);
                    if (petal->effect_delay > 0)
                        continue;
                    rr_simulation_get_petal(simulation, p_petal->simulation_id)
                        ->detached = 1;
                    struct rr_component_physical *petal_physical =
                        rr_simulation_get_physical(simulation,
                                                   p_petal->simulation_id);
                    rr_simulation_request_entity_deletion(simulation, p_petal->simulation_id);

                    EntityIdx mob_id = p_petal->simulation_id =
                        rr_simulation_alloc_mob(
                            simulation, rr_mob_id_trex, slot->rarity,
                            rr_simulation_team_id_players);
                    struct rr_component_relations *relations = rr_simulation_get_relations(simulation, mob_id);
                    rr_component_relations_set_owner(relations, player_info->flower_id);
                    struct rr_component_physical *mob_physical =
                        rr_simulation_get_physical(simulation, mob_id);
                    rr_component_physical_set_x(mob_physical,
                                                petal_physical->x);
                    rr_component_physical_set_y(mob_physical,
                                                petal_physical->y);
                }
            }
        }
        rr_component_player_info_set_slot_cd(player_info, outer, max_cd);
    }
    player_info->rotation_count = rotation_pos;
    player_info->global_rotation += 0.1;
}

static void system_petal_misc_logic(EntityIdx id, void *simulation)
{
    struct rr_component_petal *petal = rr_simulation_get_petal(simulation, id);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, id);
    struct rr_component_relations *relations =
        rr_simulation_get_relations(simulation, id);
    if (petal->detached == 0) // it's mob owned if this is true
    {
        if (petal->id == rr_petal_id_uranium)
            uranium_petal_system(simulation, petal);
        if (!rr_simulation_has_entity(simulation, relations->owner) ||
            physical->has_deletion_animation == 0)
        {
            rr_simulation_request_entity_deletion(simulation, id);
            return;
        }
        if (!rr_simulation_has_mob(simulation, relations->owner))
        {
            return;
        }
        // check if owner is a mob
        return; // no logic yet
    }
    else
    {
        if (petal->id == rr_petal_id_missile)
            rr_vector_from_polar(&physical->acceleration, 10.0f, physical->angle);
        else if (petal->id == rr_petal_id_peas)
            rr_vector_from_polar(&physical->acceleration, 7.5f, physical->angle);
        if (--rr_simulation_get_projectile(simulation, id)->ticks_until_death <=
            0)
            rr_simulation_request_entity_deletion(simulation, id);
    }
}

void rr_system_petal_behavior_tick(struct rr_simulation *simulation)
{
    rr_simulation_for_each_player_info(simulation, simulation,
                                       rr_system_petal_reload_foreach_function);
    rr_simulation_for_each_petal(simulation, simulation,
                                 system_petal_misc_logic);
}