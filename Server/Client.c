#include <Server/Client.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <Shared/Crypto.h>
#include <Shared/Entity.h>
#include <Shared/Component/PlayerInfo.h>
#include <Server/Server.h>
#include <Server/Simulation.h>

void rr_server_client_init(struct rr_server_client *this)
{
    memset(this, 0, sizeof *this);
    this->encryption_key = rr_get_rand();
    printf("client connected, encrypting with key %lu\n", this->encryption_key);
}

void rr_server_client_create_flower(struct rr_server_client *this)
{
    if (this->player_info == NULL)
    {
        puts("tried to init a flower when player info is null");
        return;
    }
    if (this->player_info->flower_id != RR_NULL_ENTITY)
    {
        puts("tried to init a flower but flower already exists");
        return;
    }
    EntityIdx flower_id = rr_simulation_alloc_entity(&this->server->simulation);
    struct rr_component_physical *physical = rr_simulation_add_physical(&this->server->simulation, flower_id);
    struct rr_component_health *health = rr_simulation_add_health(&this->server->simulation, flower_id);
    struct rr_component_relations *relations = rr_simulation_add_relations(&this->server->simulation, flower_id);
    float distance = sqrt((float)rand() / (float)RAND_MAX) * 1650.0f;
    float angle = (float)rand() / (float)RAND_MAX * M_PI * 2.0f;
    rr_component_physical_set_x(physical, cos(angle) * distance);
    rr_component_physical_set_y(physical, sin(angle) * distance);
    rr_component_physical_set_radius(physical, 25.0f);
    physical->friction = 0.9;

    rr_simulation_add_flower(&this->server->simulation, flower_id);
    rr_component_health_set_max_health(health, 100000);
    rr_component_health_set_health(health, 100000);
    rr_component_relations_set_team(relations, flower_id + 3/*rr_simulation_team_id_players*/);
    rr_component_relations_set_owner(relations, this->player_info->parent_id);
    rr_component_player_info_set_camera_x(this->player_info, physical->x);
    rr_component_player_info_set_camera_y(this->player_info, physical->y);
    rr_component_player_info_set_flower_id(this->player_info, flower_id);
}
