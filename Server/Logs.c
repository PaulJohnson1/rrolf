#include <Server/Logs.h>

#include <assert.h>

#ifndef RR_DISABLE_DISCORD_INTEGRATION
#include <curl/curl.h>

static void escape_invalid_json(char *json)
{
    
}

void rr_discord_webhook_log(char *name, char *value)
{
    CURL *curl = curl_easy_init();
    CURLcode result;

    struct curl_slist *headers = 0;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    assert(curl);
    curl_easy_setopt(curl, CURLOPT_URL, "https://canary.discord.com/api/webhooks/1114420424277770250/e0cMQafY8B5cJBJ0FadAqjvjQgC43O5vVCsk58uv5y9tZB9CWYrXk-P9zdWFxljSEcds");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, ""
        "{"
            "\"username\": \"rrolf logger\","
            "\"embeds\": "
            "["
                "{"
                    "\"color\": 5460223,"
                    "\"title\": \"%s\","
                    "\"description\": \"%s\""
                "}"
            "]"
        "}"
    );
    result = curl_easy_perform(curl);
    assert(result == CURLE_OK);
    curl_easy_cleanup(curl);
}

void rr_discord_curl_init()
{
    curl_global_init(CURL_GLOBAL_ALL);
}
#endif
