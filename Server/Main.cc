#include <iostream>
#include <fenv.h>
#include <stdlib.h>

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>
#include <curl/curl.h>

#include <Server/Server.hh>
#include <Server/Simulation.hh>

int main()
{
    using namespace app;
    fprintf(stdout, "testing stdout\n");
    fprintf(stderr, "testing stderr\n");


    feenableexcept(FE_INVALID);
#ifdef RIVET_PRODUCTION_BUILD
    // use rivet lobby token
    char const *rivetToken = getenv("RIVET_LOBBY_TOKEN");
#endif
#ifdef RIVET_DEVELOPER_BUILD
    // use rivet developer token
    char const *rivetToken = "dev_prod.eyJ0eXAiOiJKV1QiLCJhbGciOiJFZERTQSJ9.CL3lzszuMRC9jYqP-TAaEgoQ82qwoRgvQ3CWmYJNQPGvSCIvQi0KEgoQBM-6Z-llSJm8ubdJfMaGOxoJMTI3LjAuMC4xIgwKB2RlZmF1bHQQkD8.CXaejTGpSOLMRJAgKI1igFNDI_RjWRteGgwpVo4XTQxA42uMeSkgVs_Xv8_l5r5R0DpbciKQ1_PQp_UZ6au6AA";
#endif

    Server &server = *new Server;
#if defined(RIVET_PRODUCTION_BUILD) || defined(RIVET_DEVELOPER_BUILD)
    // tell rivet the server is ready
    assert(rivetToken);
    curl_slist *list = nullptr;
    CURL *curl = curl_easy_init();
    assert(curl);
    char header[500] = "Authorization: ";
    list = curl_slist_append(list, strcat(header, rivetToken));
    assert(curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list) == CURLE_OK);
    assert(curl_easy_setopt(curl, CURLOPT_POST, 1) == CURLE_OK);
    assert(curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "{}") == CURLE_OK);
    assert(curl_easy_setopt(curl, CURLOPT_URL, "https://matchmaker.api.rivet.gg/v1/lobbies/ready") == CURLE_OK);
    assert(curl_easy_perform(curl) == CURLE_OK);
    curl_easy_cleanup(curl);
    curl_slist_free_all(list);
#endif
    server.Run();
    return 0;
}
