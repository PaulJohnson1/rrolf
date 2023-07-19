#include <Client/Storage.h>

#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

#include <Client/Game.h>

uint8_t storage_result[4 * 1024] = {0};

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

void rr_local_storage_store_chunk(char *name, char *contents, uint32_t len)
{
#ifdef EMSCRIPTEN
    EM_ASM(
        {
            const string = Module.ReadCstr($0);
            const string2 =
                new TextDecoder().decode(Module.HEAPU8.subarray($1, $1 + $2));
            window.localStorage[string] = string2;
        },
        name, contents, len);
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

void rr_local_storage_get_bytes(char *label, void *bytes)
{
#ifdef EMSCRIPTEN
    EM_ASM(
        {
            const string = Module.ReadCstr($0);
            let hex = localStorage[string];
            if (!hex)
                return;
            // clang-format off
            let bytes = new Uint8Array(hex.split(" ").map(x => parseInt(x, 16)));
            // clang-format on
            HEAPU8.set(bytes, $1);
        },
        label, bytes);
#endif
}

// void rr_storage_layout_save(struct rr_game *game)
// {
//     uint8_t arr[61];
//     // memset(&arr, 0, sizeof arr);
//     uint8_t at = 0;
//     for (uint8_t i = 0; i < 20; ++i)
//     {
//         struct rr_game_loadout_petal petal = game->loadout[i];
//         if (petal.id == 0)
//             continue;
//         arr[at] = i;
//         arr[at + 1] = petal.id;
//         arr[at + 2] = petal.rarity;
//         at += 3;
//     }
//     arr[at] = 0;
//     rr_local_storage_store_chunk("loadout", (char *)&arr, at);
// }