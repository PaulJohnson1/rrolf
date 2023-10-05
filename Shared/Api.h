#pragma once

#include <Shared/StaticData.h>
#include <Shared/Utilities.h>

#ifdef RIVET_BUILD
#define RR_BASE_API_URL "https://rrolf.io/api/"
#else
#define RR_BASE_API_URL "http://localhost:55554/api/"
#endif
#ifdef RR_SERVER
#define RR_API_SECRET                                                          \
    "ad904nf3adrgnariwpanyf3qap8unri4t9b384wna3g34ytgdr4bwtvd4y"
#else
#define RR_API_SECRET "function a(b) { return k[b], aa[n.v], r.eG[g.b]; };"
#endif

void rr_api_get_password(char const *, void *);

void rr_api_get_server_alias(char const *, void *);