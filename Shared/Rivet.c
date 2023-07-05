/**
 * This file is only compiled and linked to the executable if the cmake flag
 * RIVET_BUILD is set.
 */

#include <Shared/Rivet.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef EMSCRIPTEN
#include <curl/curl.h>
#else
#include <emscripten.h>
#endif

#include <Shared/cJSON.h>

#define RR_RIVET_CURL_PROLOGUE                                                 \
    struct curl_slist *list = 0;                                               \
    int err = 0;                                                               \
    CURL *curl = curl_easy_init();                                             \
    assert(curl);                                                              \
    char header[500] = "Authorization: Bearer ";                               \
    list = curl_slist_append(list, strcat(header, lobby_token));               \
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);

#define RR_RIVET_CURL_EPILOGUE                                                 \
    err = curl_easy_perform(curl);                                             \
    assert(!err);                                                              \
    curl_easy_cleanup(curl);                                                   \
    curl_slist_free_all(list);

void rr_rivet_lobbies_ready(char const *lobby_token)
{
#ifdef RR_SERVER
    RR_RIVET_CURL_PROLOGUE
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_URL,
                     "https://matchmaker.api.rivet.gg/v1/lobbies/ready");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "{}");
    RR_RIVET_CURL_EPILOGUE
#endif
}

void rr_rivet_lobbies_set_closed(char const *lobby_token, int closed)
{
#ifdef RR_SERVER
    cJSON *root = cJSON_CreateObject();
    cJSON_AddBoolToObject(root, "is_closed", closed);
    char *post_data = cJSON_Print(root);

    RR_RIVET_CURL_PROLOGUE
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
    curl_easy_setopt(curl, CURLOPT_URL,
                     "https://matchmaker.api.rivet.gg/v1/lobbies/closed");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);
    RR_RIVET_CURL_EPILOGUE

    free(post_data);
    cJSON_Delete(root);
#endif
}

int rr_rivet_players_connected(char const *lobby_token,
                               char const *player_token)
{
#ifdef RR_SERVER
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "player_token", player_token);
    char *post_data = cJSON_Print(root);

    RR_RIVET_CURL_PROLOGUE
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_URL,
                     "https://matchmaker.api.rivet.gg/v1/players/connected");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);
    err = curl_easy_perform(curl);
    assert(!err);

    long http_code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

    free(post_data);
    cJSON_Delete(root);
    curl_easy_cleanup(curl);
    curl_slist_free_all(list);
    return http_code == 200;
#endif
    return 1;
}

void rr_rivet_players_disconnected(char const *lobby_token,
                                   char const *player_token)
{
#ifdef RR_SERVER
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "player_token", player_token);
    char *post_data = cJSON_Print(root);

    RR_RIVET_CURL_PROLOGUE
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_URL,
                     "https://matchmaker.api.rivet.gg/v1/players/disconnected");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);
    RR_RIVET_CURL_EPILOGUE

    free(post_data);
    cJSON_Delete(root);
#endif
}

// public token:
// pub_prod.eyJ0eXAiOiJKV1QiLCJhbGciOiJFZERTQSJ9.COPzyfqCMhDjm4W9jTEaEgoQjQm4bpQTSoibNAqQ6PIoSiIWGhQKEgoQBM-6Z-llSJm8ubdJfMaGOw.QAFVReaGxf6gfYm5NLa1FI6tLCVa2lBKCgbpmdXcuL3_okSrtYqlB9TeTTqZlYLxOMNcMyxnulzY0d5K4JTwCw

void rr_rivet_lobbies_find(void *captures)
{
    puts("finding rivet lobby");
#ifdef EMSCRIPTEN
    EM_ASM(
        {
            fetch("https://matchmaker.api.rivet.gg/v1/lobbies/find", {
                headers : {
                    Authorization :
                        // clang-format off
                        "Bearer pub_prod.eyJ0eXAiOiJKV1QiLCJhbGciOiJFZERTQSJ9.COPzyfqCMhDjm4W9jTEaEgoQjQm4bpQTSoibNAqQ6PIoSiIWGhQKEgoQBM-6Z-llSJm8ubdJfMaGOw.QAFVReaGxf6gfYm5NLa1FI6tLCVa2lBKCgbpmdXcuL3_okSrtYqlB9TeTTqZlYLxOMNcMyxnulzY0d5K4JTwCw"
                    // clang-format on
                },
                method : "POST",
                body : '{"game_modes":["default"]}'
            })
                .then(function(r) { return r.json(); })
                .then(function(json) {
                    const host = json.ports.default.hostname;
                    const token = "Bearer " + json.player.token;
                    const $host = _malloc(host.length + 1);
                    const $token = _malloc(1 + token.length);
                    for (let i = 0; i < host.length; i++)
                        HEAPU8[$host + i] = host[i].charCodeAt();
                    for (let i = 0; i < token.length; i++)
                        HEAPU8[$token + i] = token[i].charCodeAt();
                    $host[host.length] = 0;
                    $token[token.length] = 0;
                    Module._rr_rivet_lobby_on_find($host, $token,
                                                   json.ports.default.port, $0);
                });
        },
        captures);
#endif
}
