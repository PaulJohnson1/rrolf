#pragma once

#include <Server/Client.h>
#include <Server/Simulation.h>

// must be multiple of 8
// max for normal players is four, developers can bypass that cap
#define RR_MAX_CLIENT_COUNT (64)

struct lws_context;
struct lws;
struct rr_server;

struct rr_server
{
    uint8_t clients_in_use[RR_BITSET_ROUND(RR_MAX_CLIENT_COUNT)];
    uint8_t simulation_active;
    int8_t ticks_until_simulation_create;
    struct lws_context *server;
    struct rr_server_client clients[RR_MAX_CLIENT_COUNT];
    struct rr_simulation simulation;
    uint32_t countdown_ticks;
};

void rr_server_init(struct rr_server *);
void rr_server_free(struct rr_server *);

// Blocking function. The only time this function will never end unless the
// server crashes some how (impossible because we write god tier c)
void rr_server_run(struct rr_server *);
