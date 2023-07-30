#include <Client/Storage.h>

#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

#include <Client/Game.h>
#include <Shared/pb.h>

uint8_t storage_result[16 * 1024] = {0};

uint32_t rr_local_storage_get(char *name)
{
#ifdef EMSCRIPTEN
    return EM_ASM_INT(
        {
            let string = Module.ReadCstr($0);
            if (!window.localStorage[string])
                return 0;
            string = new TextEncoder().encode(window.localStorage[string]);
            Module.HEAPU8.set(string, $1);
            return string.length;
        },
        name, &storage_result);
#endif

    return 0;
}

void rr_local_storage_store_string(char *name, char *contents)
{
#ifdef EMSCRIPTEN
    EM_ASM(
        {
            const string = Module.ReadCstr($0);
            const string2 = Module.ReadCstr($1);
            window.localStorage[string] = string2;
        },
        name, contents);
#endif
}

void rr_local_storage_store_bytes(char *label, void const *bytes, uint64_t size)
{
#ifdef EMSCRIPTEN
    EM_ASM(
        {
            const string = Module.ReadCstr($0);
            let bytes = HEAPU8.subarray($1, $1 + $2);
            // clang-format breaks arrow functions into = > and causes a syntax
            // error in the javascript

            // clang-format off
            // size of this localstorage shit literally means exactly nothing.
            // stuff won't get larger than 100 bytes and if it does, still who
            // even cares?
            let hex = [...bytes].map(x => x.toString(16)).join(" ");
            localStorage[string] = hex;
            // clang-format on
        },
        label, bytes, size);
#endif
}

uint32_t rr_local_storage_get_bytes(char *label, void *bytes)
{
#ifdef EMSCRIPTEN
    return EM_ASM_INT(
        {
            const string = Module.ReadCstr($0);
            let hex = localStorage[string];
            if (!hex)
                return 0;
            // clang-format off
            let bytes = new Uint8Array(hex.split(" ").map(x => parseInt(x, 16)));
            // clang-format on
            const len = bytes.length;
            HEAPU8.set(bytes, $1);
            return len;
        },
        label, bytes);
#endif
}

void rr_local_storage_store_id_rarity(char *label, uint32_t *start, uint8_t id_count, uint8_t rarity_count)
{
    uint32_t at = 0;
    for (uint8_t id = 0; id < id_count; ++id)
    {
        for (uint8_t rarity = 0; rarity < rarity_count; ++rarity)
        {
            if (start[id * rarity_count + rarity] == 0)
                continue;
            storage_result[at++] = id;
            storage_result[at++] = rarity;
            uint32_t amount = start[id * rarity_count + rarity];
            while (amount > 127ull)
            {
                storage_result[at++] = (amount << 1) | 1;
                amount >>= 7ull;
            }
            storage_result[at++] = amount << 1;
        }
    }
    rr_local_storage_store_bytes(label, &storage_result[0], at);
}

void rr_local_storage_get_id_rarity(char *label, uint32_t *start, uint8_t id_count, uint8_t rarity_count)
{
    uint32_t size = rr_local_storage_get_bytes(label, &storage_result[0]);
    uint32_t at = 0;
    while (at < size)
    {
        uint8_t id = storage_result[at++];
        uint8_t rarity = storage_result[at++];
        uint8_t byte;
        uint32_t count = 0ull;
        uint64_t shift = 0ull;
        do
        {
            byte = storage_result[at++];
            count |= ((byte & 254ull) << shift) >> 1;
            shift += 7ull;
        } while (byte & 1ull);
        start[id * rarity_count + rarity] = count;
    }
}
