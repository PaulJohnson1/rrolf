#include <Shared/Api.h>

#include <assert.h>
#include <string.h>

#ifndef EMSCRIPTEN
#include <curl/curl.h>
#else
#include <emscripten.h>
#endif

#define RR_RIVET_CURL_PROLOGUE                                                 \
    int err = 0;                                                               \
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
    char url[500];
    RR_RIVET_CURL_PROLOGUE
    snprintf(url, sizeof(url), "https://rrolf.io/api/user_get/%s/%s",
             param_1, param_2);
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    RR_RIVET_CURL_EPILOGUE
    rr_api_on_get_petals(readBuffer, captures);
#else
    EM_ASM(
        {
        fetch("https://rrolf.io/api/user_get/" + UTF8ToString($0) + '/' + UTF8ToString($1))
        .then(response => response.text())
        .then(data => {
            var len = (data.length << 2) + 1;
            ret = stackAlloc(len);
            stringToUTF8(data, ret, len);
            Module._rr_api_on_get_petals(ret, $2);
        });
        },
        param_1, param_2, captures);
#endif
}

void rr_api_craft_petals(char const *param_1, char const *param_2,
                           char const *param_3, void *captures)
{
#ifndef EMSCRIPTEN
    char readBuffer[50000] = {0};
    char url[500];
    RR_RIVET_CURL_PROLOGUE
    snprintf(url, sizeof(url), "https://rrolf.io/user_craft_petals/%s/%s/%s",
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
        fetch("https://rrolf.io/user_craft_petals/" + UTF8ToString($0) + '/' + UTF8ToString($1) + '/' + UTF8ToString($2))
        .then(response => response.text())
        .then(data => {
            var fn = Module.cwrap('rr_api_on_craft_result', null, ['string']);
            fn(data);
        });
        },
        param_1, param_2, param_3);
#endif
}
