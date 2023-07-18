#include <Server/System/Respawn.h>

#include <math.h>
#include <stdlib.h>

#include <Server/Simulation.h>

static void respawn_system_tick(EntityIdx entity, void *_captures)
{
    struct rr_simulation *this = _captures;
    struct rr_component_player_info *player_info =
        rr_simulation_get_player_info(this, entity);
    if (player_info->flower_id != RR_NULL_ENTITY)
        return;
    EntityIdx flower_id = rr_simulation_alloc_entity(this);
    struct rr_component_physical *physical =
        rr_simulation_add_physical(this, flower_id);
    struct rr_component_health *health =
        rr_simulation_add_health(this, flower_id);
    struct rr_component_relations *relations =
        rr_simulation_add_relations(this, flower_id);
    float distance = sqrt((float)rand() / (float)RAND_MAX) *
                     rr_simulation_get_arena(this, 1)->radius;
    float angle = (float)rand() / (float)RAND_MAX * M_PI * 2.0f;
    rr_component_physical_set_x(physical, cos(angle) * distance);
    rr_component_physical_set_y(physical, sin(angle) * distance);
    rr_component_physical_set_radius(physical, 25.0f);
    physical->friction = 0.9;
    if (rand() < RAND_MAX / 1000)
        rr_component_physical_set_angle(physical, rr_frand() * M_PI * 2);

    rr_simulation_add_flower(this, flower_id);
    rr_component_health_set_max_health(health, 100);
    rr_component_health_set_health(health, 100);
    health->damage = 10;
    rr_component_relations_set_team(relations, rr_simulation_team_id_players);
    rr_component_relations_set_owner(relations, entity);
    rr_component_player_info_set_camera_x(player_info, physical->x);
    rr_component_player_info_set_camera_y(player_info, physical->y);
    rr_component_player_info_set_flower_id(player_info, flower_id);
}
void rr_system_respawn_tick(struct rr_simulation *this)
{
    rr_simulation_for_each_player_info(this, this, respawn_system_tick);
}
