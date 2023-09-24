#pragma once

#include <Server/Client.h>
#include <Server/Simulation.h>
#include <Server/Squad.h>

// must be multiple of 8
// max for normal players is four, developers can bypass that cap
#define RR_MAX_CLIENT_COUNT (64)
#define RR_SQUAD_COUNT RR_MAX_CLIENT_COUNT

struct lws_context;
struct lws;
struct rr_server;

enum rr_websocket_event_type
{
    rr_websocket_event_type_open,
    rr_websocket_event_type_close,
    rr_websocket_event_type_data
};

struct rr_api_websocket
{
    void *user_data;
    void (*on_event)(enum rr_websocket_event_type, void *, void *, uint64_t);
    struct lws_context *socket_context;
    struct lws *socket;
};

struct rr_server
{
    uint8_t clients_in_use[RR_BITSET_ROUND(RR_MAX_CLIENT_COUNT)];
    struct rr_server_client clients[RR_MAX_CLIENT_COUNT];
    struct lws_context *server;
    struct lws_context *api_client_context;
    struct lws *api_client;
    struct rr_squad squads[RR_MAX_CLIENT_COUNT];
    uint8_t biome;
    uint8_t api_ws_ready;
    char server_alias[16];
};

void rr_server_init(struct rr_server *);
void rr_server_free(struct rr_server *);

uint8_t rr_client_create_squad(struct rr_server *, struct rr_server_client *);
uint8_t rr_client_find_squad(struct rr_server *, struct rr_server_client *);
uint8_t rr_client_join_squad_with_code(struct rr_server *, char *);
uint8_t rr_client_join_squad(struct rr_server *, struct rr_server_client *, uint8_t);
void rr_client_leave_squad(struct rr_server *, struct rr_server_client *);
struct rr_squad_member *rr_squad_get_client_slot(struct rr_server *, struct rr_server_client *);
struct rr_simulation *rr_client_get_simulation(struct rr_server *, struct rr_server_client *);

// Blocking function. The only time this function will never end unless the
// server crashes some how (impossible because we write god tier c)
void rr_server_run(struct rr_server *);
