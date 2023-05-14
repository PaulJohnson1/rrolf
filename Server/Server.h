#pragma once

#include <Server/Simulation.h>

// must be multiple of 8
// max for normal players is four, developers can bypass that cap
#define RR_MAX_CLIENT_COUNT (16)

struct lws_context;
struct rr_server;

struct rr_server_client
{
    int file_descriptor;
    struct rr_server *server;
};

void rr_server_client_init(struct rr_server_client *);

struct rr_server
{
    uint8_t clients_in_use[RR_MAX_CLIENT_COUNT >> 3];
    struct lws_context *server;
    struct rr_server_client clients[RR_MAX_CLIENT_COUNT];
    struct rr_simulation simulation;
};

void rr_server_init(struct rr_server *);
void rr_server_run(struct rr_server *);
