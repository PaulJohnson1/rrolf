#include <assert.h>
#include <fenv.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef RIVET_BUILD
#include <curl/curl.h>
#endif

#include <Server/Logs.h>
#include <Server/Server.h>
#include <Shared/Api.h>
#include <Shared/MagicNumber.h>
#include <Shared/Rivet.h>
#include <Shared/StaticData.h>
#include <Shared/Utilities.h>

int main()
{
    fprintf(stderr, "gameserver on version %llu\n", RR_SECRET8 ^ 255);
    srand(time(0));
    // signal(SIGINT, sigint_handle);
#ifdef RIVET_BUILD
    curl_global_init(CURL_GLOBAL_ALL);
#endif
    char startup_message[1000] = {0};
#ifdef NDEBUG
    strcat(startup_message, "release");
#else
    strcat(startup_message, "debug");
#endif
    strcat(startup_message, " build running on ");
#ifdef RIVET_BUILD
    char *version_name = getenv("RIVET_VERSION_NAME");
    char *lobby_id = getenv("RIVET_LOBBY_ID");
    assert(version_name && lobby_id);
    strcat(startup_message, "rivet\nversion: `");
    strcat(startup_message, version_name);
    strcat(startup_message, "`\nlobby id: `");
    strcat(startup_message, lobby_id);
    strcat(startup_message, "`");
#elif RR_WINDOWS
    strcat(startup_message, " windows");
#else
    strcat(startup_message, " linux");
#endif
#ifdef RIVET_BUILD
    rr_discord_webhook_log("server status", "server startup", startup_message,
                           0x4000ff);
    char const *lobby_token = getenv("RIVET_LOBBY_TOKEN");
    if (!lobby_token)
    {
        fputs("using rivet build without rivet lobby token env var set\n",
              stderr);
        abort();
    }
    rr_rivet_lobbies_ready(lobby_token);
#else

#endif
    struct rr_server *s = calloc(1, sizeof *s);
    rr_server_init(s);
    rr_server_run(s);
    rr_server_free(s);
}
