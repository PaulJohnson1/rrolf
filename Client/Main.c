#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <Client/Game.h>
#include <Client/InputData.h>
#include <Client/Renderer/Renderer.h>
#include <Client/Simulation.h>
#include <Client/Socket.h>
#include <Shared/Api.h>
#include <Shared/Bitset.h>
#include <Shared/MagicNumber.h>
#include <Shared/Rivet.h>

#ifndef EMSCRIPTEN
#include <glfw/GLFW3.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

static void *rr_create_game_thread(void *arg)
{
    struct rr_game *game = arg;

    while (1)
    {
        struct timeval start;
        struct timeval end;
        gettimeofday(&start, NULL);
        rr_game_tick(game, 0.016f);
        gettimeofday(&end, NULL);
        int64_t elapsed_time = (end.tv_sec - start.tv_sec) * 1000000 +
                               (end.tv_usec - start.tv_usec);
        if (elapsed_time > 1000)
            printf("tick took %ld microseconds\n", elapsed_time);
        int64_t to_sleep = 16666 - elapsed_time;
        if (to_sleep > 0)
            usleep(to_sleep);
        // otherwise don't even call the function
    }

    return 0;
}

#endif

#ifdef EMSCRIPTEN
#include <emscripten.h>
void rr_key_event(struct rr_game *this, uint8_t type, uint32_t which,
                  uint32_t key)
{
    if (type == 1)
    {
        rr_bitset_set(this->input_data->keys_pressed, which);
        rr_bitset_set(this->input_data->keys_pressed_this_tick, which);
        rr_bitset_set(this->input_data->keycodes_pressed_this_tick, key);
    }
    else
    {
        rr_bitset_unset(this->input_data->keys_pressed, which);
        rr_bitset_unset(this->input_data->keys_released_this_tick, which);
    }
}

void rr_mouse_event(struct rr_game *this, float x, float y, uint8_t state,
                    uint8_t button)
{
    this->input_data->mouse_x = x;
    this->input_data->mouse_y = y;
    this->input_data->mouse_state = state;
    if (state == 1) // press down
    {
        this->input_data->mouse_buttons |= (1 << button);
        this->input_data->mouse_buttons_down_this_tick |= (1 << button);
    }
    else if (state == 0)
    {
        this->input_data->mouse_buttons &= ~(1 << button);
        this->input_data->mouse_buttons_up_this_tick |= (1 << button);
    }
}

void rr_touch_event(struct rr_game *this, float x, float y, uint8_t state, uint8_t identifier)
{
    if (identifier >= 16)
        return;
    struct rr_input_touch *touch = &this->input_data->touches[identifier];
    touch->touch_x = x;
    touch->touch_y = y;
    touch->identifier = identifier;
    touch->active = state;
}

void rr_wheel_event(struct rr_game *this, float delta)
{
    this->input_data->scroll_delta = delta;
}
#else
#endif

void rr_main_loop(struct rr_game *this)
{
    printf("client on version %llu\n", RR_SECRET8 ^ 255);
#ifdef EMSCRIPTEN
    EM_ASM(
        {
            Module.canvas = document.createElement("canvas");
            Module.canvas.id = "canvas";
            Module.canvas.oncontextmenu = function() { return false; };
            document.body.appendChild(Module.canvas);
            Module.ctxs = [Module.canvas.getContext('2d')];
            Module.availableCtxs =
                new Array(256).fill(0).map(function(_, i) { return i; });
            window.onkeydown = function(e)
            {
                Module._rr_key_event(
                    $0, 1, e.which, (e.key && e.key.length == 1) * e.key.charCodeAt());
                if (e.metaKey)
                    e.preventDefault();
            };
            window.onkeyup = function(e)
            {
                Module._rr_key_event(
                    $0, 0, e.which, (e.key && e.key.length == 1) * e.key.charCodeAt());
                if (e.metaKey)
                    e.preventDefault();
            };
            window.onmousedown =
                function(e){
                    const clientX = e.clientX; const clientY = e.clientY; const button = e.button;
                    Module._rr_mouse_event(
                    $0, clientX * devicePixelRatio, clientY * devicePixelRatio,
                    1, +!!button)};
            window.onmousemove = function(e){
                    const clientX = e.clientX; const clientY = e.clientY; const button = e.button;
                    Module._rr_mouse_event(
                    $0, clientX * devicePixelRatio, clientY * devicePixelRatio,
                    2, +!!button)};
            window.onmouseup =
                function(e){
                    const clientX = e.clientX; const clientY = e.clientY; const button = e.button;
                    Module._rr_mouse_event(
                    $0, clientX * devicePixelRatio, clientY * devicePixelRatio,
                    0, +!!button)};
            window.addEventListener("touchstart", function(e){
                e.preventDefault();
                e.stopPropagation();
                if (!e.changedTouches.length)
                    return;
                const touch = e.changedTouches[0];
                Module._rr_mouse_event(
                    $0, touch.clientX * devicePixelRatio, touch.clientY * devicePixelRatio,
                    1, 0);
                for (const t of e.changedTouches)
                    Module._rr_touch_event($0, t.clientX * devicePixelRatio, t.clientY * devicePixelRatio, 1, t.identifier);
            }, {passive: false});
            window.addEventListener("touchmove", function(e){
                e.preventDefault();
                e.stopPropagation();
                if (!e.changedTouches.length)
                    return;
                const touch = e.changedTouches[0];
                Module._rr_mouse_event(
                    $0, touch.clientX * devicePixelRatio, touch.clientY * devicePixelRatio,
                    2, 0);
                for (const t of e.changedTouches)
                    Module._rr_touch_event($0, t.clientX * devicePixelRatio, t.clientY * devicePixelRatio, 1, t.identifier);
            }, {passive: false});
            window.addEventListener("touchend", function(e){
                e.preventDefault();
                e.stopPropagation();
                if (!e.changedTouches.length)
                    return;
                const touch = e.changedTouches[0];
                Module._rr_mouse_event(
                    $0, touch.clientX * devicePixelRatio, touch.clientY * devicePixelRatio,
                    0, 0);
                for (const t of e.changedTouches)
                    Module._rr_touch_event($0, t.clientX * devicePixelRatio, t.clientY * devicePixelRatio, 0, t.identifier);
            }, {passive: false});
            window.onwheel =
                function({deltaY}){Module._rr_wheel_event($0, deltaY)};
            Module.addCtx = function()
            {
                if (Module.availableCtxs.length)
                {
                    const index = Module.availableCtxs.shift();
                    if (index == 0)
                        return 0; // used for the main ctx, because that has
                                  // special behavior
                    const ocanvas = new OffscreenCanvas(1, 1);
                    Module.ctxs[index] = ocanvas.getContext('2d');
                    return index;
                }
                throw new Error(
                    'Out of Contexts: Can be fixed by allowing more contexts');
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
                while (Module.HEAPU8[ptr++])
                    ;
                return new TextDecoder().decode(
                    Module.HEAPU8.subarray(start, ptr - 1));
            };

            function loop(time)
            {
                if (window.start == null)
                    window.start = time + 1;
                const delta = Math.min(0.5, (time - start) / 1000);
                start = time;
                Module.canvas.width = innerWidth * devicePixelRatio;
                Module.canvas.height = innerHeight * devicePixelRatio;
                Module._rr_renderer_main_loop($0, delta, Module.canvas.width,
                                              Module.canvas.height,
                                              devicePixelRatio);
                requestAnimationFrame(loop);
            };
            requestAnimationFrame(loop);
        },
        this, &this->input_data->mouse_x, &this->input_data->mouse_state);
#endif
}

void rr_renderer_main_loop(struct rr_game *this, float delta, float width,
                           float height, float device_pixel_ratio)
{
    float a = height / 1080;
    float b = width / 1920;

    float scale = (this->renderer->scale = b < a ? a : b) * device_pixel_ratio;
    this->renderer->width = this->window->width = this->window->abs_width =
        width;
    this->renderer->height = this->window->height = this->window->abs_height =
        height;
    rr_game_tick(this, delta);
    this->input_data->scroll_delta = 0;
}

int main()
{
    static struct rr_game game;
    static struct rr_renderer renderer;
    static struct rr_input_data input_data;
    struct rr_simulation *simulation = malloc(sizeof *simulation);
    struct rr_simulation *deletion_simulation = malloc(sizeof *deletion_simulation);
    rr_main_loop(&game);

    rr_renderer_init(&renderer);
    rr_game_init(&game);
    rr_input_data_init(&input_data);
    rr_simulation_init(simulation);
    rr_simulation_init(deletion_simulation);

    game.renderer = &renderer;
    game.input_data = &input_data;
    game.simulation = simulation;
    game.deletion_simulation = deletion_simulation;
    rr_game_tick(&game, 1);

#ifndef EMSCRIPTEN
    // glfwSetErrorCallback([](int error, char const *description)
    //                      { std::cerr << "code " << error << ' ' <<
    //                      description << '\n'; });

    glfwInit();
    GLFWwindow *window =
        glfwCreateWindow(800, 800, "rrolf native client", NULL, NULL);

    // pthread_t socket_tid;

    // if (pthread_create(&socket_tid, NULL, rr_create_game_thread, &game) != 0)
    // {
    //     fputs("Failed to create game thread\n", stderr);
    //     return 1;
    // }

    // rr_game_connect_socket(&game);
    rr_create_game_thread(&game);
#endif

    return 0;
}
