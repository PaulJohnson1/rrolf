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

void rr_api_get_petals(char const *param_1, char const *param_2, void *captures)
{
#ifndef EMSCRIPTEN
    char readBuffer[50000] = {0};
    char url[5000] = {0};
    RR_RIVET_CURL_PROLOGUE
    snprintf(url, sizeof(url), RR_BASE_API_URL "user_get/%s/%s", param_1, param_2);
    //printf("url is %s\n", url);
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    RR_RIVET_CURL_EPILOGUE
    rr_api_on_get_petals(readBuffer, captures);
#else
    EM_ASM(
        {
            fetch(UTF8ToString($3) + "user_get/" + UTF8ToString($0) + '/' +
                  UTF8ToString($1))
                .then(function(response){return response.arrayBuffer()})
                .then(function(data) {
                    data = new Uint8Array(data);
                    const $a = _malloc(data.length);
                    HEAPU8.set(data, $a);
                    Module._rr_api_on_get_petals($a, $2);
                    _free($a);
                });
        },
        param_1, param_2, captures, RR_BASE_API_URL);
#endif
}

void rr_api_craft_petals(char const *param_1, char const *param_2,
                         char const *param_3, void *captures)
{
#ifndef EMSCRIPTEN
    char readBuffer[50000] = {0};
    char url[500] = {0};
    RR_RIVET_CURL_PROLOGUE
    snprintf(url, sizeof(url), RR_BASE_API_URL "user_craft_petals/%s/%s/%s",
             param_1, param_2, param_3);
    curl_easy_setopt(curl, CURLOPT_HTTPPOST, 1);
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    RR_RIVET_CURL_EPILOGUE
    rr_api_on_craft_result(readBuffer, captures);
#else
    EM_ASM(
        {
            fetch(UTF8ToString($4) + "user_craft_petals/" + UTF8ToString($0) +
                  '/' + UTF8ToString($1) + '/' + UTF8ToString($2))
                .then(function(response){return response.arrayBuffer()})
                .then(function(data) {
                    data = new Uint8Array(data);
                    const $a = _malloc(data.length);
                    HEAPU8.set(data, $a);
                    Module._rr_api_on_craft_result($a, $3);
                    _free($a);
                });
        },
        param_1, param_2, param_3, captures, RR_BASE_API_URL);
#endif
}

void rr_api_get_password(char const *token, void *captures)
{
#ifdef EMSCRIPTEN
    EM_ASM(
        {
            fetch(UTF8ToString($0) + "user_get_password/" + UTF8ToString($1)).then(x => x.text()).then(pw => {
                    const $pw = _malloc(pw.length + 1);
                    for (let i = 0; i < pw.length; i++)
                        HEAPU8[$pw + i] = pw[i].charCodeAt();
                    HEAPU8[$pw + pw.length] = 0;
                    Module._rr_api_on_get_password($pw, $2);
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
                fetch("https://matchmaker.api.rivet.gg/v1/lobbies/join", {
                headers : {
                    Authorization :
                        // clang-format off
                        "Bearer pub_prod.eyJ0eXAiOiJKV1QiLCJhbGciOiJFZERTQSJ9.COPzyfqCMhDjm4W9jTEaEgoQjQm4bpQTSoibNAqQ6PIoSiIWGhQKEgoQBM-6Z-llSJm8ubdJfMaGOw.QAFVReaGxf6gfYm5NLa1FI6tLCVa2lBKCgbpmdXcuL3_okSrtYqlB9TeTTqZlYLxOMNcMyxnulzY0d5K4JTwCw"
                    // clang-format on
                },
                method : "POST",
                body : '{"lobby_id":"' + data + '"}'
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
                    HEAPU8[$host + host.length] = 0;
                    HEAPU8[$token + token.length] = 0;
                    Module._rr_rivet_lobby_on_find($host, $token, json.ports.default.port, $2);
                    _free($host);
                    _free($token);
                })
                .catch(function(error) {
                    Module._rr_rivet_lobby_on_find(0, 0, 0, $2);
                });
            });
        },
        param_1, RR_BASE_API_URL, game);
#endif
}