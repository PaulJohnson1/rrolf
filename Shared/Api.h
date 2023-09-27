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
#define RR_API_SECRET "the_rrolf_api_secret_key_that_no_one_will_guess"
#endif

struct rr_api_account
{
    double xp;
    char *username;
    char *password;
    uint32_t maximum_wave;
    uint32_t petals[rr_petal_id_max][rr_rarity_id_max];
    uint8_t already_playing;
};

extern void rr_api_on_get_petals(char *, void *);
void rr_api_on_craft_result(char *, void *);

void rr_api_get_petals(char const *, char const *, void *);
void rr_api_craft_petals(char const *, char const *, char const *, void *);
void rr_api_get_password(char const *, void *);

void rr_api_get_server_alias(char const *, void *);