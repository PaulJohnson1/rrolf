#include <Client/Storage.h>

#include <emscripten.h>

char *rr_local_storage_get(char *name)
{
#ifdef EMSCRIPTEN
    return (char *) EM_ASM_INT({
        let string = Module.ReadCstr($0);
        if (!window.localStorage[string])
            return 0;
        string = new TextEncoder().encode(window.localStorage[string]);
        const ptr = malloc(string.length + 1);
        Module.HEAPU8.set(ptr, string);
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
