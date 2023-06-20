#pragma once

#include <Shared/Utilities.h>

#if defined(RIVET_BUILD) && !defined(WASM_BUILD)
// you're welcome bismuth
#include <curl/curl.h>
#endif

struct rr_rivet_lobby_connect_info
{
    char *player_token;
    char *hostname;
    uint16_t port;
};

RR_SERVER_ONLY(extern void rr_rivet_lobbies_ready(char const *lobby_token);)
RR_CLIENT_ONLY(extern void rr_rivet_lobbies_find(void (*cb)(struct rr_rivet_lobby_connect_info), void *);)
