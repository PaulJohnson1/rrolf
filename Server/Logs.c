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

#include <Server/Logs.h>

#include <assert.h>
#include <stdlib.h>

#ifdef RIVET_BUILD
#ifndef RR_DISABLE_DISCORD_INTEGRATION
#include <curl/curl.h>

#include <Shared/cJSON.h>

void rr_discord_webhook_log(char *webhook_name, char *name, char *value,
                            uint32_t color)
{
    CURL *curl = curl_easy_init();
    CURLcode result;

    struct curl_slist *headers = 0;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    assert(curl);
    curl_easy_setopt(
        curl, CURLOPT_URL,
        "https://canary.discord.com/api/webhooks/1114420424277770250/"
        "e0cMQafY8B5cJBJ0FadAqjvjQgC43O5vVCsk58uv5y9tZB9CWYrXk-P9zdWFxljSEcds");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    cJSON *root = cJSON_CreateObject();
    cJSON *embeds = cJSON_CreateArray();
    cJSON *embed = cJSON_CreateObject();

    cJSON_AddItemToObject(root, "username", cJSON_CreateString(webhook_name));
    cJSON_AddItemToObject(root, "embeds", embeds);
    cJSON_AddItemToArray(embeds, embed);
    cJSON_AddItemToObject(embed, "color", cJSON_CreateNumber(color));
    cJSON_AddItemToObject(embed, "title", cJSON_CreateString(name));
    cJSON_AddItemToObject(embed, "description", cJSON_CreateString(value));

    char *post_data = cJSON_Print(root);

    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);
    result = curl_easy_perform(curl);
    assert(result == CURLE_OK);
    curl_easy_cleanup(curl);
    free(post_data);
    cJSON_Delete(root);
    curl_slist_free_all(headers);
}

void rr_discord_curl_init() { curl_global_init(CURL_GLOBAL_ALL); }
#endif
#endif
