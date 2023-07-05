#pragma once

#include <stdint.h>

#define RR_DISCORD_WEBHOOK_URL                                                 \
    "https://canary.discord.com/api/webhooks/1114420424277770250/"             \
    "e0cMQafY8B5cJBJ0FadAqjvjQgC43O5vVCsk58uv5y9tZB9CWYrXk-P9zdWFxljSEcds"

void rr_discord_webhook_log(char *webhook_name, char *name, char *value,
                            uint32_t color);

#ifdef RR_DISABLE_DISCORD_INTEGRATION
#define rr_discord_webhook_log(a, b, c)
#endif
