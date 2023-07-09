#include <Client/Ui/Ui.h>

#include <stdlib.h>
#include <stdio.h>

#include <Client/Game.h>
#include <Client/Renderer/Renderer.h>
#include <Client/Renderer/RenderFunctions.h>
#include <Client/Ui/Engine.h>

#include <Shared/StaticData.h>

struct tooltip_petal_icon_metadata
{
    uint8_t id;
    uint8_t rarity;
};

static void inventory_button_on_render(struct rr_ui_element *this,
                                       struct rr_game *game)
{
    struct tooltip_petal_icon_metadata *data = this->data;
    struct rr_renderer *renderer = game->renderer;
    rr_renderer_scale(renderer, renderer->scale * this->width / 60);
    rr_renderer_render_background(renderer, data->rarity);
    rr_renderer_draw_image(renderer, &game->static_petals[data->id][data->rarity]);
}

static struct rr_ui_element *tooltip_petal_icon_init(uint8_t id, uint8_t rarity)
{
    struct rr_ui_element *this = rr_ui_element_init();
    struct tooltip_petal_icon_metadata *data = malloc(sizeof *data);
    data->id = id;
    data->rarity = rarity;
    this->data = data;
    this->abs_width = this->abs_height = this->width = this->height = 40;
    this->on_render = inventory_button_on_render;
    return this;
}

struct rr_ui_element *rr_ui_mob_tooltip_init(uint8_t id, uint8_t rarity)
{
    char *hp = malloc((sizeof *hp) * 16);
    hp[sprintf(hp, "%.1f",
                RR_MOB_DATA[id].health *
                    RR_MOB_RARITY_SCALING[rarity].health)] = 0;
    char *dmg = malloc((sizeof *dmg) * 16);
    dmg[sprintf(dmg, "%.1f",
                RR_MOB_DATA[id].damage *
                    RR_MOB_RARITY_SCALING[rarity].damage)] = 0;
    struct rr_ui_element *this = rr_ui_set_background(
        rr_ui_v_container_init(
            rr_ui_container_init(), 10, 5, 6,
                rr_ui_set_justify(rr_ui_text_init(RR_MOB_NAMES[id], 24, 0xffffffff), -1, -1),
                rr_ui_set_justify(rr_ui_text_init(RR_RARITY_NAMES[rarity], 16, RR_RARITY_COLORS[rarity]), -1, -1),
                rr_ui_static_space_init(10),
                rr_ui_set_justify(
                    rr_ui_h_container_init(
                        rr_ui_container_init(), 0, 0, 2,
                        rr_ui_text_init("Health: ", 12, 0xff44ff44),
                        rr_ui_text_init(hp, 12, 0xff44ff44)),
                    -1, 0),
                rr_ui_set_justify(
                    rr_ui_h_container_init(
                        rr_ui_container_init(), 0, 0, 2,
                        rr_ui_text_init("Damage: ", 12, 0xffff4444),
                        rr_ui_text_init(dmg, 12, 0xffff4444)
                    ),
                -1, 0),
                rr_ui_static_space_init(10)
            ),
        0x80000000);
    for (uint8_t i = 0; i < 4; ++i)
    {
        if (RR_MOB_DATA[id].loot[i].id == 0)
            break;
        struct rr_loot_data *data = &RR_MOB_DATA[id].loot[i];
        struct rr_ui_element *temp = rr_ui_h_container_init(rr_ui_container_init(), 0, 10, 0);
        for (uint8_t r = 1; r < rr_rarity_id_mythic + 2; ++r)
        {
            if (data->loot_table[rarity][r] - data->loot_table[rarity][r - 1] < 0.0001)
                continue;
            char *d = malloc((sizeof *d) * 8);
            d[sprintf(d, "%.2f%%", 100 * (data->loot_table[rarity][r] - data->loot_table[rarity][r - 1]))] = 0;
            rr_ui_container_add_element(temp, rr_ui_v_container_init(rr_ui_container_init(), 0, 5, 2,
                    tooltip_petal_icon_init(data->id, r - 1),
                    rr_ui_text_init(d, 11, 0xffffffff)
                )
            );
        }
        rr_ui_container_add_element(this, temp);
    }
    rr_ui_link_toggle(
        rr_ui_set_justify(this, -1, -1),
    rr_ui_never_show);
    this->poll_events = rr_ui_no_focus;
    return this;
}