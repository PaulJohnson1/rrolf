#include <Shared/Bitset.h>

int rr_bitset_get_bit(uint8_t *a, uint64_t i)
{
    return a[i >> 3] & (1 << (i & 7));
}

int rr_bitset_get(uint8_t *a, uint64_t i)
{
    return (a[i >> 3] & (1 << (i & 7))) >> (i & 7);
}

void rr_bitset_set(uint8_t *a, uint64_t i)
{
    a[i >> 3] |= 1 << (i & 7);
}

void rr_bitset_unset(uint8_t *a, uint64_t i)
{
    a[i >> 3] &= ~(1 << (i & 7));
}

void rr_bitset_for_each_bit(uint8_t *start, uint8_t *end, void *captures, void (*cb)(uint64_t, void *))
{
    uint8_t *const original_start = start;
    while (start != end)
    {
        if ((start + 8 < end) && !*(uint64_t *)start)
        {
            start += 8;
            continue;
        }
        if (*start)
        {
            if (*start & 1)
                cb(((start - original_start) << 3) + 0, captures);
            if (*start & 2)
                cb(((start - original_start) << 3) + 1, captures);
            if (*start & 4)
                cb(((start - original_start) << 3) + 2, captures);
            if (*start & 8)
                cb(((start - original_start) << 3) + 3, captures);
            if (*start & 16)
                cb(((start - original_start) << 3) + 4, captures);
            if (*start & 32)
                cb(((start - original_start) << 3) + 5, captures);
            if (*start & 64)
                cb(((start - original_start) << 3) + 6, captures);
            if (*start & 128)
                cb(((start - original_start) << 3) + 7, captures);
        }
        start++;
    }
}

void rr_bitset_for_each_bit_old(uint8_t *start, uint8_t *end, void *captures, void (*cb)(uint64_t, void *))
{
    uint8_t *const original_start = start;
    while (start != end)
    {
        for (uint64_t i = 0; i < 8; i++)
            if (rr_bitset_get_bit(start, i))
                cb(((start - original_start) << 3) + i, captures);
        start++;
    }
}
