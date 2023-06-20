#include <fenv.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

#include <curl/curl.h>

#include <Server/Logs.h>
#include <Server/Server.h>
#include <Shared/Utilities.h>
#include <Shared/StaticData.h>
#include <Shared/Rivet.h>

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
    rr_discord_webhook_log("server status", "server shutdown", log, 0xff2222);
}

int main()
{
    signal(SIGINT, sigint_handle);
#ifndef NDEBUG
    feenableexcept(FE_DIVBYZERO | FE_INVALID);
#endif
    curl_global_init(CURL_GLOBAL_ALL);
    char startup_message[1000] = {0};
    char *version_name = getenv("RIVET_VERSION_NAME");
    char *lobby_id = getenv("RIVET_LOBBY_ID");
#ifdef NDEBUG
    strcat(startup_message, "release");
#else
    strcat(startup_message, "debug");
#endif
    strcat(startup_message, " build running on ");
#ifdef RIVET_BUILD
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
    rr_discord_webhook_log("server status", "server startup", startup_message, 0x4000ff);
#ifdef RIVET_BUILD
    char const *lobby_token = getenv("RIVET_LOBBY_TOKEN");
    if (!lobby_token)
    {
        fputs("using rivet build without rivet lobby token env var set\n", stderr);
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
