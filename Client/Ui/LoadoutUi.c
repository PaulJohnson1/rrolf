#include <Client/Ui/Element.h>

#include <stdlib.h>

#include <Client/Game.h>
#include <Client/Socket.h>
#include <Client/InputData.h>
#include <Client/Simulation.h>
#include <Client/Ui/Engine.h>
#include <Client/Renderer/Renderer.h>
#include <Client/Renderer/RenderFunctions.h>

#include <Shared/StaticData.h>
#include <Shared/pb.h>

struct loadout_button_metadata
{
    uint8_t position;
    uint8_t main_loadout;
    void (*on_event)(struct rr_ui_element *, uint8_t, struct rr_game *, void *);
    float lerp_width;
};

static void petal_switch_button_event(struct rr_ui_element *this, uint8_t type, struct rr_game *game, void *_captures)
{
    if (type == 1) //mouse_down
    {
        struct proto_bug encoder;
        proto_bug_init(&encoder, output_packet);
        proto_bug_write_uint8(&encoder, 2, "header");
        proto_bug_write_uint8(&encoder, *(uint8_t *) _captures, "petal switch");
        rr_websocket_send(&game->socket, encoder.start, encoder.current);
    }
}

static void loadout_button_on_render(struct rr_ui_element *this, void *_game)
{
    if (this->hidden)
        return;
    struct rr_game *game = _game;
    struct rr_renderer *renderer = game->renderer;
    struct loadout_button_metadata *data = this->misc_data;
    struct rr_renderer_context_state state;
    if (game->simulation->player_info == RR_NULL_ENTITY)
        return;

    rr_renderer_init_context_state(renderer, &state);
    struct rr_component_player_info *player_info = rr_simulation_get_player_info(game->simulation, game->simulation->player_info);
    struct rr_component_player_info_petal_slot *slot = data->main_loadout ? &player_info->slots[data->position] : &player_info->secondary_slots[data->position];
    uint8_t id = slot->id;
    uint8_t rarity = slot->rarity;
    ui_translate(this, renderer);
    rr_renderer_scale(renderer, renderer->scale);
    if (rr_button_is_touching_mouse(this, game))
    {
        if (game->input_data->mouse_buttons_this_tick & 1)
            data->on_event(this, 1, game, &data->position);
    }    
    rr_renderer_scale(renderer, this->width / 60);
    rr_renderer_render_background(renderer, rarity);
    rr_renderer_draw_image(renderer, &game->static_petals[id][rarity]);
    
    rr_renderer_free_context_state(renderer, &state);
}

static struct rr_ui_element *rr_ui_loadout_button_init(uint8_t pos, uint8_t main)
{
    struct rr_ui_element *element = rr_ui_element_init();
    struct loadout_button_metadata *data = malloc(sizeof *data);
    data->position = pos;
    data->main_loadout = main;
    data->on_event = petal_switch_button_event;
    element->width = element->height = main ? 60 : 50;
    element->on_render = loadout_button_on_render;
    element->misc_data = data;
    return element;
}

struct rr_ui_element *rr_ui_loadout_container_init()
{
    return rr_ui_v_container_init(rr_ui_container_init(), 20, 20, 2,
        rr_ui_h_container_init(rr_ui_container_init(), 0, 20, 10,
            rr_ui_loadout_button_init(0, 1),
            rr_ui_loadout_button_init(1, 1),
            rr_ui_loadout_button_init(2, 1),
            rr_ui_loadout_button_init(3, 1),
            rr_ui_loadout_button_init(4, 1),
            rr_ui_loadout_button_init(5, 1),
            rr_ui_loadout_button_init(6, 1),
            rr_ui_loadout_button_init(7, 1),
            rr_ui_loadout_button_init(8, 1),
            rr_ui_loadout_button_init(9, 1)
        ),
        rr_ui_h_container_init(rr_ui_container_init(), 0, 20, 10,
            rr_ui_loadout_button_init(0, 0),
            rr_ui_loadout_button_init(1, 0),
            rr_ui_loadout_button_init(2, 0),
            rr_ui_loadout_button_init(3, 0),
            rr_ui_loadout_button_init(4, 0),
            rr_ui_loadout_button_init(5, 0),
            rr_ui_loadout_button_init(6, 0),
            rr_ui_loadout_button_init(7, 0),
            rr_ui_loadout_button_init(8, 0),
            rr_ui_loadout_button_init(9, 0)
        )
    );
}
