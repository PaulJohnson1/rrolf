#include <Server/Squad.h>

#include <string.h>
#include <stdlib.h>

#include <Server/Server.h>

void rr_squad_init(struct rr_squad *this)
{
    memset(this, 0, sizeof *this);
    this->in_use = 1;
    for (uint32_t i = 0; i < 6; ++i)
        this->squad_code[i] = (char) (97 + rand() % 26);
}

uint8_t rr_squad_has_space(struct rr_squad *this)
{
    return this->members_in_use != (1 << RR_SQUAD_MEMBER_COUNT) - 1;
}

void rr_squad_add_client(struct rr_squad *this, struct rr_server_client *client)
{
    if (!this->in_use)
        rr_squad_init(this);
    for (uint32_t i = 0; i < RR_SQUAD_MEMBER_COUNT; ++i)
    {
        if ((this->members_in_use >> i) & 1)
            continue;
        client->squad_pos = i;
        this->clients[i] = client;
        this->members_in_use |= 1 << i;
        return;
    }
}

void rr_squad_remove_client(struct rr_squad *this, struct rr_server_client *client)
{    
    this->members_in_use &= ~(1 << client->squad_pos);
    //client->squad = 0;
    client->squad_pos = 0;
    if (this->members_in_use == 0)
        this->in_use = 0;
}

