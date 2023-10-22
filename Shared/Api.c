#include <Shared/Api.h>

#include <assert.h>
#include <string.h>

#ifndef EMSCRIPTEN
#include <curl/curl.h>
#else
#include <emscripten.h>
#endif

#define RR_RIVET_CURL_PROLOGUE                                                 \
    CURLcode err;                                                              \
    CURL *curl = curl_easy_init();                                             \
    assert(curl);

#define RR_RIVET_CURL_EPILOGUE                                                 \
    err = curl_easy_perform(curl);                                             \
    assert(!err);                                                              \
    curl_easy_cleanup(curl);

size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    char *mem = (char *)userp;

    /* copying received data into our memory */
    memcpy(mem, contents, realsize);

    return realsize;
}

void rr_api_get_password(char const *token, void *captures)
{
#ifdef EMSCRIPTEN
    EM_ASM(
        {
            fetch(UTF8ToString($0) + "user_get_password/" + UTF8ToString($1)).then(x => x.text()).then(pw => {
                    const $pw = _malloc(pw.length + 1);
                    HEAPU8.set(new TextEncoder().encode(pw), $pw);
                    HEAPU8[$pw + pw.length] = 0;
                    _rr_api_on_get_password($pw, $2);
                    _free($pw);         
                });
        }, RR_BASE_API_URL, token, captures
    );
#endif
}

void rr_api_get_server_alias(char const *param_1, void *game)
{
#ifdef EMSCRIPTEN
    EM_ASM(
        {
            fetch(UTF8ToString($1) + 'user_get_server_alias/' + UTF8ToString($0)).then(function(x) {return x.text()})
            .then(function(data) {
                if (data === "")
                    return;
                fetch("https://matchmaker.api.rivet.gg/v1/lobbies/join", {
                    "headers": {
                        "Authorization":
                            // clang-format off
                            "Bearer pub_prod.eyJ0eXAiOiJKV1QiLCJhbGciOiJFZERTQSJ9.COPzyfqCMhDjm4W9jTEaEgoQjQm4bpQTSoibNAqQ6PIoSiIWGhQKEgoQBM-6Z-llSJm8ubdJfMaGOw.QAFVReaGxf6gfYm5NLa1FI6tLCVa2lBKCgbpmdXcuL3_okSrtYqlB9TeTTqZlYLxOMNcMyxnulzY0d5K4JTwCw"
                        // clang-format on
                    },
                    "method": "POST",
                    "body": '{"lobby_id":"' + data + '"}'
                })
                    .then(function(r) { return r.json(); })
                    .then(function(json) {
                        const host = json["ports"]["default"]["hostname"];
                        const token = "Bearer " + json["player"]["token"];
                        const $host = _malloc(host.length + 1);
                        const $token = _malloc(1 + token.length);
                        HEAPU8.set(new TextEncoder().encode(host), $host);
                        HEAPU8.set(new TextEncoder().encode(token), $token);
                        HEAPU8[$host + host.length] = 0;
                        HEAPU8[$token + token.length] = 0;
                        _rr_rivet_lobby_on_find($host, $token, json["ports"]["default"]["port"], $2);
                        _free($host);
                        _free($token);
                    })
                    .catch(function(error) {
                        console.log(error);
                        return;//_rr_rivet_lobby_on_find(0, 0, 0, $2);
                    });
            });
        },
        param_1, RR_BASE_API_URL, game);
#endif
}