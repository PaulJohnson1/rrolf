#include <Shared/Bitset.h>

int rr_bitset_get_bit(uint8_t *a, uint64_t i)
{
    return a[i >> 3] & (1 << (i & 7));
}

int rr_bitset_get(uint8_t *a, uint64_t i)
{
    return (a[i >> 3] & (1 << (i & 7))) ? 1 : 0;
}

void rr_bitset_set(uint8_t *a, uint64_t i)
{
    a[i >> 3] |= 1 << (i & 7);
}

void rr_bitset_unset(uint8_t *a, uint64_t i)
{
    a[i >> 3] &= ~(1 << (i & 7));
}
