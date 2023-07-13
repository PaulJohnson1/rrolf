#include <Client/Storage.h>

#include <emscripten.h>

#include <Client/Game.h>

uint8_t storage_result[4 * 1024] = {0};

uint32_t rr_local_storage_get(char *name)
{
#ifdef EMSCRIPTEN
    return EM_ASM_INT({
        let string = Module.ReadCstr($0);
        if (!window.localStorage[string])
            return 0;
        string = new TextEncoder().encode(window.localStorage[string]);
        Module.HEAPU8.set(string, $1);
        return string.length;
    }, name, &storage_result); 
#endif
}

void rr_local_storage_store_string(char *name, char *contents)
{
#ifdef EMSCRIPTEN
    EM_ASM({
        const string = Module.ReadCstr($0);
        const string2 = Module.ReadCstr($1);
        window.localStorage[string] = string2;
    }, name, contents); 
#endif 
}

void rr_local_storage_store_chunk(char *name, char *contents, uint32_t len)
{
#ifdef EMSCRIPTEN
    EM_ASM({
        const string = Module.ReadCstr($0);
        const string2 = new TextDecoder().decode(Module.HEAPU8.subarray($1, $1 + $2));
        window.localStorage[string] = string2;
    }, name, contents, len); 
#endif 
}

void rr_storage_layout_save(struct rr_game *game)
{
    uint8_t arr[61];
    //memset(&arr, 0, sizeof arr);
    uint8_t at = 0;
    for (uint8_t i = 0; i < 20; ++i)
    {
        struct rr_game_loadout_petal petal = game->loadout[i];
        if (petal.id == 0)
            continue;
        arr[at] = i;
        arr[at + 1] = petal.id;
        arr[at + 2] = petal.rarity;
        at += 3;
    }
    arr[at] = 0;
    rr_local_storage_store_chunk("loadout", (char *) &arr, at);
}