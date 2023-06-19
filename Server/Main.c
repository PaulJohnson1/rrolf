#include <fenv.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <Server/Logs.h>
#include <Server/Server.h>
#include <Shared/Utilities.h>
#include <Shared/StaticData.h>
#include <Shared/Rivet.h>

int main()
{
#ifndef NDEBUG
    feenableexcept(FE_DIVBYZERO | FE_INVALID);
#endif
    curl_global_init(CURL_GLOBAL_ALL);
    rr_discord_webhook_log("server startup", "running "
#ifdef NDEBUG
                                             "release (NDEBUG)"
#else
                                             "debug (!NDEBUG)"
#endif
                                             " build with "
#ifdef RIVET_BUILD
                                             "rivet"
#elif RR_WINDOWS
                                             "development windows machine"
#else
                                             "development linux machine"
#endif
    );
#ifdef RIVET_BUILD
    char const *lobby_token = getenv("RIVET_LOBBY_TOKEN");
    if (!lobby_token)
    {
        fputs("using rivet build without rivet lboby token env var set\n", stderr);
        abort();
    }
    rr_rivet_lobbies_ready(lobby_token);
#else

#endif
    struct rr_server *s = malloc(sizeof *s);
    rr_server_init(s);
    rr_server_run(s);
    rr_server_free(s);
}
