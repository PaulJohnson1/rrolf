#include <fenv.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <Server/Server.h>
#include <Shared/Encoder.h>
#include <Shared/Utilities.h>
#include <Shared/Bitset.h>

uint64_t a = 0;
uint64_t b = 0;

void rr_bitset_for_each_bit_function(uint64_t bit, void *captures)
{
    a += bit;
}

void rr_bitset_for_each_bit_old_function(uint64_t bit, void *captures)
{
    b += bit;
}

#define RR_TEST_BITSET_SIZE ((100000000 + 7) >> 3)

int main()
{
    uint8_t *test_bitset = malloc(RR_TEST_BITSET_SIZE);
    uint8_t *test_bitset_end = test_bitset + RR_TEST_BITSET_SIZE;
    memset(test_bitset, 0, test_bitset_end - test_bitset);
    for (uint64_t i = 0; i < 10000000; i++)
        if (rand() & 1)
            rr_bitset_set(test_bitset, rand() % 10000000);
    for (uint64_t i = 0; i < 10000000; i++)
        if (rand() & 1)
            rr_bitset_set(test_bitset, rand() % 10000000 + 10000000);
    for (uint64_t i = 0; i < 10000000; i++)
        if (rand() & 1)
            rr_bitset_set(test_bitset, rand() % 10000000 + 90000000);

    puts("testing");

    {
        struct timeval start;
        struct timeval end;

        gettimeofday(&start, NULL); // gettimeofday actually starts from unix timestamp 0 (goofy)
        rr_bitset_for_each_bit(test_bitset, test_bitset_end, NULL, rr_bitset_for_each_bit_function);
        gettimeofday(&end, NULL);
        long elapsed_time = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
        printf("new took %ld microseconds %ld, \n", elapsed_time, a);
    }

    {
        struct timeval start;
        struct timeval end;

        gettimeofday(&start, NULL); // gettimeofday actually starts from unix timestamp 0 (goofy)
        rr_bitset_for_each_bit_old(test_bitset, test_bitset_end, NULL, rr_bitset_for_each_bit_old_function);
        gettimeofday(&end, NULL);
        long elapsed_time = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
        printf("old took %ld microseconds %ld\n", elapsed_time, b);
    }

// #ifndef NDEBUG
//     feenableexcept(FE_DIVBYZERO | FE_INVALID);
// #endif

//     struct rr_server s;
//     rr_server_init(&s);
//     struct rr_encoder encoder;
//     static uint8_t data[10000]; // lazy, will change at a later point in time
//     rr_encoder_init(&encoder, data);

    // EntityIdx c = rr_simulation_alloc_entity(&s.simulation);
    // EntityIdx e = rr_simulation_alloc_entity(&s.simulation);
    // struct rr_component_physical *physical = rr_simulation_add_physical(&s.simulation, e);
    // struct rr_component_player_info *player_info = rr_simulation_add_player_info(&s.simulation, c);

    // rr_component_physical_set_radius(physical, 100000.0f);
    // rr_component_player_info_set_camera_fov(player_info, 1.0f);
    // rr_simulation_write_binary(&s.simulation, &encoder, player_info);
    // rr_log_hex(encoder.start, encoder.current);
    // rr_server_run(&s);
    // rr_server_free(&s);
}
