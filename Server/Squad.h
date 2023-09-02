#pragma once

#include <stdint.h>

#include <Server/Simulation.h>

#include <Shared/Squad.h>

#define RR_ERROR_CODE_INVALID_SQUAD 255
#define RR_ERROR_CODE_FULL_SQUAD 254

struct rr_server_client;

struct rr_squad
{
    struct rr_squad_member members[RR_SQUAD_MEMBER_COUNT];
    uint8_t member_count;
    uint8_t private;
    char squad_code[6];
};

void rr_squad_init(struct rr_squad *);

uint8_t rr_squad_has_space(struct rr_squad *);

void rr_squad_add_client(struct rr_squad *, struct rr_server_client *);
void rr_squad_remove_client(struct rr_squad *, struct rr_server_client *);
