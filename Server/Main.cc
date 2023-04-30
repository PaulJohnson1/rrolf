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

    feenableexcept(FE_INVALID);
#ifdef RIVET_PRODUCTION_BUILD
    char const *rivetToken = getenv("RIVET_LOBBY_TOKEN");
#endif

    Server &server = *new Server;
#if defined(RIVET_PRODUCTION_BUILD) || defined(RIVET_DEVELOPER_BUILD)
    assert(rivetToken);
    std::cout << "connecting to rivet server with token: " << rivetToken << '\n';
    curl_slist *list = nullptr;
    CURL *curl = curl_easy_init();
    assert(curl);
    char header[500] = "Authorization: Bearer ";
    list = curl_slist_append(list, strcat(header, rivetToken));
    assert(curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list) == CURLE_OK);
    assert(curl_easy_setopt(curl, CURLOPT_POST, 1) == CURLE_OK);
    assert(curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "{}") == CURLE_OK);
    assert(curl_easy_setopt(curl, CURLOPT_URL, "https://matchmaker.api.rivet.gg/v1/lobbies/ready") == CURLE_OK);
    std::cerr << "\n\n\n" << std::to_string(curl_easy_perform(curl)) << "\n\n\n";
    curl_easy_cleanup(curl);
    curl_slist_free_all(list);
#endif
    server.Run();
    return 0;
}
