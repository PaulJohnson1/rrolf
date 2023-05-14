#include <Shared/Bitset.h>

int rr_bitset_get(uint8_t *arr, uint64_t pos)
{
    return arr[pos >> 3] & (1 << (pos & 7)) ? 1 : 0;
}

void rr_bitset_set(uint8_t *arr, uint64_t pos)
{
    arr[pos >> 3] |= 1 << (pos & 7);
}

void rr_bitset_unset(uint8_t *arr, uint64_t pos)
{
    arr[pos >> 3] &= ~(1 << (pos & 7));
}