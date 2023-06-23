#include <Client/Game.h>
#include <Client/InputData.h>
#include <Client/Renderer/Renderer.h>
#include <Client/Simulation.h>
#include <Client/Socket.h>
#include <Shared/Bitset.h>

#include <stdio.h>
#include <stdint.h>

#ifndef EMSCRIPTEN
#include <sys/time.h>
#include <unistd.h>
#endif

#ifdef EMSCRIPTEN
#include <emscripten.h>
void rr_key_event(struct rr_game *this, uint8_t type, uint32_t key)
{
    if (type == 1)
    {
        rr_bitset_set(this->input_data->keys_pressed, key);
        rr_bitset_set(this->input_data->keys_pressed_this_tick, key);
    }
    else
    {
        rr_bitset_unset(this->input_data->keys_pressed, key);
        rr_bitset_unset(this->input_data->keys_released_this_tick, key);
    }
}

void rr_mouse_event(struct rr_game *this, float x, float y, uint8_t state, uint8_t button)
{
    this->input_data->mouse_x = x;
    this->input_data->mouse_y = y;
    this->input_data->mouse_state = state;
    if (state == 1) // press down
    {
        this->input_data->mouse_buttons |= (1 << button);
    }
    else if (state == 0)
    {
        this->input_data->mouse_buttons &= ~(1 << button);
        //this->input_data->mouse_buttons_this_tick &= ~(1 << button);
        this->input_data->mouse_buttons_this_tick |= (1 << button);
    }
}

void rr_wheel_event(struct rr_game *this, float delta)
{
    this->input_data->scroll_delta = delta;
}
#else
#endif

void rr_main_renderer_initialize(struct rr_game *this)
{
#ifdef EMSCRIPTEN
    EM_ASM({
        document.oncontextmenu = function() { return false; };
        Module.canvas = document.createElement("canvas");
        Module.canvas.id = "canvas";
        document.body.appendChild(Module.canvas);
        Module.ctxs = [Module.canvas.getContext('2d')];
        Module.availableCtxs = new Array(128).fill(0).map(function(_, i) { return i; });
        window.addEventListener(
            "keydown", function({which}) { Module._rr_key_event($0, 1, which); });
        window.addEventListener(
            "keyup", function({which}) { Module._rr_key_event($0, 0, which); });
        window.addEventListener("mousedown", function({clientX, clientY, button}){Module._rr_mouse_event($0, clientX * devicePixelRatio, clientY * devicePixelRatio, 1, +!!button)});
        window.addEventListener("mousemove", function({clientX, clientY, button}){Module._rr_mouse_event($0, clientX * devicePixelRatio, clientY * devicePixelRatio, 2, +!!button)});
        window.addEventListener("mouseup", function({clientX, clientY, button}){Module._rr_mouse_event($0, clientX * devicePixelRatio, clientY * devicePixelRatio, 0, +!!button)});
        window.addEventListener("wheel", function({deltaY}){Module._rr_wheel_event($0, deltaY)});
        Module.paths = new Array(128).fill(null);
        Module.availablePaths = new Array(128).fill(0).map(function(_, i) { return i; });
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
                const ocanvas = new OffscreenCanvas(1, 1);
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
            const start = ptr;
            while (Module.HEAPU8[ptr++]);
            return new TextDecoder().decode(Module.HEAPU8.subarray(start, ptr));
        };
        function loop(time)
        {
            if (window.start == null)
                window.start = time + 1;
            const delta = Math.min(0.5, (time - start) / 1000);
            start = time;
            Module.canvas.width = innerWidth * devicePixelRatio;
            Module.canvas.height = innerHeight * devicePixelRatio;
            Module._rr_renderer_main_loop($0, delta, Module.canvas.width, Module.canvas.height, devicePixelRatio);
            requestAnimationFrame(loop);
        };
        requestAnimationFrame(loop);
    },
           this);
#endif
}

void rr_renderer_main_loop(struct rr_game *this, float delta, float width, float height, float device_pixel_ratio)
{
    float a = height / 1080;
    float b = width / 1920;

    float scale = (this->renderer->scale = b < a ? a : b);
    this->renderer->width = width;
    this->renderer->height = height;
    this->global_container->lerp_x = this->global_container->x = width * 0.5 / scale;
    this->global_container->lerp_y = this->global_container->y = height * 0.5 / scale;
    this->global_container->width = width / scale;
    this->global_container->height = height / scale;
    rr_game_tick(this, delta);
    this->input_data->scroll_delta = 0;
}

int main()
{
    puts("client init");
    static struct rr_game game;
    static struct rr_renderer renderer;
    static struct rr_input_data input_data;
    static struct rr_simulation simulation;
    rr_main_renderer_initialize(&game);

    rr_renderer_init(&renderer);
    rr_game_init(&game);
    rr_input_data_init(&input_data);
    rr_simulation_init(&simulation);

    game.renderer = &renderer;
    game.input_data = &input_data;
    game.simulation = &simulation;
    rr_game_tick(&game, 1);

#ifndef EMSCRIPTEN
    while (1)
    {
        struct timeval start;
        struct timeval end;
        gettimeofday(&start, NULL);
        rr_game_tick(&game, 0.016f);
        gettimeofday(&end, NULL);
        long elapsed_time = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
        if (elapsed_time > 1000)
            printf("tick took %ld microseconds\n", elapsed_time);
        long to_sleep = 16666 - elapsed_time;
        usleep(to_sleep > 0 ? to_sleep : 0);
    }
#endif

    puts("main end (shouldn't see this hopefully)");
    return 0;
}
