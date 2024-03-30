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

#include <stdio.h>
#include <string.h>

#include <Server/Simulation.h>
#include <Server/SpatialHash.h>
#include <Shared/Bitset.h>

struct physics_simulation_captures
{
    struct rr_simulation *simulation;
    struct rr_component_physical *physical;
};

static void system_reset_colliding_with(EntityIdx entity, void *captures)
{
    struct rr_simulation *this = captures;
    if (!rr_simulation_has_physical(this, entity))
        return;

    struct rr_component_physical *physical =
        rr_simulation_get_physical(this, entity);
    physical->colliding_with_size = 0;
    EntityIdx owner = rr_simulation_get_relations(this, entity)->owner;
    if (rr_simulation_entity_alive(this, owner) &&
        rr_simulation_has_physical(this, owner))
        if (physical->arena != rr_simulation_get_physical(this, owner)->arena)
            rr_simulation_request_entity_deletion(this, entity);
}

static void system_insert_entities(EntityIdx entity, void *_captures)
{
    struct rr_simulation *this = _captures;
    struct rr_component_physical *physical =
        rr_simulation_get_physical(this, entity);
    if (rr_simulation_has_health(this, entity))
    {
        struct rr_component_health *health =
            rr_simulation_get_health(this, entity);
        if (health->health == 0)
            return;
        rr_component_health_set_flags(health, health->flags & (~2));
    }
    rr_spatial_hash_insert(
        &rr_simulation_get_arena(this, physical->arena)->spatial_hash, entity);
}
static uint8_t should_entities_collide(struct rr_simulation *this, EntityIdx a,
                                       EntityIdx b)
{
#define exclude(component_a, component_b)                                      \
    if (rr_simulation_has_##component_a(this, a) &&                            \
        rr_simulation_has_##component_b(this, b))                              \
        return 0;                                                              \
    if (rr_simulation_has_##component_a(this, b) &&                            \
        rr_simulation_has_##component_b(this, a))                              \
        return 0;
    exclude(web, web);
    exclude(web, petal);
    exclude(drop, drop);
    exclude(drop, mob);
    uint8_t team1 = rr_simulation_get_relations(this, a)->team;
    uint8_t team2 = rr_simulation_get_relations(this, b)->team;
    if (team1 != team2)
        return 1; // only drop doesn't care about team
    exclude(petal, petal);
    exclude(petal, flower);
    exclude(petal, mob);
    exclude(flower, mob);
#undef exclude

    return 1;
}
static void grid_filter_candidates(struct rr_simulation *this,
                                   EntityIdx entity1, EntityIdx entity2,
                                   void *_captures)
{
    struct rr_component_physical *physical1 =
        rr_simulation_get_physical(this, entity1);
    struct rr_component_physical *physical2 =
        rr_simulation_get_physical(this, entity2);
    if (!should_entities_collide(this, entity1, entity2))
        return;
    struct rr_vector delta = {physical1->x - physical2->x,
                              physical1->y - physical2->y};
    float collision_radius = physical1->radius + physical2->radius;
    if ((delta.x * delta.x + delta.y * delta.y) <
        collision_radius * collision_radius)
    {
#ifndef RIVET_BUILD
        if (physical1->colliding_with_size >= RR_MAX_COLLISION_COUNT)
            puts("entity cram limit exceeded");
#endif
        physical1->colliding_with[physical1->colliding_with_size++] = entity2;
    }
}

static void collapse_arena(EntityIdx entity, void *_captures)
{
    struct rr_simulation *this = _captures;
    struct rr_component_arena *arena = rr_simulation_get_arena(this, entity);
    rr_spatial_hash_reset(&arena->spatial_hash);
    if (!rr_simulation_has_mob(this, entity))
        return;
    struct rr_component_mob *mob = rr_simulation_get_mob(this, entity);
    if (arena->mob_count == 0 && arena->player_entered)
    {
        if (mob->ticks_to_despawn > 25)
            mob->ticks_to_despawn = 25;
        --mob->ticks_to_despawn;
    }
    else if (arena->player_entered)
        --mob->ticks_to_despawn;
    if (mob->ticks_to_despawn == 0)
        rr_simulation_request_entity_deletion(this, entity);
}

static void find_collisions(EntityIdx entity, void *_captures)
{
    struct rr_simulation *this = _captures;
    struct rr_component_arena *arena = rr_simulation_get_arena(this, entity);
    rr_spatial_hash_find_possible_collisions(&arena->spatial_hash, NULL,
                                             grid_filter_candidates);
}

void rr_system_collision_detection_tick(struct rr_simulation *this)
{
    rr_simulation_for_each_arena(this, this, collapse_arena);
    rr_simulation_for_each_physical(this, this, system_reset_colliding_with);
    rr_simulation_for_each_physical(this, this, system_insert_entities);
    rr_simulation_for_each_arena(this, this, find_collisions);
}
