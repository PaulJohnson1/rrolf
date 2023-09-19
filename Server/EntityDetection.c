#include <Server/EntityDetection.h>
#include <Server/SpatialHash.h>
#include <Server/Simulation.h>

#include <Shared/Vector.h>

struct entity_finder_captures
{
    struct rr_simulation *simulation;
    void *captures;
    uint8_t (*filter)(struct rr_simulation *, EntityIdx, EntityIdx, void *);
    EntityIdx closest;
    EntityIdx seeker;
    EntityIdx arena;
    uint8_t seeker_team;
    float closest_dist;
    float x;
    float y;
};

void shg_cb(EntityIdx potential, void *_captures)
{
    struct entity_finder_captures *captures = _captures;
    struct rr_simulation *simulation = captures->simulation;
    if (!rr_simulation_has_mob(simulation, potential) && !rr_simulation_has_flower(simulation, potential))
        return;
    if (rr_simulation_get_relations(simulation, potential)->team == captures->seeker_team)
        return;
    struct rr_component_physical *t_physical = rr_simulation_get_physical(simulation, potential);
    if (t_physical->arena != captures->arena)
        return;
    struct rr_vector delta = {captures->x - t_physical->x, captures->y - t_physical->y};
    float dist = rr_vector_get_magnitude(&delta) * t_physical->aggro_range_multiplier - t_physical->radius;
    if (dist > captures->closest_dist)
        return;
    if (!captures->filter(simulation, captures->seeker, potential, captures->captures))
        return;
    captures->closest_dist = dist;
    captures->closest = potential;
}

EntityIdx rr_simulation_find_nearest_enemy(struct rr_simulation *simulation, EntityIdx seeker, float search_range, void *captures, uint8_t (*filter)(struct rr_simulation *, EntityIdx, EntityIdx, void *))
{
    struct rr_component_physical *physical = rr_simulation_get_physical(simulation, seeker);
    
    return rr_simulation_find_nearest_enemy_custom_pos(simulation, seeker, physical->x, physical->y, search_range, captures, filter);
}

EntityIdx rr_simulation_find_nearest_enemy_custom_pos(struct rr_simulation *simulation, EntityIdx seeker, float x, float y, float min_dist, void *captures, uint8_t (*filter)(struct rr_simulation *, EntityIdx, EntityIdx, void *))
{
    EntityIdx target = RR_NULL_ENTITY;
    struct rr_component_physical *physical = rr_simulation_get_physical(simulation, seeker);
    struct rr_component_relations *relations = rr_simulation_get_relations(simulation, seeker);
    struct entity_finder_captures shg_captures;
    shg_captures.simulation = simulation;
    shg_captures.captures = captures;
    shg_captures.filter = filter;
    shg_captures.closest = target;
    shg_captures.seeker = seeker;
    shg_captures.closest_dist = min_dist;
    shg_captures.x = x;
    shg_captures.y = y;
    shg_captures.seeker_team = relations->team;
    shg_captures.arena = physical->arena;
    rr_spatial_hash_query(simulation->grid, x, y, min_dist, min_dist, &shg_captures, shg_cb);

    return shg_captures.closest;
}

uint8_t no_filter(struct rr_simulation *simulation, EntityIdx seeker, EntityIdx target, void *captures)
{
    return 1;
}