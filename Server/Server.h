#pragma once

#include <Server/Client.h>
#include <Server/Simulation.h>

// must be multiple of 8
// max for normal players is four, developers can bypass that cap
#define RR_MAX_CLIENT_COUNT (64)

struct lws_context;
struct lws;
struct rr_server;

enum rr_websocket_event_type
{
    rr_websocket_event_type_open,
    rr_websocket_event_type_close,
    rr_websocket_event_type_data
};

struct rr_squad
{
    struct rr_server_client *clients[RR_SQUAD_MEMBER_COUNT];
    uint32_t countdown_ticks;
    uint8_t members_in_use;
    uint8_t private;
};

struct rr_server
{
    uint8_t clients_in_use[RR_BITSET_ROUND(RR_MAX_CLIENT_COUNT)];
    struct lws_context *server;
    struct rr_server_client clients[RR_MAX_CLIENT_COUNT];
    struct rr_squad squads[16];
    struct rr_simulation simulation;
    uint8_t pos;
    uint8_t biome;
};

void rr_server_init(struct rr_server *);
void rr_server_free(struct rr_server *);

// Blocking function. The only time this function will never end unless the
// server crashes some how (impossible because we write god tier c)
void rr_server_run(struct rr_server *);
