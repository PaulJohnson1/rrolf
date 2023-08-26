#pragma once

#include <Server/Client.h>
#include <Server/Simulation.h>
#include <Server/Squad.h>

// must be multiple of 8
// max for normal players is four, developers can bypass that cap
#define RR_MAX_CLIENT_COUNT (64)

#define RR_SQUAD_COUNT (RR_MAX_CLIENT_COUNT / RR_SQUAD_MEMBER_COUNT)

struct lws_context;
struct lws;
struct rr_server;

enum rr_websocket_event_type
{
    rr_websocket_event_type_open,
    rr_websocket_event_type_close,
    rr_websocket_event_type_data
};

struct rr_server
{
    struct rr_simulation simulation;
    uint8_t clients_in_use[RR_BITSET_ROUND(RR_MAX_CLIENT_COUNT)];
    struct rr_server_client clients[RR_MAX_CLIENT_COUNT];
    struct lws_context *server;
    struct rr_squad squads[RR_SQUAD_COUNT];
    uint8_t biome;
};

void rr_server_init(struct rr_server *);
void rr_server_free(struct rr_server *);

// Blocking function. The only time this function will never end unless the
// server crashes some how (impossible because we write god tier c)
void rr_server_run(struct rr_server *);
