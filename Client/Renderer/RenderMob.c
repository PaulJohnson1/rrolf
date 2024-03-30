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

#include <Client/Renderer/ComponentRender.h>

#include <math.h>

#include <Client/Game.h>
#include <Client/Renderer/Renderer.h>
#include <Client/Simulation.h>
#include <Shared/StaticData.h>

#include <Client/Assets/RenderFunctions.h>

void rr_component_mob_render(EntityIdx entity, struct rr_game *game,
                             struct rr_simulation *simulation)
{
    struct rr_renderer *renderer = game->renderer;
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);
    struct rr_component_mob *mob = rr_simulation_get_mob(simulation, entity);
    if (rr_simulation_get_relations(simulation, entity)->team ==
            rr_simulation_team_id_players &&
        mob->id == rr_mob_id_trex)
        rr_renderer_add_color_filter(renderer, 0xffffff63, 0.3);
    uint8_t has_arena = rr_simulation_has_arena(simulation, entity);
    struct rr_component_health *health;
    if (!has_arena)
    {
        health = rr_simulation_get_health(simulation, entity);
        rr_renderer_add_color_filter(renderer, 0xffff0000,
                                     0.5 * health->damage_animation);
    }
    rr_renderer_set_global_alpha(renderer, 1 - physical->deletion_animation);
    rr_renderer_scale(renderer, 1 + physical->deletion_animation * 0.5);
    rr_renderer_rotate(renderer, physical->lerp_angle);
    rr_renderer_scale(renderer, RR_MOB_RARITY_SCALING[mob->rarity].radius);
    if (mob->id == rr_mob_id_meteor)
    {
        struct rr_simulation_animation *particle = rr_particle_alloc(
            &game->particle_manager, rr_animation_type_default);
        float angle =
            rr_vector_theta(&physical->lerp_velocity) + M_PI - 0.5 + rr_frand();
        float dist = rr_frand() * 50;
        rr_vector_from_polar(&particle->velocity,
                             (rr_frand() * 5 + 5) *
                                 RR_MOB_RARITY_SCALING[mob->rarity].radius,
                             angle);
        particle->x = physical->lerp_x + cosf(angle) * dist;
        particle->y = physical->lerp_y + sinf(angle) * dist;
        particle->size =
            (4 + rr_frand() * 2) * RR_MOB_RARITY_SCALING[mob->rarity].radius;
        particle->opacity = 0.8;
        particle->color = 0xffab3423;
    }
    if (physical->animation_timer > 2 * M_PI)
        physical->animation_timer = fmod(physical->animation_timer, 2 * M_PI);
    physical->animation =
        rr_lerp(physical->animation, sinf(physical->animation_timer),
                30 * game->lerp_delta);

    uint8_t use_cache = has_arena ? 1
                                  : ((health->damage_animation < 0.1) |
                                     game->cache.low_performance_mode) &
                                        1;
    uint8_t is_friendly =
        (rr_simulation_get_relations(simulation, entity)->team !=
         rr_simulation_team_id_mobs)
        << 1;
    uint8_t is_centi_body =
        4 - ((rr_simulation_has_centipede(simulation, entity) &&
              rr_simulation_get_centipede(simulation, entity)->is_head)
             << 2);
    rr_renderer_draw_mob(renderer, mob->id, physical->animation_timer,
                         physical->turning_animation - physical->lerp_angle,
                         use_cache | is_friendly | is_centi_body);
}
