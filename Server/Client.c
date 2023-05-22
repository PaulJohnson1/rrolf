#include <Server/Client.h>

#include <string.h>
#include <stdio.h>

#include <Shared/Entity.h>
#include <Shared/Component/PlayerInfo.h>

#include <Server/Server.h>
#include <Server/Simulation.h>

void rr_server_client_init(struct rr_server_client *this)
{
    memset(this, 0, sizeof *this);
    puts("client connected");
}

void rr_server_client_create_flower(struct rr_server_client *this)
{
    if (this->player_info == NULL)
    {
        puts("tried to init a flower when player info is null");
        return;
    }
    if (this->player_info->flower_id != 0)
    {
        puts("tried to init a flower but flower already exists");
        return;
    }
    EntityIdx flower_id = rr_simulation_alloc_entity(&this->server->simulation);
    rr_component_physical_set_radius(rr_simulation_add_physical(&this->server->simulation, flower_id), 25.0f);
    rr_simulation_get_physical(&this->server->simulation, flower_id)->friction = 0.9;
    rr_simulation_add_flower(&this->server->simulation, flower_id);
    struct rr_component_health *health = rr_simulation_add_health(&this->server->simulation, flower_id);
    rr_component_health_set_health(health, 0.5);
    rr_component_health_set_max_health(health, 1);
    struct rr_component_relations *relations = rr_simulation_add_relations(&this->server->simulation, flower_id);
    rr_component_relations_set_team(relations, 1);
    rr_component_player_info_set_flower_id(this->player_info, flower_id);
}