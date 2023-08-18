#include <Server/EntityDetection.h>

#include <Server/Simulation.h>
#include <Shared/Vector.h>

EntityIdx rr_simulation_find_nearest_enemy(struct rr_simulation *simulation, EntityIdx seeker, float search_range, void *captures, uint8_t (*filter)(struct rr_simulation *, EntityIdx, EntityIdx, void *))
{
    EntityIdx target = RR_NULL_ENTITY;
    struct rr_component_physical *physical = rr_simulation_get_physical(simulation, seeker);
    struct rr_component_relations *relations = rr_simulation_get_relations(simulation, seeker);
    float min_dist = search_range;
    if (relations->team == rr_simulation_team_id_mobs)
    {
        for (uint32_t i = 0; i < simulation->flower_count; ++i)
        {
            EntityIdx potential = simulation->flower_vector[i];
            struct rr_component_physical *t_physical = rr_simulation_get_physical(simulation, potential);
            struct rr_vector delta = {physical->x - t_physical->x, physical->y - t_physical->y};
            float dist = rr_vector_get_magnitude(&delta) - t_physical->radius - physical->radius;
            if (dist > search_range)
                continue;
            if (!filter(simulation, seeker, potential, captures))
                continue;
            min_dist = dist;
            target = potential;
        }
        for (uint32_t i = 0; i < simulation->mob_count; ++i)
        {
            EntityIdx potential = simulation->mob_vector[i];
            if (rr_simulation_get_relations(simulation, potential)->team == rr_simulation_team_id_mobs)
                continue;
            struct rr_component_physical *t_physical = rr_simulation_get_physical(simulation, potential);
            struct rr_vector delta = {physical->x - t_physical->x, physical->y - t_physical->y};
            float dist = rr_vector_get_magnitude(&delta) - t_physical->radius - physical->radius;
            if (dist > search_range)
                continue;
            if (!filter(simulation, seeker, potential, captures))
                continue;
            min_dist = dist;
            target = potential;
        }
    }
    else
    {
        for (uint32_t i = 0; i < simulation->mob_count; ++i)
        {
            EntityIdx potential = simulation->mob_vector[i];
            if (rr_simulation_get_relations(simulation, potential)->team == rr_simulation_team_id_players)
                continue;
            struct rr_component_physical *t_physical = rr_simulation_get_physical(simulation, potential);
            struct rr_vector delta = {physical->x - t_physical->x, physical->y - t_physical->y};
            float dist = rr_vector_get_magnitude(&delta) - t_physical->radius - physical->radius;
            if (dist > search_range)
                continue;
            if (!filter(simulation, seeker, potential, captures))
                continue;
            min_dist = dist;
            target = potential;
        }
    }
    return target;
}

uint8_t no_filter(struct rr_simulation *simulation, EntityIdx seeker, EntityIdx target, void *captures)
{
    return 1;
}