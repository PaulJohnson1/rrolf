#pragma once

#include <Shared/Utilities.h>

#if defined(RIVET_BUILD) && !defined(EMSCRIPTEN)
// you're welcome bismuth
#include <curl/curl.h>
#endif

// user must define this function.
void rr_rivet_lobby_on_find(char *s, char *token, uint16_t port, void *captures);

RR_SERVER_ONLY(extern void rr_rivet_lobbies_ready(char const *lobby_token);)
RR_SERVER_ONLY(extern int rr_rivet_players_connected(char const *lobby_token, char const *player_token);)
RR_SERVER_ONLY(extern void rr_rivet_players_disconnected(char const *lobby_token, char const *player_token);)
RR_SERVER_ONLY(extern void rr_rivet_lobbies_set_closed(char const *lobby_token, int closed);)
RR_CLIENT_ONLY(extern void rr_rivet_lobbies_find(void *);)
