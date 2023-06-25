/**
 * This file is only compiled and linked to the executable if the cmake flag
 * RIVET_BUILD is set.
 */

#include <Shared/Rivet.h>

#include <assert.h>
#include <string.h>

#ifndef WASM_BUILD
#include <curl/curl.h>
#else
#include <emscripten/fetch.h>
#endif

void rr_rivet_lobbies_ready(char const *lobby_token)
{
#ifdef RR_SERVER
    struct curl_slist *list = 0;
    int err = 0;
    CURL *curl = curl_easy_init();
    assert(curl);
    char header[500] = "Authorization: Bearer ";
    list = curl_slist_append(list, strcat(header, lobby_token));
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "{}");
    curl_easy_setopt(curl, CURLOPT_URL, "https://matchmaker.api.rivet.gg/v1/lobbies/ready");
    err = curl_easy_perform(curl);
    assert(!err);
    curl_easy_cleanup(curl);
    curl_slist_free_all(list);
#endif
}

// public token: pub_prod.eyJ0eXAiOiJKV1QiLCJhbGciOiJFZERTQSJ9.COPzyfqCMhDjm4W9jTEaEgoQjQm4bpQTSoibNAqQ6PIoSiIWGhQKEgoQBM-6Z-llSJm8ubdJfMaGOw.QAFVReaGxf6gfYm5NLa1FI6tLCVa2lBKCgbpmdXcuL3_okSrtYqlB9TeTTqZlYLxOMNcMyxnulzY0d5K4JTwCw
// user must free result

// user must define this function.
void rr_rivet_lobby_on_find(char *s, uint16_t port, void *captures);

void rr_rivet_lobbies_find(void *captures)
{
    puts("finding rivet lobby");
    #ifdef WASM_BUILD
        EM_ASM({
            fetch("https://matchmaker.api.rivet.gg/v1/lobbies/find", {
                headers: {
                    Authorization: "Bearer pub_prod.eyJ0eXAiOiJKV1QiLCJhbGciOiJFZERTQSJ9.COPzyfqCMhDjm4W9jTEaEgoQjQm4bpQTSoibNAqQ6PIoSiIWGhQKEgoQBM-6Z-llSJm8ubdJfMaGOw.QAFVReaGxf6gfYm5NLa1FI6tLCVa2lBKCgbpmdXcuL3_okSrtYqlB9TeTTqZlYLxOMNcMyxnulzY0d5K4JTwCw"
                },
                method: "POST",
                body: '{"game_modes":["default"]}'
            })
            .then(r =>
            {
                return r.json();
            })
            .then(json =>
            {
                const host = json.ports.default.hostname;
                const pointer = _malloc(host.length + 1);
                for (let i = 0; i < host.length; i++)
                    HEAPU8[pointer + i] = host[i].charCodeAt();
                pointer[host.length] = 0;
                Module._rr_rivet_lobby_on_find(pointer, json.ports.default.port, $0);
            });
        }, captures);
    #endif
}
