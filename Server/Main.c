#include <fenv.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <Server/Logs.h>
#include <Server/Server.h>
#include <Shared/Utilities.h>
#include <Shared/StaticData.h>

int main()
{
#ifndef NDEBUG
    feenableexcept(FE_DIVBYZERO | FE_INVALID);
#endif
    rr_discord_curl_init();
    rr_discord_webhook_log("server startup", "server started up");
    struct rr_server *s = malloc(sizeof *s);
    rr_server_init(s);
    rr_server_run(s);
    rr_server_free(s);
}
