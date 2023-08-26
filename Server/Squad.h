#pragma once

#include <stdint.h>

#include <Server/Simulation.h>

struct rr_server_client;

struct rr_squad
{
    struct rr_server_client *clients[RR_SQUAD_MEMBER_COUNT];
    uint8_t in_use;
    uint8_t members_in_use;
    uint8_t private;
    char squad_code[6];
};

void rr_squad_init(struct rr_squad *);

uint8_t rr_squad_has_space(struct rr_squad *);

void rr_squad_add_client(struct rr_squad *, struct rr_server_client *);
void rr_squad_remove_client(struct rr_squad *, struct rr_server_client *);
