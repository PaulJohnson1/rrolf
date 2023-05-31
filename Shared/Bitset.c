#include <Shared/Bitset.h>

uint8_t rr_bitset_get_bit(uint8_t *a, uint64_t i)
{
    // return a[i];
    return a[i >> 3] & (1 << (i & 7));
}

uint8_t rr_bitset_get(uint8_t *a, uint64_t i)
{
    // return a[i];
    return (a[i >> 3] & (1 << (i & 7))) ? 1 : 0;
}

void rr_bitset_set(uint8_t *a, uint64_t i)
{
    // a[i] = 1;
    a[i >> 3] |= 1 << (i & 7);
}

void rr_bitset_unset(uint8_t *a, uint64_t i)
{
    // a[i] = 0;
    a[i >> 3] &= ~(1 << (i & 7));
}

void rr_bitset_maybe_set(uint8_t *a, uint64_t i, uint8_t bit)
{
    // a[i] = bit;
    if (bit)
        rr_bitset_set(a, i);
    else
        rr_bitset_unset(a, i);
}
void rr_bitset_for_each_bit(uint8_t *start, uint8_t *end, void *captures, void (*cb)(uint64_t, void *))
{
    // uint8_t *const original_start = start;

    // // Iterate over the misaligned bytes
    // while ((uint64_t)start % sizeof(uint64_t))
    // {
    //     if (*start)
    //         cb(start - original_start, captures);
    //     start++;
    // }

    // // Iterate over the aligned uint64_t values
    // for (; start <= (end - sizeof(uint64_t)); start += sizeof(uint64_t))
    //     if (*(uint64_t *)start)
    //     {
    //         uint64_t value = *(uint64_t *)start;
    //         uint64_t offset = start - original_start;

    //         if (*(uint32_t *)start)
    //         {
    //             if (*(uint16_t *)start)
    //             {
    //                 if (*(uint8_t *)start)
    //                     cb(offset, captures);
    //                 if (*((uint8_t *)start + 1))
    //                     cb(offset + 1, captures);
    //             }
    //             if (*((uint16_t *)start + 1))
    //             {
    //                 if (*((uint8_t *)start + 2))
    //                     cb(offset + 2, captures);
    //                 if (*((uint8_t *)start + 3))
    //                     cb(offset + 3, captures);
    //             }
    //         }
    //         if (*((uint32_t *)start + 1))
    //         {
    //             if (*((uint16_t *)start + 2))
    //             {
    //                 if (*((uint8_t *)start + 4))
    //                     cb(offset + 4, captures);
    //                 if (*((uint8_t *)start + 5))
    //                     cb(offset + 5, captures);
    //             }
    //             if (*((uint16_t *)start + 3))
    //             {
    //                 if (*((uint8_t *)start + 6))
    //                     cb(offset + 6, captures);
    //                 if (*((uint8_t *)start + 7))
    //                     cb(offset + 7, captures);
    //             }
    //         }
    //     }

    // // Iterate over the remaining misaligned bytes, if any
    // for (uint8_t *i = start; i < end; i++)
    // {
    //     if (*start)
    //         cb(start - original_start, captures);
    //     start++;
    // }

    uint8_t *const original_start = start;

    while ((uint64_t) start % sizeof(uint64_t))
    {
        if (start == end)
            return;
        if (*start)
        {
            if (*start & 1)
                cb(((start - original_start) << 3) | 0, captures);
            if (*start & 2)
                cb(((start - original_start) << 3) | 1, captures);
            if (*start & 4)
                cb(((start - original_start) << 3) | 2, captures);
            if (*start & 8)
                cb(((start - original_start) << 3) | 3, captures);
            if (*start & 16)
                cb(((start - original_start) << 3) | 4, captures);
            if (*start & 32)
                cb(((start - original_start) << 3) | 5, captures);
            if (*start & 64)
                cb(((start - original_start) << 3) | 6, captures);
            if (*start & 128)
                cb(((start - original_start) << 3) | 7, captures);
        }
        start++;
    }

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
                cb(((start - original_start) << 3) | 0, captures);
            if (*start & 2)
                cb(((start - original_start) << 3) | 1, captures);
            if (*start & 4)
                cb(((start - original_start) << 3) | 2, captures);
            if (*start & 8)
                cb(((start - original_start) << 3) | 3, captures);
            if (*start & 16)
                cb(((start - original_start) << 3) | 4, captures);
            if (*start & 32)
                cb(((start - original_start) << 3) | 5, captures);
            if (*start & 64)
                cb(((start - original_start) << 3) | 6, captures);
            if (*start & 128)
                cb(((start - original_start) << 3) | 7, captures);
        }
        start++;
    }
}
