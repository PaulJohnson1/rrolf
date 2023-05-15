#include <Client/Renderer.h>

#include <stdio.h>

#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

void rr_main_renderer_initialize(struct rr_renderer *this)
{
#ifdef EMSCRIPTEN
    EM_ASM({
document.oncontextmenu = function() { return false; };
        Module.canvas = document.createElement("canvas");
        Module.canvas.id = "canvas";
        document.body.appendChild(Module.canvas);
        Module.ctxs = [Module.canvas.getContext('2d')];
        Module.availableCtxs = new Array(100).fill(0).map(function(_, i) { return i; });
        /*
        window.addEventListener(
            "keydown", function({which}) { Module.___Renderer_KeyEvent(1, which); });
        window.addEventListener(
            "keyup", function({which}) { Module.___Renderer_KeyEvent(0, which); });
            */
        // window.addEventListener("mousedown", function({clientX, clientY, button}){Module.___Renderer_MouseEvent(clientX*devicePixelRatio, clientY*devicePixelRatio, 1, button)});
        // window.addEventListener("mousemove", function({clientX, clientY, button}){Module.___Renderer_MouseEvent(clientX*devicePixelRatio, clientY*devicePixelRatio, 2, button)});
        // window.addEventListener("mouseup", function({clientX, clientY, button}){Module.___Renderer_MouseEvent(clientX*devicePixelRatio, clientY*devicePixelRatio, 0, button)});
        Module.paths = [... Array(100)].fill(null);
        Module.availablePaths = new Array(100).fill(0).map(function(_, i) { return i; });
        Module.addPath = function()
        {
            if (Module.availablePaths.length)
            {
                const index = Module.availablePaths.pop();
                Module.paths[index] = new Path2D();
                return index;
            }
            throw new Error('Out of Paths: Can be fixed by allowing more paths');
            return -1;
        };
        Module.removePath = function(index)
        {
            Module.paths[index] = null;
            Module.availablePaths.push(index);
        };
        Module.addCtx = function()
        {
            if (Module.availableCtxs.length)
            {
                const index = Module.availableCtxs.shift();
                if (index == 0)
                    return 0; // used for the main ctx, because that has special behavior
                const ocanvas = new OffscreenCanvas(0, 0);
                Module.ctxs[index] = ocanvas.getContext('2d');
                return index;
            }
            throw new Error('Out of Contexts: Can be fixed by allowing more contexts');
            return -1;
        };
        Module.removeCtx = function(index)
        {
            if (index == 0)
                throw new Error('Tried to delete the main context');
            Module.ctxs[index] = null;
            Module.availableCtxs.push(index);
        };
        Module.ReadCstr = function(ptr)
        {
            let str = "";
            let char;
            while ((char = Module.HEAPU8[ptr++]))
                str += String.fromCharCode(char);
            return str;
        };
        function loop()
        {
            requestAnimationFrame(loop);
            Module.canvas.width = innerWidth * devicePixelRatio;
            Module.canvas.height = innerHeight * devicePixelRatio;
            Module._rr_renderer_main_loop($0, Module.canvas.width, Module.canvas.height, devicePixelRatio);
        };
        requestAnimationFrame(loop);        
    }, this);
#endif
}

void rr_renderer_main_loop(struct rr_renderer *this, float width, float height, float device_pixel_ratio)
{
    rr_renderer_begin_path(this);
    rr_renderer_arc(this, 100, 100, 100);
    rr_renderer_set_fill(this, 0xffff0000);
    rr_renderer_fill(this);
}


int main()
{
    struct rr_renderer renderer;

    rr_renderer_init(&renderer);
    printf("hello %p \n", &renderer);
    rr_main_renderer_initialize(&renderer);

    puts("main end (shouldn't see this hopefully)");

    return 0;
}