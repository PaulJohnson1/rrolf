#include <Server/Client.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Server/EntityAllocation.h>
#include <Server/Server.h>
#include <Server/Simulation.h>
#include <Shared/Component/PlayerInfo.h>
#include <Shared/Crypto.h>
#include <Shared/Entity.h>

void rr_server_client_init(struct rr_server_client *this)
{
    memset(this, 0, sizeof *this);
    this->clientbound_encryption_key = rr_get_rand();
    this->serverbound_encryption_key = rr_get_rand();
    this->requested_verification = rr_get_rand();
    printf("client connected, using encryption data %lu %lu %lu\n",
           this->requested_verification, this->clientbound_encryption_key,
           this->serverbound_encryption_key);
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
    puts("creating flower");
    rr_simulation_alloc_player(this->player_info->parent_id, &this->server->simulation);
}
