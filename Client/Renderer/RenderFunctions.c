#include <Client/Renderer/RenderFunctions.h>

#include <math.h>
#include <stdio.h>

#include <Client/Game.h>
#include <Client/Renderer/Renderer.h>
#include <Shared/StaticData.h>

void rr_renderer_render_petal(struct rr_renderer *renderer, uint8_t id)
{
    switch (id)
    {
    case rr_petal_id_no_petal:
        break;
    case rr_petal_id_basic:
        rr_renderer_set_stroke(renderer, 0xffcfcfcf);
        rr_renderer_set_fill(renderer, 0xffffffff);
        rr_renderer_set_line_width(renderer, 3.0f);
        rr_renderer_begin_path(renderer);
        rr_renderer_arc(renderer, 0.0f, 0.0f, 10.0f);
        rr_renderer_fill(renderer);
        rr_renderer_stroke(renderer);
        break;
    case rr_petal_id_light:
        rr_renderer_set_stroke(renderer, 0xffcfcfcf);
        rr_renderer_set_fill(renderer, 0xffffffff);
        rr_renderer_set_line_width(renderer, 3.0f);
        rr_renderer_begin_path(renderer);
        rr_renderer_arc(renderer, 0.0f, 0.0f, 7.0f);
        rr_renderer_fill(renderer);
        rr_renderer_stroke(renderer);
        break;
    case rr_petal_id_rock:
        rr_renderer_set_stroke(renderer, 0xff606060);
        rr_renderer_set_fill(renderer, 0xff777777);
        rr_renderer_set_line_width(renderer, 3.0f);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, 12.138091087341309f, 0.0f);
        rr_renderer_line_to(renderer, 3.8414306640625f, 12.377452850341797f);
        rr_renderer_line_to(renderer, -11.311542510986328f, 7.916932582855225f);
        rr_renderer_line_to(renderer, -11.461170196533203f,
                            -7.836822032928467f);
        rr_renderer_line_to(renderer, 4.538298606872559f, -13.891617774963379f);
        rr_renderer_line_to(renderer, 12.138091087341309f, 0.0f);
        rr_renderer_fill(renderer);
        rr_renderer_stroke(renderer);
        break;
    case rr_petal_id_stinger:
        rr_renderer_set_fill(renderer, 0xff333333);
        rr_renderer_set_stroke(renderer, 0xff292929);
        rr_renderer_set_line_width(renderer, 3.0f);
        rr_renderer_set_line_join(renderer, 1.0f);
        rr_renderer_set_line_cap(renderer, 1.0f);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, 7.0f, 0.0f);
        rr_renderer_line_to(renderer, -3.5f, 6.062177658081055f);
        rr_renderer_line_to(renderer, -3.5f, -6.062178134918213f);
        rr_renderer_line_to(renderer, 7.0f, 0.0f);
        rr_renderer_fill(renderer);
        rr_renderer_stroke(renderer);
        break;
    case rr_petal_id_faster:
        rr_renderer_set_stroke(renderer, 0xffcecfa3);
        rr_renderer_set_fill(renderer, 0xfffeffc9);
        rr_renderer_set_line_width(renderer, 3.0f);
        rr_renderer_begin_path(renderer);
        rr_renderer_arc(renderer, 0.0f, 0.0f, 7.0f);
        rr_renderer_fill(renderer);
        rr_renderer_stroke(renderer);
        break;
    case rr_petal_id_missile:
        rr_renderer_set_fill(renderer, 0xff333333);
        rr_renderer_set_stroke(renderer, 0xff333333);
        rr_renderer_set_line_width(renderer, 5.0f);
        rr_renderer_set_line_join(renderer, 1.0f);
        rr_renderer_set_line_cap(renderer, 1.0f);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, 11.0f, 0.0f);
        rr_renderer_line_to(renderer, -11.0f, -6.0f);
        rr_renderer_line_to(renderer, -11.0f, 6.0f);
        rr_renderer_line_to(renderer, 11.0f, 0.0f);
        rr_renderer_fill(renderer);
        rr_renderer_stroke(renderer);
        break;
    case rr_petal_id_peas:
        rr_renderer_set_stroke(renderer, 0xff709d45);
        rr_renderer_set_fill(renderer, 0xff8ac255);
        rr_renderer_set_line_width(renderer, 3.0f);
        rr_renderer_begin_path(renderer);
        rr_renderer_arc(renderer, 0.0f, 0.0f, 7.0f);
        rr_renderer_fill(renderer);
        rr_renderer_stroke(renderer);
        break;
    case rr_petal_id_leaf:
        rr_renderer_set_stroke(renderer, 0xff2e933c);
        rr_renderer_set_fill(renderer, 0xff39b54a);
        rr_renderer_set_line_width(renderer, 3.0f);
        rr_renderer_set_line_join(renderer, 1.0f);
        rr_renderer_set_line_cap(renderer, 1.0f);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, -20.0f, 0.0f);
        rr_renderer_line_to(renderer, -15.0f, 0.0f);
        rr_renderer_bezier_curve_to(renderer, -10.0f, -12.0f, 5.0f, -12.0f,
                                    15.0f, 0.0f);
        rr_renderer_bezier_curve_to(renderer, 5.0f, 12.0f, -10.0f, 12.0f,
                                    -15.0f, 0.0f);
        rr_renderer_fill(renderer);
        rr_renderer_stroke(renderer);
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, -9.0f, 0.0f);
        rr_renderer_quadratic_curve_to(renderer, 0.0f, -1.5f, 7.5f, 0.0f);
        rr_renderer_stroke(renderer);
        break;
    case rr_petal_id_egg:
        rr_renderer_set_stroke(renderer, 0xffcfcfcf);
        rr_renderer_set_fill(renderer, 0xffffffff);
        rr_renderer_set_line_width(renderer, 3);
        rr_renderer_begin_path(renderer);
        rr_renderer_arc(renderer, 0, 0, 12);
        rr_renderer_fill(renderer);
        rr_renderer_stroke(renderer);
        break;
    default:
        break;
    }
}

void rr_renderer_render_static_petal(struct rr_renderer *renderer, uint8_t id,
                                     uint8_t rarity)
{
    uint32_t count = RR_PETAL_DATA[id].count[rarity];
    if (id == rr_petal_id_peas)
        rr_renderer_rotate(renderer, 1.0f - M_PI / 4.0f);
    if (count == 1)
    {
        if (id == rr_petal_id_missile)
            rr_renderer_rotate(renderer, 1.0f);
        else if (id == rr_petal_id_leaf)
            rr_renderer_rotate(renderer, -1.0f);
        rr_renderer_render_petal(renderer, id);
    }
    else
    {
        struct rr_renderer_context_state state;
        float r = RR_PETAL_DATA[id].clump_radius == 0.0f
                      ? 10.0f
                      : RR_PETAL_DATA[id].clump_radius;
        for (uint32_t i = 0; i < count; ++i)
        {
            rr_renderer_init_context_state(renderer, &state);
            rr_renderer_translate(renderer, r, 0.0f);
            if (id == rr_petal_id_missile)
                rr_renderer_rotate(renderer, 1.0f);
            else if (id == rr_petal_id_leaf)
                rr_renderer_rotate(renderer, -1.0f);
            else if (id == rr_petal_id_stinger && rarity == rr_rarity_id_ultra)
                rr_renderer_rotate(renderer, M_PI);
            rr_renderer_render_petal(renderer, id);
            rr_renderer_free_context_state(renderer, &state);
            rr_renderer_rotate(renderer, M_PI * 2.0f / count);
        }
    }
}

void rr_renderer_render_mob(struct rr_renderer *renderer, struct rr_game *game,
                            uint8_t id, float animation_tick)
{
    struct rr_renderer_context_state original_state;
    struct rr_renderer_context_state state;

    rr_renderer_init_context_state(renderer, &original_state);
    switch (id)
    {
    case rr_mob_id_triceratops:
        rr_renderer_rotate(renderer, M_PI / 2);
        rr_renderer_scale(renderer, 0.2f);
        rr_renderer_draw_image(renderer, &game->mob_triceratops[0]);
        rr_renderer_draw_image(renderer, &game->mob_triceratops[1]);
        rr_renderer_draw_image(renderer, &game->mob_triceratops[2]);
        rr_renderer_draw_image(renderer, &game->mob_triceratops[3]);
        rr_renderer_draw_image(renderer, &game->mob_triceratops[4]);
        rr_renderer_draw_image(renderer, &game->mob_triceratops[5]);
        rr_renderer_draw_image(renderer, &game->mob_triceratops[6]);

        break;
    case rr_mob_id_trex:
        rr_renderer_rotate(renderer, M_PI / 2);
        rr_renderer_scale(renderer, 0.2f);

        rr_renderer_init_context_state(renderer, &state);
        rr_renderer_translate(renderer, 0.0f, animation_tick * 10.0f);
        rr_renderer_draw_image(renderer, &game->mob_trex_legs[0]);
        rr_renderer_free_context_state(renderer, &state);

        rr_renderer_init_context_state(renderer, &state);
        rr_renderer_translate(renderer, 0.0f, animation_tick * -10.0f);
        rr_renderer_draw_image(renderer, &game->mob_trex_legs[1]);
        rr_renderer_free_context_state(renderer, &state);

        rr_renderer_draw_image(renderer, &game->mob_trex_tail_bottom);
        rr_renderer_draw_image(renderer, &game->mob_trex_body);
        rr_renderer_draw_image(renderer, &game->mob_trex_tail_top);
        rr_renderer_draw_image(renderer, &game->mob_trex_body_line);
        rr_renderer_draw_image(renderer, &game->mob_trex_head);
        break;
    case rr_mob_id_stump:
        rr_renderer_rotate(renderer, M_PI / 2);
        rr_renderer_scale(renderer, 0.2f);
        rr_renderer_draw_image(renderer, &game->mob_stump);
        break;
    case rr_mob_id_spinosaurus_head:
        rr_renderer_scale(renderer, 10.0f / 36.0f);
        rr_renderer_set_fill(renderer, 0xff333333);
        // side circle a
        rr_renderer_begin_path(renderer);
        rr_renderer_arc(renderer, animation_tick * 3.0f, -30.0f, 15.0f);
        rr_renderer_fill(renderer);
        // side circle b
        rr_renderer_begin_path(renderer);
        rr_renderer_arc(renderer, -animation_tick * 3.0f, 30.0f, 15.0f);
        rr_renderer_fill(renderer);
        rr_renderer_set_fill(renderer, 0xff8ac255);
        rr_renderer_set_stroke(renderer, 0xff709d45);
        rr_renderer_set_line_width(renderer, 7.0f);
        rr_renderer_begin_path(renderer);
        rr_renderer_arc(renderer, 0.0f, 0.0f, 35.0f);
        rr_renderer_fill(renderer);
        rr_renderer_stroke(renderer);
        rr_renderer_set_stroke(renderer, 0xff333333);
        rr_renderer_set_line_cap(renderer, 1.0f);
        rr_renderer_set_line_width(renderer, 3.0f);
        rr_renderer_init_context_state(renderer, &state);
        rr_renderer_rotate(renderer, animation_tick * 0.1f);
        rr_renderer_set_fill(renderer, 0xff333333);
        // antennae circle a
        rr_renderer_begin_path(renderer);
        rr_renderer_arc(renderer, 55.0f + animation_tick * 2.0f, -30.0f, 5.0f);
        rr_renderer_fill(renderer);
        // antennae circle b
        rr_renderer_begin_path(renderer);
        rr_renderer_arc(renderer, 55.0f - animation_tick * 2.0f, 30.0f, 5.0f);
        rr_renderer_fill(renderer);
        // antennae line a
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, 25.0f, -10.0f);
        rr_renderer_quadratic_curve_to(renderer, 45.0f, -10.0f,
                                       55.0f + animation_tick * 2.0f, -30.0f);
        rr_renderer_stroke(renderer);
        // antennae line b
        rr_renderer_begin_path(renderer);
        rr_renderer_move_to(renderer, 25.0f, 10.0f);
        rr_renderer_quadratic_curve_to(renderer, 45.0f, 10.0f,
                                       55.0f - animation_tick * 2.0f, 30.0f);
        rr_renderer_stroke(renderer);
        rr_renderer_free_context_state(renderer, &state);
        break;
    case rr_mob_id_spinosaurus_body:
        rr_renderer_scale(renderer, 10.0f / 36.0f);
        rr_renderer_set_fill(renderer, 0xff333333);
        // side circle a
        rr_renderer_begin_path(renderer);
        rr_renderer_arc(renderer, animation_tick * 2.0f, -30.0f, 15.0f);
        rr_renderer_fill(renderer);
        // antennae circle b
        rr_renderer_begin_path(renderer);
        rr_renderer_arc(renderer, -animation_tick * 2.0f, 30.0f, 15.0f);
        rr_renderer_fill(renderer);
        rr_renderer_set_fill(renderer, 0xff8ac255);
        rr_renderer_set_stroke(renderer, 0xff709d45);
        rr_renderer_set_line_width(renderer, 7.0f);
        rr_renderer_begin_path(renderer);
        rr_renderer_arc(renderer, 0.0f, 0.0f, 35.0f);
        rr_renderer_fill(renderer);
        rr_renderer_stroke(renderer);
        break;
    case rr_mob_id_pteranodon:
        rr_renderer_rotate(renderer, M_PI / 2);
        rr_renderer_scale(renderer, 0.2f);

        rr_renderer_init_context_state(renderer, &state);
        rr_renderer_rotate(renderer, animation_tick * 0.1f);
        rr_renderer_translate(renderer, 40.0f, 30.0f);
        rr_renderer_draw_image(renderer, &game->mob_pteranodon_wings[0]);
        rr_renderer_free_context_state(renderer, &state);

        rr_renderer_init_context_state(renderer, &state);
        rr_renderer_rotate(renderer, animation_tick * -0.1f);
        rr_renderer_translate(renderer, -40.0f, 30.0f);
        rr_renderer_draw_image(renderer, &game->mob_pteranodon_wings[1]);
        rr_renderer_free_context_state(renderer, &state);

        rr_renderer_draw_image(renderer, &game->mob_pteranodon_body);
        break;
    case rr_mob_id_dakotaraptor:
        rr_renderer_rotate(renderer, M_PI / 2);
        rr_renderer_scale(renderer, 0.2f);

        rr_renderer_draw_image(renderer, &game->mob_dakotaraptor[0]);
        rr_renderer_draw_image(renderer, &game->mob_dakotaraptor[1]);
        rr_renderer_draw_image(renderer, &game->mob_dakotaraptor[2]);
        rr_renderer_draw_image(renderer, &game->mob_dakotaraptor[3]);
        rr_renderer_draw_image(renderer, &game->mob_dakotaraptor[4]);
        rr_renderer_draw_image(renderer, &game->mob_dakotaraptor[5]);
        break;
    case 255:
        rr_renderer_set_stroke(renderer, 0xffcfcfcf);
        rr_renderer_set_fill(renderer, 0xffffffff);
        rr_renderer_set_line_width(renderer, 7.0f);
        rr_renderer_begin_path(renderer);
        rr_renderer_arc(renderer, 0.0f, 0.0f, 7.0f);
        rr_renderer_fill(renderer);
        rr_renderer_stroke(renderer);
        break;
    default:
        break;
    }

    rr_renderer_free_context_state(renderer, &original_state);
}

void rr_renderer_render_background(struct rr_renderer *renderer, uint8_t rarity)
{
    if (rarity == 255)
    {
        rr_renderer_set_fill(renderer, 0xffcccccc);
        renderer->state.filter.amount = 0.2f;
        rr_renderer_set_stroke(renderer, 0xffcccccc);
        rr_renderer_set_line_width(renderer, 6.0f);
        rr_renderer_begin_path(renderer);
        rr_renderer_round_rect(renderer, -30.0f, -30.0f, 60.0f, 60.0f, 6.0f);
        rr_renderer_fill(renderer);
        rr_renderer_stroke(renderer);
        renderer->state.filter.amount = 0.0f;
        return;
    }
    rr_renderer_set_fill(renderer, RR_RARITY_COLORS[rarity]);
    renderer->state.filter.amount = 0.2f;
    rr_renderer_set_stroke(renderer, RR_RARITY_COLORS[rarity]);
    rr_renderer_set_line_width(renderer, 6.0f);
    rr_renderer_begin_path(renderer);
    rr_renderer_round_rect(renderer, -30.0f, -30.0f, 60.0f, 60.0f, 6.0f);
    rr_renderer_fill(renderer);
    rr_renderer_stroke(renderer);
    rr_renderer_clip(renderer);
    renderer->state.filter.amount = 0.0f;
}
