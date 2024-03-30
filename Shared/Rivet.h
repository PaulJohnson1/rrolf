// Copyright (C) 2024  Paul Johnson

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.

// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include <Shared/Utilities.h>

#if defined(RIVET_BUILD) && !defined(EMSCRIPTEN)
#include <curl/curl.h>
#endif

struct rr_rivet_account
{
    char account_number[10];
    char token[500];
    char api_password[500];
    char uuid[500];
    char name[500];
    char avatar_url[500];
};

// user must define this function.
void rr_rivet_lobby_on_find(char *s, char *token, uint16_t port,
                            void *captures);
void rr_rivet_on_log_in(char *token, char *avatar_url, char *name,
                        char *account_number, char *uuid, uint8_t linked,
                        void *captures);

RR_SERVER_ONLY(extern void rr_rivet_lobbies_ready(char const *lobby_token);)
RR_SERVER_ONLY(extern int rr_rivet_players_connected(char const *lobby_token,
                                                     char const *player_token);)
RR_SERVER_ONLY(extern void rr_rivet_players_disconnected(
                   char const *lobby_token, char const *player_token);)
RR_SERVER_ONLY(extern void rr_rivet_lobbies_set_closed(char const *lobby_token,
                                                       int closed);)
RR_CLIENT_ONLY(extern void rr_rivet_lobbies_find(void *captures,
                                                 char const *region);)
RR_CLIENT_ONLY(extern void rr_rivet_lobbies_join(void *captures, char const *);)
RR_CLIENT_ONLY(extern void rr_rivet_identities_create_guest(void *captures);)
RR_CLIENT_ONLY(extern void rr_rivet_link_account(char *game_user,
                                                 char *api_password,
                                                 void *captures);)
