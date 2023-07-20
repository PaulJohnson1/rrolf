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

// void rr_bitset_for_each_bit(uint8_t *start, uint8_t *end, void *captures,
//                             void (*cb)(uint64_t, void *))
// {
//     uint8_t *const original_start = start;
//     uint64_t bitmapsize = (end - start) / sizeof(uint64_t);

//     uint64_t bitset;
//     for (uint64_t k = 0; k < bitmapsize; ++k)
//     {
//         bitset = bitmap[k];
//         uint64_t p = k * 64;
//         while (bitset != 0)
//         {
//             if (bitset & 0x1)
//             {
//                 cb(p, captures);
//             }
//             bitset >>= 1;
//             p += 1;
//         }
//     }
// }

// void rr_bitset_for_each_bit(uint8_t *start, uint8_t *end, void *captures,
// void (*cb)(uint64_t, void *))
// {
//     uint8_t *const original_start = start;

//     while (start != end)
//     {
//         if ((start + 8 < end) && (uint64_t)start % 8 == 0)
//         {
//             uint64_t val = *(uint64_t *)start;
//             while (val)
//             {
//                 uint64_t t = __builtin_ctzll(val);
//                 cb(((start - original_start) << 3) | t, captures);
//                 val &= val - 1; // clear the rightmost set bit
//             }
//             start += 8;
//         }
//         else
//         {
//             uint8_t val = *start;
//             while (val)
//             {
//                 uint8_t t = __builtin_ctz(val);
//                 cb(((start - original_start) << 3) | t, captures);
//                 val &= val - 1; // clear the rightmost set bit
//             }
//             start++;
//         }
//     }
// }

void rr_bitset_for_each_bit(uint8_t *start, uint8_t *end, void *captures,
                            void (*cb)(uint64_t, void *))
{
    uint8_t *const original_start = start;

    while (start != end)
    {
        if ((start + 8 < end) && (uint64_t)start % 8 == 0 &&
            !*(uint64_t *)start)
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
