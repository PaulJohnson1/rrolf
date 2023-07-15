#include <assert.h>
#include <fenv.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef RIVET_BUILD
#include <curl/curl.h>
#endif

#include <Server/Logs.h>
#include <Server/Server.h>
#include <Shared/Api.h>
#include <Shared/Rivet.h>
#include <Shared/StaticData.h>
#include <Shared/Utilities.h>

int volatile quitting_already = 0;

void sigint_handle(int s)
{
    fputs("closing server\n", stderr);
    if (quitting_already)
        exit(1234);
    quitting_already = 1;
#ifdef RIVET_BUILD
    char log[1000] = {"lobby id: `"};
    strcat(log, getenv("RIVET_LOBBY_ID"));
    strcat(log, "`");
#else
    char *log =
#ifdef RR_WINDOWS
        "windows"
#else
        "linux"
#endif
        ;
#endif
#ifdef RIVET_BUILD
    rr_discord_webhook_log("server status", "server shutdown", log, 0xff2222);
#endif
}

void rr_api_on_get_petals(char *thing, void *a) { puts(thing); }
void rr_api_on_craft_result(char *thing, void *a) { puts(thing); }

int main()
{
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
