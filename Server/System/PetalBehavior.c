#include <Server/System/PetalBehavior.h>

#include <math.h>
#include <stdio.h>

#include <Server/Simulation.h>

#include <Shared/Entity.h>
#include <Shared/StaticData.h>
#include <Shared/Utilities.h>
#include <Shared/Vector.h>

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
// sinc ethis is static, the fucntion name doesn't need any sorto f prefix and
// can just be petal_logic
static void system_flower_petal_movement_logic(
    struct rr_simulation *simulation, EntityIdx id,
    struct rr_component_player_info *player_info, uint32_t rotation_pos,
    uint32_t outer_pos, uint32_t inner_pos,
    struct rr_petal_data const *petal_data)
{
    struct rr_component_petal *petal = rr_simulation_get_petal(simulation, id);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, id);
    uint8_t is_projectile = rr_simulation_has_projectile(simulation, id);
    if (is_projectile)
    {
        struct rr_component_projectile *projectile =
            rr_simulation_get_projectile(simulation, id);
        if (--projectile->shoot_delay <= 0)
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
                rr_vector_from_polar(&physical->acceleration, 10.0f,
                                     physical->angle);
                rr_vector_from_polar(&physical->velocity, 100.0f,
                                     physical->angle);
                projectile->ticks_until_death = 25;
                break;
            default:
                break;
            }
        }
    }

    struct rr_component_physical *flower_physical =
        rr_simulation_get_physical(simulation, player_info->flower_id);
    struct rr_vector position_vector = {physical->x, physical->y};
    struct rr_vector flower_vector = {flower_physical->x, flower_physical->y};
    float holdingRadius = 75;
    if (player_info->input & 1 && !is_projectile)
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
    physical->acceleration.x = 0.6f * chase_vector.x;
    physical->acceleration.y = 0.6f * chase_vector.y;
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
                    struct rr_component_health *health =
                        rr_simulation_get_health(
                            simulation, slot->petals[inner].simulation_id);
                    rr_component_health_set_health(health, 0);
                    slot->petals[inner].simulation_id = RR_NULL_ENTITY;
                }
                slot->petals[inner].cooldown_ticks = data->cooldown;
            }
        }
        return;
    }
    struct rr_component_flower *flower = rr_simulation_get_flower(simulation, player_info->flower_id);
    rr_component_flower_set_face_flags(flower, player_info->input);
    player_info->modifiers.drop_pickup_radius = 25;
    uint32_t rotation_pos = 0;
    for (uint64_t outer = 0; outer < player_info->slot_count; ++outer)
    {
        struct rr_component_player_info_petal_slot *slot =
            &player_info->slots[outer];
        struct rr_petal_data const *data = &RR_PETAL_DATA[slot->id];
        if (data->id == rr_petal_id_leaf)
        {
            struct rr_component_health *player_health =
                rr_simulation_get_health(simulation, player_info->flower_id);
            rr_component_health_set_health(player_health,
                                           player_health->health + 0.04 * RR_PETAL_RARITY_SCALE[slot->rarity]);
        }
        uint8_t max_cd = 0;
        for (uint64_t inner = 0; inner < slot->count; ++inner)
        {
            if (inner == 0 || data->clump_radius == 0)
                ++rotation_pos; // clump rotpos ++
            // specials
            if (data->id == rr_petal_id_faster)
                player_info->global_rotation += (0.008 + 0.004 * slot->rarity);
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
                uint8_t cd =
                    ((float)p_petal->cooldown_ticks / data->cooldown) * 255;
                if (cd > max_cd)
                    max_cd = cd;
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

                    float scale = RR_PETAL_RARITY_SCALE[slot->rarity];

                    rr_component_health_set_max_health(health,
                                                       scale * data->health);
                    rr_component_health_set_health(health,
                                                   scale * data->health);
                    rr_component_health_set_hidden(health, 1);
                    health->damage = scale * data->damage / slot->count;

                    if (data->id == rr_petal_id_missile ||
                        data->id == rr_petal_id_peas ||
                        data->id == rr_petal_id_egg)
                    {
                        struct rr_component_projectile *projectile =
                            rr_simulation_add_projectile(
                                simulation, p_petal->simulation_id);
                        projectile->shoot_delay = 12;
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
                if (data->id == rr_petal_id_magnet)
                {
                    player_info->modifiers.drop_pickup_radius += -50 + data->id * 25;
                }
                system_flower_petal_movement_logic(
                    simulation, p_petal->simulation_id, player_info,
                    rotation_pos, outer, inner, data);
                if (data->id == rr_petal_id_egg)
                {
                    struct rr_component_projectile *projectile =
                        rr_simulation_get_projectile(simulation,
                                                     p_petal->simulation_id);
                    if (projectile->shoot_delay > 0)
                        continue;
                    rr_simulation_get_petal(simulation, p_petal->simulation_id)
                        ->detached = 1;
                    struct rr_component_physical *petal_physical =
                        rr_simulation_get_physical(simulation,
                                                   p_petal->simulation_id);
                    // rr_simulation_request_entity_deletion(simulation,
                    // p_petal->simulation_id);
                    rr_component_health_set_health(
                        rr_simulation_get_health(simulation,
                                                 p_petal->simulation_id),
                        0);

                    EntityIdx mob_id = p_petal->simulation_id =
                        rr_simulation_alloc_mob(simulation, rr_mob_id_trex,
                                                slot->rarity == 0 ? 0 : slot->rarity - 1, rr_simulation_team_id_players);
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

static void system_non_player_owned_petal_movement_logic(EntityIdx id,
                                                         void *simulation)
{
    struct rr_component_petal *petal = rr_simulation_get_petal(simulation, id);
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, id);
    struct rr_component_relations *relations =
        rr_simulation_get_relations(simulation, id);
    if (petal->detached == 0) // it's mob owned if this is true
    {
        if (!rr_simulation_has_entity(simulation, relations->owner) ||
            physical->has_deletion_animation == 0)
        {
            struct rr_component_health *health =
                rr_simulation_get_health(simulation, id);
            rr_component_health_set_health(health, 0);
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
        rr_vector_from_polar(&physical->acceleration, 10.0f, physical->angle);
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
                                 system_non_player_owned_petal_movement_logic);
}