#pragma once

#include <Shared/Utilities.h>

#if defined(RIVET_BUILD) && !defined(EMSCRIPTEN)
#include <curl/curl.h>
#endif

struct rr_rivet_account
{
    char account_number[6];
    char token[300];
    char uuid[100];
    char name[100];
    char avatar_url[200];
};

// user must define this function.
void rr_rivet_lobby_on_find(char *s, char *token, uint16_t port,
                            void *captures);

RR_SERVER_ONLY(extern void rr_rivet_lobbies_ready(char const *lobby_token);)
RR_SERVER_ONLY(extern int rr_rivet_players_connected(char const *lobby_token,
                                                     char const *player_token);)
RR_SERVER_ONLY(extern void rr_rivet_players_disconnected(
                   char const *lobby_token, char const *player_token);)
RR_SERVER_ONLY(extern void rr_rivet_lobbies_set_closed(char const *lobby_token,
                                                       int closed);)
RR_CLIENT_ONLY(extern void rr_rivet_lobbies_find(void *);)
RR_CLIENT_ONLY(extern void rr_rivet_identities_create_guest(void *);)
