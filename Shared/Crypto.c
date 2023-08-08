#include <Shared/Crypto.h>

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <Shared/MagicNumber.h>

// https://github.com/shiffthq/chacha20/blob/master/src/chacha20.c
static inline void u32t8le(uint32_t v, uint8_t p[4])
{
    p[0] = v & 0xff;
    p[1] = (v >> 8) & 0xff;
    p[2] = (v >> 16) & 0xff;
    p[3] = (v >> 24) & 0xff;
}

static inline uint32_t u8t32le(uint8_t p[4])
{
    uint32_t value = p[3];

    value = (value << 8) | p[2];
    value = (value << 8) | p[1];
    value = (value << 8) | p[0];

    return value;
}

static inline uint32_t rotl32(uint32_t x, int n)
{
    // http://blog.regehr.org/archives/1063
    return x << n | (x >> (-n & 31));
}

// https://tools.ietf.org/html/rfc7539#section-2.1
static void chacha20_quarterround(uint32_t *x, int a, int b, int c, int d)
{
    x[a] += x[b];
    x[d] = rotl32(x[d] ^ x[a], 16);
    x[c] += x[d];
    x[b] = rotl32(x[b] ^ x[c], 12);
    x[a] += x[b];
    x[d] = rotl32(x[d] ^ x[a], 8);
    x[c] += x[d];
    x[b] = rotl32(x[b] ^ x[c], 7);
}

static void chacha20_serialize(uint32_t in[16], uint8_t output[64])
{
    int i;
    for (i = 0; i < 16; i++)
    {
        u32t8le(in[i], output + (i << 2));
    }
}

static void chacha20_block(uint32_t in[16], uint8_t out[64], int num_rounds)
{
    int i;
    uint32_t x[16];

    memcpy(x, in, sizeof(uint32_t) * 16);

    for (i = num_rounds; i > 0; i -= 2)
    {
        chacha20_quarterround(x, 0, 4, 8, 12);
        chacha20_quarterround(x, 1, 5, 9, 13);
        chacha20_quarterround(x, 2, 6, 10, 14);
        chacha20_quarterround(x, 3, 7, 11, 15);
        chacha20_quarterround(x, 1, 5, 10, 15);
        chacha20_quarterround(x, 1, 6, 11, 14);
        chacha20_quarterround(x, 2, 7, 8, 13);
        chacha20_quarterround(x, 3, 4, 9, 14);
    }

    for (i = 0; i < 16; i++)
    {
        x[i] += in[i];
    }

    chacha20_serialize(x, out);
}

// https://tools.ietf.org/html/rfc7539#section-2.3
static void chacha20_init_state(uint32_t s[16], uint8_t key[32],
                                uint32_t counter, uint8_t nonce[12])
{
    int i;

    // refer:
    // https://dxr.mozilla.org/mozilla-beta/source/security/nss/lib/freebl/chacha20.c
    // convert magic number to string: "expand 32-byte k"
    s[0] = 0x61707865 ^ 0xfeedface;
    s[1] = 0x3320646e ^ 0xfacefeed;
    s[2] = 0x79622d32 ^ 0xdeadbeef;
    s[3] = 0x6b206574 ^ 0xbeefdaed;

    for (i = 0; i < 8; i++)
    {
        s[4 + i] = u8t32le(key + i * 4);
    }

    s[12] = counter;

    for (i = 0; i < 3; i++)
    {
        s[13 + i] = u8t32le(nonce + i * 4);
    }
}

static void ChaCha20XOR(uint8_t key[32], uint32_t counter, uint8_t nonce[12],
                        uint8_t *in, uint8_t *out, int inlen)
{
    int i, j;

    uint32_t s[16];
    uint8_t block[64];

    chacha20_init_state(s, key, counter, nonce);

    for (i = 0; i < inlen; i += 64)
    {
        chacha20_block(s, block, 20);
        s[12]++;

        for (j = i; j < i + 64; j++)
        {
            if (j >= inlen)
            {
                break;
            }
            out[j] = in[j] ^ block[j - i];
        }
    }
}

uint64_t rr_get_hash(uint64_t x)
{
    x = (x + 1) * (100000 ^ RR_SECRET8);
    x ^= x << 17;
    x ^= x >> 13;
    x ^= x << 5;
    return x;
}

static uint64_t g_random_seed = 123123213231231123;

uint64_t rr_get_rand() { return g_random_seed = rr_get_hash(g_random_seed); }

void rr_encrypt(uint8_t *start, uint64_t size, uint64_t key)
{
    uint8_t *clone = malloc(size);
    memcpy(clone, start, size);
    uint64_t cipher_key[4];
    // idk what the nonce is for but it gets initialized with random bytes
    uint32_t nonce[3];
    // also don't know what the point in the counter is but it is also random
    // bytes for this
    uint32_t counter;
    for (uint64_t i = 0; i < 4; i++)
        cipher_key[i] = key = rr_get_hash(
            rr_get_hash(rr_get_hash(rr_get_hash(rr_get_hash(key)))));
    for (uint64_t i = 0; i < 3; i++)
        nonce[i] = key = rr_get_hash(rr_get_hash(key));
    counter = rr_get_hash(key);

    ChaCha20XOR((uint8_t *)cipher_key, counter, (uint8_t *)nonce, clone, start,
                size);
    free(clone);
}

void rr_decrypt(uint8_t *start, uint64_t size, uint64_t key)
{
    // encrypt and decrypt are the same
    rr_encrypt(start, size, key);
}
