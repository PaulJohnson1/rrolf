#include <Client/Storage.h>

#include <emscripten.h>

#include <Client/Game.h>

char *rr_local_storage_get(char *name)
{
#ifdef EMSCRIPTEN
    return (char *) EM_ASM_INT({
        let string = Module.ReadCstr($0);
        if (!window.localStorage[string])
            return 0;
        string = new TextEncoder().encode(window.localStorage[string]);
        const ptr = Module._malloc(string.length + 1);
        Module.HEAPU8.set(string, ptr);
        Module.HEAPU8[ptr + string.length] = 0;
        return ptr;
    }, name); 
#endif
}

void rr_local_storage_set(char *name, char *contents)
{
#ifdef EMSCRIPTEN
    EM_ASM({
        let string = Module.ReadCstr($0);
        let string2 = Module.ReadCstr($1);
        window.localStorage[string] = string2;
    }, name, contents); 
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
        arr[at] = i + 1;
        arr[at + 1] = petal.id;
        arr[at + 2] = petal.rarity + 1;
        at += 3;
    }
    arr[at] = 0;
    rr_local_storage_set("loadout", (char *) &arr);
}