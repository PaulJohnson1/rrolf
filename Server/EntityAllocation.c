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

#include <Server/EntityAllocation.h>
#include <Server/Simulation.h>
#include <Server/Waves.h>

#include <math.h>
#include <stdlib.h>
#include <string.h>

#include <Shared/Squad.h>
#include <Shared/Utilities.h>

static struct rr_maze_grid DEFAULT_GRID = {0};

static void set_respawn_zone(struct rr_component_arena *arena, uint32_t x,
                             uint32_t y)
{
    float dim = arena->maze->grid_size;
    arena->respawn_zone.x = 2 * x * dim;
    arena->respawn_zone.y = 2 * y * dim;
}

EntityIdx rr_simulation_alloc_player(struct rr_simulation *this,
                                     EntityIdx arena_id, EntityIdx entity)
{
    struct rr_component_player_info *player_info =
        rr_simulation_get_player_info(this, entity);
    rr_component_player_info_set_arena(player_info, arena_id);
    EntityIdx flower_id = rr_simulation_alloc_entity(this);
    struct rr_component_physical *physical =
        rr_simulation_add_physical(this, flower_id);
    struct rr_component_health *health =
        rr_simulation_add_health(this, flower_id);
    struct rr_component_relations *relations =
        rr_simulation_add_relations(this, flower_id);
    struct rr_component_arena *arena = rr_simulation_get_arena(this, arena_id);
    struct rr_spawn_zone *respawn_zone = &arena->respawn_zone;
    rr_component_physical_set_x(
        physical, respawn_zone->x + 2 * arena->maze->grid_size * rr_frand());
    rr_component_physical_set_y(
        physical, respawn_zone->y + 2 * arena->maze->grid_size * rr_frand());
    rr_component_physical_set_radius(physical, 25.0f);
    physical->mass = 10;
    physical->arena = arena_id;
    physical->friction = 0.75;
    if (rand() < RAND_MAX / 1000)
        rr_component_physical_set_angle(physical, rr_frand() * M_PI * 2);

    memcpy(rr_simulation_add_flower(this, flower_id)->nickname,
           player_info->squad_member->nickname,
           sizeof player_info->squad_member->nickname);
    rr_component_flower_set_level(rr_simulation_get_flower(this, flower_id),
                                  player_info->level);
    rr_component_health_set_max_health(
        health,
        (player_info->dev ? 1000 : 1) * 100 * pow(1.0256, player_info->level > 120 ? 120 : player_info->level));
    rr_component_health_set_health(health, health->max_health);
    health->damage = health->max_health * 0.1;
    health->damage_paused = 25;
    rr_component_relations_set_team(relations, rr_simulation_team_id_players);
    rr_component_relations_set_owner(
        relations, rr_simulation_get_entity_hash(this, entity));
    rr_component_relations_update_root_owner(this, relations);
    rr_component_player_info_set_camera_x(player_info, physical->x);
    rr_component_player_info_set_camera_y(player_info, physical->y);
    rr_component_player_info_set_flower_id(
        player_info, rr_simulation_get_entity_hash(this, flower_id));
    return flower_id;
}

EntityIdx rr_simulation_alloc_petal(struct rr_simulation *this, EntityIdx arena,
                                    float x, float y, uint8_t id,
                                    uint8_t rarity, EntityIdx owner)
{
    struct rr_petal_data const *data = &RR_PETAL_DATA[id];
    EntityIdx petal_id = rr_simulation_alloc_entity(this);
    struct rr_component_physical *physical =
        rr_simulation_add_physical(this, petal_id);
    struct rr_component_petal *petal = rr_simulation_add_petal(this, petal_id);
    struct rr_component_relations *relations =
        rr_simulation_add_relations(this, petal_id);
    struct rr_component_health *health =
        rr_simulation_add_health(this, petal_id);
    rr_component_physical_set_radius(physical, 10);
    rr_component_physical_set_angle(physical, rr_frand() * M_PI * 2);
    rr_component_physical_set_x(physical, x);
    rr_component_physical_set_y(physical, y);
    physical->arena = arena;
    physical->mass = 5;
    physical->friction = 0.75;
    float scale_h = data->scale[rarity].health;
    float scale_d = data->scale[rarity].damage;
    if (id == rr_petal_id_club)
    {
        rr_component_physical_set_radius(physical, 15);
        physical->mass = 25 * powf(1.8, petal->rarity);
        physical->knockback_scale = 5;
    }

    rr_component_petal_set_id(petal, id);
    rr_component_petal_set_rarity(petal, rarity);

    rr_component_relations_set_owner(
        relations, rr_simulation_get_entity_hash(
                       this, owner)); // flower owns petal, not player
    rr_component_relations_set_team(
        relations, rr_simulation_get_relations(this, owner)->team);
    rr_component_relations_update_root_owner(this, relations);
    rr_component_health_set_max_health(health, scale_h * data->health);
    rr_component_health_set_health(health, health->max_health);
    rr_component_health_set_flags(health, health->flags | 1);
    health->damage = scale_d * data->damage / RR_PETAL_DATA[id].count[rarity];
    if (data->secondary_cooldown > 0)
    {
        petal->effect_delay = data->secondary_cooldown;
        if (id != rr_petal_id_mint)
            petal->no_rotation = 1;
    }
    return petal_id;
}

static EntityIdx rr_simulation_alloc_mob_non_recursive(
    struct rr_simulation *this, EntityIdx arena_id, float x, float y,
    enum rr_mob_id mob_id, enum rr_rarity_id rarity_id,
    enum rr_simulation_team_id team_id)
{
    EntityIdx entity = rr_simulation_alloc_entity(this);

    struct rr_component_arena *arena = rr_simulation_get_arena(this, 1);

    struct rr_component_mob *mob = rr_simulation_add_mob(this, entity);
    mob->zone = &DEFAULT_GRID;
    struct rr_component_physical *physical =
        rr_simulation_add_physical(this, entity);
    struct rr_component_health *health = rr_simulation_add_health(this, entity);
    struct rr_component_relations *relations =
        rr_simulation_add_relations(this, entity);
    struct rr_component_ai *ai = rr_simulation_add_ai(this, entity);
    // init team elsewhere
    rr_component_mob_set_id(mob, mob_id);
    rr_component_mob_set_rarity(mob, rarity_id);
    struct rr_mob_rarity_scale const *rarity_scale =
        RR_MOB_RARITY_SCALING + rarity_id;
    struct rr_mob_data const *mob_data = RR_MOB_DATA + mob_id;
    rr_component_physical_set_radius(physical,
                                     mob_data->radius * rarity_scale->radius);
    rr_component_physical_set_angle(physical, rr_frand() * 2 * M_PI);
    rr_component_physical_set_x(physical, x);
    rr_component_physical_set_y(physical, y);
    physical->arena = arena_id;
    physical->friction = 0.75;
    physical->mass = 25.0f * powf(6, RR_MOB_RARITY_SCALING[rarity_id].radius);
    rr_component_health_set_max_health(health,
                                       mob_data->health * rarity_scale->health);
    rr_component_health_set_health(health,
                                   mob_data->health * rarity_scale->health);
    health->damage = mob_data->damage * rarity_scale->damage;

    rr_component_relations_set_team(relations, team_id);

    return entity;
}

EntityIdx rr_simulation_alloc_mob(struct rr_simulation *this,
                                  EntityIdx arena_id, float x, float y,
                                  enum rr_mob_id mob_id,
                                  enum rr_rarity_id rarity_id,
                                  enum rr_simulation_team_id team_id)
{
    EntityIdx entity = rr_simulation_alloc_entity(this);

    struct rr_component_mob *mob = rr_simulation_add_mob(this, entity);
    struct rr_component_physical *physical =
        rr_simulation_add_physical(this, entity);
    struct rr_component_relations *relations =
        rr_simulation_add_relations(this, entity);
    struct rr_component_ai *ai = rr_simulation_add_ai(this, entity);
    // init team elsewhere
    mob->zone = &DEFAULT_GRID;
    rr_component_mob_set_id(mob, mob_id);
    rr_component_mob_set_rarity(mob, rarity_id);
    struct rr_mob_rarity_scale const *rarity_scale =
        RR_MOB_RARITY_SCALING + rarity_id;
    struct rr_mob_data const *mob_data = RR_MOB_DATA + mob_id;
    rr_component_physical_set_radius(physical,
                                     mob_data->radius * rarity_scale->radius);
    rr_component_physical_set_angle(physical, rr_frand() * 2 * M_PI);
    rr_component_physical_set_x(physical, x);
    rr_component_physical_set_y(physical, y);
    physical->arena = arena_id;
    physical->friction = 0.75;
    physical->mass = 25.0f * powf(6, RR_MOB_RARITY_SCALING[rarity_id].radius);
    physical->slow_resist = rr_fclamp(0.2 * (rarity_scale->radius - 1), 0, 1);
    if (mob_id == rr_mob_id_meteor)
    {
        physical->mass *= 25;
        team_id = rr_simulation_team_id_players;
        for (uint32_t i = 0; i < RR_SQUAD_COUNT; ++i)
            mob->squad_damage_counter[i] = 1e10;
    }
    rr_component_relations_set_team(relations, team_id);
    rr_component_relations_update_root_owner(this, relations);
    if (mob_id == rr_mob_id_beehive)
    {
        struct rr_component_arena *arena =
            rr_simulation_add_arena(this, entity);
        rr_component_arena_set_biome(arena, rr_biome_id_beehive);
        rr_component_arena_spatial_hash_init(arena, this);
        set_respawn_zone(arena, 0, 0);
        for (uint32_t X = 0; X < arena->maze->maze_dim; ++X)
        {
            for (uint32_t Y = 0; Y < arena->maze->maze_dim; ++Y)
            {
                uint8_t v = rr_component_arena_get_grid(arena, X, Y)->value;
                if (v == 0 || (v & 8))
                    continue;
                ++arena->mob_count;
                EntityIdx bee_entity = rr_simulation_alloc_mob(
                    this, entity, (X + rr_frand()) * arena->maze->grid_size,
                    (Y + rr_frand()) * arena->maze->grid_size,
                    rr_mob_id_honeybee, rarity_id, team_id);
                struct rr_component_mob *bee_mob =
                    rr_simulation_get_mob(this, bee_entity);
                bee_mob->no_drop = mob->no_drop;
            }
        }
    }
    else
    {
        struct rr_component_health *health =
            rr_simulation_add_health(this, entity);
        rr_component_health_set_max_health(health, mob_data->health *
                                                       rarity_scale->health);
        rr_component_health_set_health(health,
                                       mob_data->health * rarity_scale->health);
        health->damage = mob_data->damage * rarity_scale->damage;
        health->damage_paused = 25;
        if (mob_id == rr_mob_id_edmontosaurus)
            health->damage_reduction = 10 * rarity_scale->damage;
        else if (mob_id == rr_mob_id_house_centipede)
        {
            // ai->ai_type = rr_ai_type_neutral;
            EntityIdx prev_node = entity;
            struct rr_component_centipede *centipede =
                rr_simulation_add_centipede(this, entity);
            rr_component_centipede_set_is_head(centipede, 1);
            struct rr_vector extension;
            rr_vector_from_polar(&extension, -physical->radius * 2,
                                 physical->angle);
            EntityIdx new_entity = RR_NULL_ENTITY;
            for (uint64_t i = 0; i < 5; ++i)
            {
                new_entity = rr_simulation_alloc_mob_non_recursive(
                    this, arena_id, physical->x + extension.x * (i + 1),
                    physical->y + extension.y * (i + 1), mob_id, rarity_id,
                    team_id);
                centipede->child_node =
                    rr_simulation_get_entity_hash(this, new_entity);
                centipede = rr_simulation_add_centipede(this, new_entity);
                centipede->parent_node =
                    rr_simulation_get_entity_hash(this, entity);
                struct rr_component_mob *old_mob =
                    rr_simulation_get_mob(this, entity);
                struct rr_component_mob *new_mob =
                    rr_simulation_get_mob(this, new_entity);
                new_mob->no_drop = old_mob->no_drop;
                entity = new_entity;
            }
        }
    }

    return entity;
}

EntityIdx rr_simulation_alloc_entity(struct rr_simulation *this)
{
    for (EntityIdx i = 1; i < RR_MAX_ENTITY_COUNT; i++)
    {
        if (!rr_simulation_has_entity(this, i))
        {
            if (rr_bitset_get_bit(this->deleted_last_tick, i))
                continue;
            this->entity_tracker[i] = 1;
            ++this->entity_hash_tracker[i];
#ifndef NDEBUG
            printf("<rr_simulation::entity_create::%d>\n", i);
#endif
            return i;
        }
    }

    RR_UNREACHABLE("ran out of entity ids");
}
