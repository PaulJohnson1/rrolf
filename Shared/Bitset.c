#include <Shared/Bitset.h>

uint8_t rr_bitset_get_bit(uint8_t *a, uint64_t i)
{
    return a[i >> 3] & (1 << (i & 7));
}

uint8_t rr_bitset_get(uint8_t *a, uint64_t i)
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

void rr_bitset_maybe_set(uint8_t *a, uint64_t i, uint8_t bit)
{
    if (bit)
        rr_bitset_set(a, i);
    else
        rr_bitset_unset(a, i);
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

void rr_bitset_for_each_bit_until(uint8_t *start, uint8_t *end, void *captures, uint8_t (*cb)(uint64_t, void *))
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
                if (cb(((start - original_start) << 3) + 0, captures))
                    return;
            if (*start & 2)
                if (cb(((start - original_start) << 3) + 1, captures))
                    return;
            if (*start & 4)
                if (cb(((start - original_start) << 3) + 2, captures))
                    return;
            if (*start & 8)
                if (cb(((start - original_start) << 3) + 3, captures))
                    return;
            if (*start & 16)
                if (cb(((start - original_start) << 3) + 4, captures))
                    return;
            if (*start & 32)
                if (cb(((start - original_start) << 3) + 5, captures))
                    return;
            if (*start & 64)
                if (cb(((start - original_start) << 3) + 6, captures))
                    return;
            if (*start & 128)
                if (cb(((start - original_start) << 3) + 7, captures))
                    return;
        }
        start++;
    }
}
