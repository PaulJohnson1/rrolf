#pragma once

#include <Shared/Utilities.h>

#ifdef RR_SERVER
#define RR_API_SECRET                                                          \
    "ad904nf3adrgnariwpanyf3qap8unri4t9b384wna3g34ytgdr4bwtvd4y"
#else
#define RR_API_SECRET "the_rrolf_api_secret_key_that_no_one_will_guess"
#endif

#define RR_RIVET_CURL_PROLOGUE                                                 \
    int err = 0;                                                               \
    CURL *curl = curl_easy_init();                                             \
    assert(curl);

#define RR_RIVET_CURL_EPILOGUE                                                 \
    err = curl_easy_perform(curl);                                             \
    assert(!err);                                                              \
    curl_easy_cleanup(curl);

void rr_api_on_get_petals(char *, void *);
void rr_api_on_craft_result(char *, void *);

void rr_api_get_petals(char const *id, char const *token, void *);
void rr_api_craft_petals(char const *id, char const *token, char const *petals,
                         void *);
void rr_api_merge_petals(char const *id, char const *petals, void *);
