#include <Client/DOM.h>

#include <emscripten.h>

void rr_dom_create_text_element(char const *name, uint32_t text_limit)
{
    EM_ASM({
        const name = Module.ReadCstr($0);
        const elem = document.createElement('input');
        elem.id = name;
        elem.type = "text";
        elem.style.position = "absolute";
        elem.style["font-family"] = "Ubuntu";
        document.body.appendChild(elem);
    }, name, text_limit);
}

void rr_dom_element_show(char const *name)
{
    EM_ASM({
        const name = Module.ReadCstr($0);
        const elem = document.getElementById(name);
        elem.style.display = 'block';
    }, name);
}

void rr_dom_element_hide(char const *name)
{
    EM_ASM({
        const name = Module.ReadCstr($0);
        const elem = document.getElementById(name);
        elem.style.display = 'none';
    }, name);
}

void rr_dom_element_update_position(char const *name, float x, float y, float w, float h)
{
    EM_ASM({
        const name = Module.ReadCstr($0);
        const elem = document.getElementById(name);
        elem.style.left = ($1 - $3 / 2) / devicePixelRatio + "px";
        elem.style.top = ($2 - $4 / 2) / devicePixelRatio + "px";
        elem.style.width = $3 / devicePixelRatio + "px";
        elem.style.height = $4 / devicePixelRatio + "px";
    }, name, x, y, w, h);
}

void rr_dom_retrieve_text(char const *name, char *out, uint32_t max_len)
{
    EM_ASM({
        const name = Module.ReadCstr($0);
        const elem = document.getElementById(name);
        let arr = new TextEncoder().encode(elem.value);
        const len = $2 > arr.length ? arr.length : $2;
        // remember off by one errors
        arr = arr.slice(0,len);
        Module.HEAPU8.set(arr, $1);
        Module.HEAPU8[$1 + len] = 0;
    }, name, out, max_len);
}