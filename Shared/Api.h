#pragma once

#include <Shared/StaticData.h>
#include <Shared/Utilities.h>

#ifdef RR_SERVER
#define RR_API_SECRET                                                          \
    "ad904nf3adrgnariwpanyf3qap8unri4t9b384wna3g34ytgdr4bwtvd4y"
#else
#define RR_API_SECRET "the_rrolf_api_secret_key_that_no_one_will_guess"
#endif

#ifdef RIVET_BUILD
#define RR_BASE_API_URL "https://rrolf.io/api/"
#else
#define RR_BASE_API_URL "http://localhost:55554/api/"
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
extern void rr_api_on_craft_result(char *, void *);
extern void rr_api_on_open_result(char *, void *);
extern void rr_api_on_get_password(char *, void *);

extern void rr_api_get_petals(char const *, char const *, void *);
extern void rr_api_craft_petals(char const *, char const *, char const *, void *);
extern void rr_api_on_close(char const *, char const *, uint32_t, char const *);
extern void rr_api_on_open(char const *, void *);
extern void rr_api_get_password(char const *, void *);

extern void rr_api_create_squad(char const *, char const *, void *);
