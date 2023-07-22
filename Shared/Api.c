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
    char url[500] = {0};
    RR_RIVET_CURL_PROLOGUE
    snprintf(url, sizeof(url), "https://rrolf.io/api/user_get/%s/%s", param_1,
             param_2);
    printf("url is %s\n", url);
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    RR_RIVET_CURL_EPILOGUE
    rr_api_on_get_petals(readBuffer, captures);
#else
    EM_ASM(
        {
            fetch("https://rrolf.io/api/user_get/" + UTF8ToString($0) + '/' +
                  UTF8ToString($1))
                .then(function(response){return response.text()})
                .then(function(data) {
                    const $a = _malloc(1 + data.length);
                    for (let i = 0; i < data.length; i++)
                        HEAPU8[$a + i] = data[i].charCodeAt();
                    HEAPU8[$a + data.length] = 0;
                    Module._rr_api_on_get_petals($a, $2);
                });
        },
        param_1, param_2, captures);
#endif
}

void rr_api_merge_petals(char const *id, char const *petals)
{
#ifndef EMSCRIPTEN
    char url[5000] = {0};
    RR_RIVET_CURL_PROLOGUE
    printf("merging %p into %p\n", petals, id);
    printf("merging %s into %s\n", petals, id);
    snprintf(url, sizeof(url),
             "https://rrolf.io/api/user_merge_petals/%s/%s/%s", RR_API_SECRET,
             id, petals);
    curl_easy_setopt(curl, CURLOPT_URL, url);
    RR_RIVET_CURL_EPILOGUE
#endif
}
void rr_api_craft_petals(char const *param_1, char const *param_2,
                         char const *param_3, void *captures)
{
#ifndef EMSCRIPTEN
    char readBuffer[50000] = {0};
    char url[500] = {0};
    RR_RIVET_CURL_PROLOGUE
    snprintf(url, sizeof(url),
             "https://rrolf.io/api/user_craft_petals/%s/%s/%s", param_1,
             param_2, param_3);
    curl_easy_setopt(curl, CURLOPT_HTTPPOST, 1);
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    RR_RIVET_CURL_EPILOGUE
    rr_api_on_craft_result(readBuffer, captures);
#else
    EM_ASM(
        {
            fetch("https://rrolf.io/api/user_craft_petals/" + UTF8ToString($0) +
                  '/' + UTF8ToString($1) + '/' + UTF8ToString($2))
                .then(function(response){return response.text()})
                .then(function(data) {
                    const $a = _malloc(1 + data.length);
                    for (let i = 0; i < data.length; i++)
                        HEAPU8[$a + i] = data[i].charCodeAt();
                    HEAPU8[$a + data.length] = 0;
                    Module._rr_api_on_craft_result($a, $3);
                });
        },
        param_1, param_2, param_3, captures);
#endif
}
