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

#include <Shared/StaticData.h>
#include <Shared/Utilities.h>

#ifdef RIVET_BUILD
#define RR_BASE_API_URL "https://rrolf.io/api/"
#else
#define RR_BASE_API_URL "https://55554-maxnest0x0-rrolf-4mdcfhgyf5k.ws-eu110.gitpod.io/api/"
#endif
#ifdef RR_SERVER
#define RR_API_SECRET                                                          \
    "ad904nf3adrgnariwpanyf3qap8unri4t9b384wna3g34ytgdr4bwtvd4y"
#else
#define RR_API_SECRET "function a(b) { return k[b], aa[n.v], r.eG[g.b]; };"
#endif

void rr_api_get_password(char const *, void *);

void rr_api_get_server_alias(char const *, void *);