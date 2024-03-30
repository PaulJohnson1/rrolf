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
