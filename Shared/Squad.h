#pragma once

#include <stdint.h>

#include <Shared/Entity.h>
#include <Shared/Utilities.h>

#ifdef RR_SERVER
struct rr_server_client;
#endif

struct rr_squad_member
{
    RR_SERVER_ONLY(struct rr_server_client *client;)
    uint32_t level;
    uint8_t in_use : 1;
    uint8_t playing : 1;
    uint8_t dev : 1;
    struct rr_id_rarity_pair loadout[20];
    char nickname[16];
};