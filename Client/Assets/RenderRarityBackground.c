#include <Client/Assets/RenderFunctions.h>

#include <math.h>

#include <Client/Renderer/Renderer.h>
#include <Shared/StaticData.h>

struct rr_renderer background_cache;

void rr_renderer_draw_background(struct rr_renderer *renderer, uint8_t rarity, uint8_t flags)
{
    if (flags & 1)
    {
        rr_renderer_draw_clipped_image(renderer, &background_cache, 34 + 68 * rarity, 34, 68, 68, 0, 0);
        if (rarity >= rr_rarity_id_max)
            return;
        rr_renderer_begin_path(renderer);
        rr_renderer_round_rect(renderer, -27.0f, -27.0f, 54.0f, 54.0f, 3.0f);
        rr_renderer_clip(renderer);
    }
    else
    {
        if (rarity == rr_rarity_id_max + 2)
        {
            rr_renderer_set_fill(renderer, 0xff777777);
            renderer->state.filter.amount = 0.2f;
            rr_renderer_set_stroke(renderer, 0xff777777);
            rr_renderer_set_line_width(renderer, 6.0f);
            rr_renderer_begin_path(renderer);
            rr_renderer_round_rect(renderer, -30.0f, -30.0f, 60.0f, 60.0f, 6.0f);
            rr_renderer_fill(renderer);
            rr_renderer_stroke(renderer);
            renderer->state.filter.amount = 0.0f;
            return;
        }
        else if (rarity == rr_rarity_id_max + 1)
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
        else if (rarity == rr_rarity_id_max)
        {
            rr_renderer_set_fill(renderer, 0x40ffffff);
            rr_renderer_begin_path(renderer);
            rr_renderer_round_rect(renderer, -32.0f, -32.0f, 64.0f, 64.0f, 6.0f);
            rr_renderer_fill(renderer);
            return;
        }
        renderer->state.filter.amount = 0.2f;
        rr_renderer_set_fill(renderer, RR_RARITY_COLORS[rarity]);
        rr_renderer_set_line_width(renderer, 6.0f);
        rr_renderer_begin_path(renderer);
        rr_renderer_round_rect(renderer, -33.0f, -33.0f, 66.0f, 66.0f, 6.0f);
        rr_renderer_fill(renderer);
        renderer->state.filter.amount = 0.0f;
        rr_renderer_set_fill(renderer, RR_RARITY_COLORS[rarity]);
        rr_renderer_begin_path(renderer);
        rr_renderer_round_rect(renderer, -27.0f, -27.0f, 54.0f, 54.0f, 3.0f);
        rr_renderer_fill(renderer);
        rr_renderer_clip(renderer);
    }
}

void rr_renderer_background_cache_init()
{
    rr_renderer_init(&background_cache);
    rr_renderer_set_dimensions(&background_cache, 68 * (rr_rarity_id_max + 3), 68);
    rr_renderer_translate(&background_cache, 34, 34);
    struct rr_renderer_context_state state;
    for (uint32_t i = 0; i <= rr_rarity_id_max + 2; ++i)
    {
        rr_renderer_context_state_init(&background_cache, &state);
        rr_renderer_draw_background(&background_cache, i, 0);
        rr_renderer_context_state_free(&background_cache, &state);
        rr_renderer_translate(&background_cache, 68, 0);
    }
}