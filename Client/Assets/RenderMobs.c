#include <Client/Assets/RenderFunctions.h>

#include <math.h>
#include <stdlib.h>

#include <Client/Assets/Render.h>
#include <Client/Renderer/Renderer.h>
#include <Shared/StaticData.h>

//head, body, legs, tail, IN THAT ORDER

struct rr_renderer_spritesheet mob_sprites[rr_mob_id_max];
struct rr_renderer_spritesheet friendly_trex_spritesheet;
void render_sprite(struct rr_renderer *renderer, uint8_t id, uint32_t pos, uint8_t flags)
{
    if (flags & 1)
        render_sprite_from_cache(renderer, (flags & 2) && id == rr_mob_id_trex ? &friendly_trex_spritesheet : &mob_sprites[id], pos);
    else
        mob_sprites[id].sprites[pos].render(renderer);
}

void rr_renderer_draw_mob(struct rr_renderer *renderer, uint8_t id, float animation_tick, float turning_value, uint8_t flags)
{
     struct rr_renderer_context_state original_state;
    struct rr_renderer_context_state state;

    rr_renderer_context_state_init(renderer, &original_state);
    rr_renderer_rotate(renderer, M_PI / 2);
    switch (id)
    {
    case rr_mob_id_pachycephalosaurus:
        rr_renderer_scale(renderer, 0.75);
    case rr_mob_id_triceratops:
    case rr_mob_id_trex:
    case rr_mob_id_edmontosaurus:
        rr_renderer_scale(renderer, 0.2f);

        rr_renderer_context_state_init(renderer, &state);
        rr_renderer_translate(renderer, 0.0f, animation_tick * 10.0f);
        render_sprite(renderer, id, 2, flags);
        rr_renderer_context_state_free(renderer, &state);

        rr_renderer_context_state_init(renderer, &state);
        rr_renderer_translate(renderer, 0.0f, animation_tick * -10.0f);
        render_sprite(renderer, id, 3, flags);
        rr_renderer_context_state_free(renderer, &state);

        rr_renderer_context_state_init(renderer, &state);
        rr_renderer_translate(renderer,  0, 75);
        rr_renderer_rotate(renderer, turning_value);
        rr_renderer_translate(renderer,  0, -75 + 155);
        render_sprite(renderer, id, 4, flags);
        rr_renderer_context_state_free(renderer, &state);

        render_sprite(renderer, id, 1, flags);

        rr_renderer_context_state_init(renderer, &state);
        rr_renderer_translate(renderer,  0, -75);
        rr_renderer_translate(renderer,  0, 75 - 145);
        render_sprite(renderer, id, 0, flags);
        rr_renderer_context_state_free(renderer, &state);
        break;
    case rr_mob_id_fern:
        rr_renderer_scale(renderer, 0.6f);
    case rr_mob_id_kelp:
        rr_renderer_scale(renderer, 0.5f);
    case rr_mob_id_tree:
    case rr_mob_id_meteor:
        rr_renderer_scale(renderer, 0.4f);
        render_sprite(renderer, id, 0, flags);
        break;
    case rr_mob_id_pteranodon:
        rr_renderer_scale(renderer, 0.15f);

        rr_renderer_context_state_init(renderer, &state);
        rr_renderer_rotate(renderer, animation_tick * 0.1f);
        rr_renderer_translate(renderer, 160, 0);
        render_sprite(renderer, id, 1, flags);
        rr_renderer_context_state_free(renderer, &state);

        rr_renderer_context_state_init(renderer, &state);
        rr_renderer_rotate(renderer, animation_tick * -0.1f);
        rr_renderer_translate(renderer, -160, 0);
        render_sprite(renderer, id, 2, flags);
        rr_renderer_context_state_free(renderer, &state);
        render_sprite(renderer, id, 0, flags);
        break;
    case rr_mob_id_dakotaraptor:
    case rr_mob_id_ornithomimus:
        rr_renderer_scale(renderer, 0.16f);

        rr_renderer_context_state_init(renderer, &state);
        rr_renderer_translate(renderer, -65, 0);
        rr_renderer_rotate(renderer, animation_tick * 0.1f);
        render_sprite(renderer, id, 2, flags);
        rr_renderer_context_state_free(renderer, &state);
        
        rr_renderer_context_state_init(renderer, &state);
        rr_renderer_translate(renderer, 65, 0);
        rr_renderer_rotate(renderer, animation_tick * -0.1f);
        render_sprite(renderer, id, 3, flags);
        rr_renderer_context_state_free(renderer, &state);

        rr_renderer_context_state_init(renderer, &state);
        rr_renderer_translate(renderer, 0, 180);
        rr_renderer_rotate(renderer, turning_value);
        rr_renderer_translate(renderer, 0, 15);
        render_sprite(renderer, id, 4, flags);
        rr_renderer_context_state_free(renderer, &state);

        render_sprite(renderer, id, 1, flags);


        rr_renderer_context_state_init(renderer, &state);
        rr_renderer_translate(renderer, 0, id == rr_mob_id_ornithomimus ? -175 : -125);
        
        render_sprite(renderer, id, 0, flags);
        rr_renderer_context_state_free(renderer, &state);
        break;
    case rr_mob_id_ankylosaurus:
        rr_renderer_scale(renderer, 0.2f);

        rr_renderer_context_state_init(renderer, &state);
        rr_renderer_translate(renderer, 0, 155);
        rr_renderer_rotate(renderer, turning_value);
        render_sprite(renderer, id, 2, flags);
        rr_renderer_context_state_free(renderer, &state);

        render_sprite(renderer, id, 1, flags);
        
        rr_renderer_context_state_init(renderer, &state);
        rr_renderer_translate(renderer, 0, -145);
        render_sprite(renderer, id, 0, flags);
        rr_renderer_context_state_free(renderer, &state);
        break;
    case rr_mob_id_quetzalcoatlus:
        rr_renderer_scale(renderer, 0.2f);

        rr_renderer_context_state_init(renderer, &state);
        rr_renderer_rotate(renderer, animation_tick * 0.1f);
        rr_renderer_translate(renderer, 125, 75);
        render_sprite(renderer, id, 2, flags);
        rr_renderer_context_state_free(renderer, &state);

        rr_renderer_context_state_init(renderer, &state);
        rr_renderer_rotate(renderer, animation_tick * -0.1f);
        rr_renderer_translate(renderer, -125, 75);
        render_sprite(renderer, id, 3, flags);
        rr_renderer_context_state_free(renderer, &state);
        render_sprite(renderer, id, 1, flags);

        rr_renderer_translate(renderer, 0, -165);
        render_sprite(renderer, id, 0, flags);
        break;
    case rr_mob_id_pectinodon:
        rr_renderer_scale(renderer, 0.12f);

        rr_renderer_context_state_init(renderer, &state);
        rr_renderer_translate(renderer, -90, 50);
        rr_renderer_rotate(renderer, animation_tick * 0.1f);
        render_sprite(renderer, id, 2, flags);
        rr_renderer_context_state_free(renderer, &state);
        
        rr_renderer_context_state_init(renderer, &state);
        rr_renderer_translate(renderer, 90, 50);
        rr_renderer_rotate(renderer, animation_tick * -0.1f);
        render_sprite(renderer, id, 3, flags);
        rr_renderer_context_state_free(renderer, &state);

        rr_renderer_context_state_init(renderer, &state);
        rr_renderer_translate(renderer, 0, 290);
        rr_renderer_rotate(renderer, turning_value);
        rr_renderer_translate(renderer, 0, -50);
        render_sprite(renderer, id, 4, flags);

        rr_renderer_context_state_free(renderer, &state);
        render_sprite(renderer, id, 1, flags);

        rr_renderer_translate(renderer, 0, -185);
        render_sprite(renderer, id, 0, flags);
        break;
    case rr_mob_id_king_mackarel:
        rr_renderer_scale(renderer, 0.2f);

        rr_renderer_context_state_init(renderer, &state);
        rr_renderer_translate(renderer,  0, 100);
        rr_renderer_rotate(renderer, animation_tick * 0.1f);
        rr_renderer_translate(renderer,  0, -100 + 180);
        render_sprite(renderer, id, 4, flags);
        rr_renderer_context_state_free(renderer, &state);

        render_sprite(renderer, id, 1, flags);

        rr_renderer_context_state_init(renderer, &state);
        rr_renderer_translate(renderer, -30, -100);
        rr_renderer_rotate(renderer, animation_tick * 0.1f);
        rr_renderer_translate(renderer, -30, 30);
        render_sprite(renderer, id, 2, flags);
        rr_renderer_context_state_free(renderer, &state);

        rr_renderer_context_state_init(renderer, &state);
        rr_renderer_translate(renderer, 30, -100);
        rr_renderer_rotate(renderer, animation_tick * -0.1f);
        rr_renderer_translate(renderer, 30, 30);
        render_sprite(renderer, id, 3, flags);
        rr_renderer_context_state_free(renderer, &state);

        rr_renderer_context_state_init(renderer, &state);
        rr_renderer_translate(renderer,  0, -75);
        rr_renderer_translate(renderer,  0, 75 - 145);
        render_sprite(renderer, id, 0, flags);
        rr_renderer_context_state_free(renderer, &state);
        break;
    case rr_mob_id_sea_snail:
        rr_renderer_scale(renderer, 0.2f);
        rr_renderer_context_state_init(renderer, &state);
        rr_renderer_translate(renderer,  0, -125 + animation_tick * 30);
        render_sprite(renderer, id, 0, flags);
        rr_renderer_context_state_free(renderer, &state);
        render_sprite(renderer, id, 1, flags);
        break;
    case rr_mob_id_seagull:
        rr_renderer_scale(renderer, 0.15f);

        rr_renderer_context_state_init(renderer, &state);
        rr_renderer_rotate(renderer, animation_tick * 0.1f);
        rr_renderer_translate(renderer, 125, 15);
        render_sprite(renderer, id, 1, flags);
        rr_renderer_context_state_free(renderer, &state);

        rr_renderer_context_state_init(renderer, &state);
        rr_renderer_rotate(renderer, animation_tick * -0.1f);
        rr_renderer_translate(renderer, -125, 15);
        render_sprite(renderer, id, 2, flags);
        rr_renderer_context_state_free(renderer, &state);
        render_sprite(renderer, id, 0, flags);
        break;
    }
    rr_renderer_context_state_free(renderer, &original_state);
}

static void friendly_mask(struct rr_renderer *renderer)
{
    rr_renderer_add_color_filter(renderer, 0xffffff45, 0.3);
}

void rr_renderer_mob_cache_init()
{
    rr_renderer_spritesheet_init(&mob_sprites[0], NULL, 192, 336, rr_triceratops_head_draw,
    192, 336, rr_triceratops_body_draw, 240, 240, rr_triceratops_leg1_draw, 
    240, 240, rr_triceratops_leg2_draw, 192, 336, rr_triceratops_tail_draw, 0);

    rr_renderer_spritesheet_init(&mob_sprites[1], NULL, 144, 240, rr_t_rex_head_draw,
    192, 336, rr_t_rex_body_draw, 240, 240, rr_t_rex_leg1_draw, 
    240, 240, rr_t_rex_leg2_draw, 192, 336, rr_t_rex_tail_draw, 0);

    rr_renderer_spritesheet_init(&friendly_trex_spritesheet, friendly_mask, 144, 240, rr_t_rex_head_draw,
    192, 336, rr_t_rex_body_draw, 240, 240, rr_t_rex_leg1_draw, 
    240, 240, rr_t_rex_leg2_draw, 192, 336, rr_t_rex_tail_draw, 0);

    rr_renderer_spritesheet_init(&mob_sprites[2], NULL, 672, 672, rr_fern_draw, 0);

    rr_renderer_spritesheet_init(&mob_sprites[3], NULL, 384, 384, rr_tree_draw, 0);

    rr_renderer_spritesheet_init(&mob_sprites[4], NULL, 192, 336, rr_pteranodon_body_draw, 
    432, 288, rr_pteranodon_wing1_draw, 432, 288, rr_pteranodon_wing2_draw, 0);

    rr_renderer_spritesheet_init(&mob_sprites[5], NULL, 144, 240, rr_dakotaraptor_head_draw, 
    192, 336, rr_dakotaraptor_body_draw, 144, 240, rr_dakotaraptor_wing1_draw, 144, 240, 
    rr_dakotaraptor_wing2_draw, 192, 336, rr_dakotaraptor_tail_draw, 0);

    rr_renderer_spritesheet_init(&mob_sprites[6], NULL, 144, 240, rr_pachycephalosaurus_head_draw,
    192, 336, rr_pachycephalosaurus_body_draw, 240, 240, rr_pachycephalosaurus_leg1_draw, 
    240, 240, rr_pachycephalosaurus_leg2_draw, 192, 336, rr_pachycephalosaurus_tail_draw, 0);

    rr_renderer_spritesheet_init(&mob_sprites[7], NULL, 144, 240, rr_ornithomimus_head_draw, 
    192, 336, rr_ornithomimus_body_draw, 144, 240, rr_ornithomimus_wing1_draw, 144, 240, 
    rr_ornithomimus_wing2_draw, 192, 336, rr_ornithomimus_tail_draw, 0);

    rr_renderer_spritesheet_init(&mob_sprites[8], NULL, 144, 144, rr_ankylosaurus_head_draw, 
    192, 336, rr_ankylosaurus_body_draw, 192, 336, rr_ankylosaurus_tail_draw, 0);
    
    rr_renderer_spritesheet_init(&mob_sprites[9], NULL, 144, 240, rr_meteor_draw, 0);

    rr_renderer_spritesheet_init(&mob_sprites[10], NULL, 192, 336, rr_quetzalcoatlus_head_draw, 
    192, 336, rr_quetzalcoatlus_body_draw, 192, 336, rr_quetzalcoatlus_wing1_draw, 192, 336, 
    rr_quetzalcoatlus_wing2_draw, 0);

    rr_renderer_spritesheet_init(&mob_sprites[11], NULL, 192, 336, rr_pectinodon_head_draw, 
    192, 336, rr_pectinodon_body_draw, 144, 240, rr_pectinodon_wing1_draw, 144, 240, 
    rr_pectinodon_wing2_draw, 192, 336, rr_pectinodon_tail_draw, 0);

    rr_renderer_spritesheet_init(&mob_sprites[12], NULL, 144, 240, rr_edmontosaurus_head_draw, 
    192, 336, rr_edmontosaurus_body_draw, 240, 240, rr_edmontosaurus_leg1_draw, 240, 240, 
    rr_edmontosaurus_leg2_draw, 192, 336, rr_edmontosaurus_tail_draw, 0);

    rr_renderer_spritesheet_init(&mob_sprites[13], NULL, 144, 240, rr_king_mackarel_head_draw, 
    192, 336, rr_king_mackarel_body_draw, 144, 144, rr_king_mackarel_fin1_draw, 144, 144, 
    rr_king_mackarel_fin2_draw, 240, 240, rr_king_mackarel_tail_draw, 0);

    rr_renderer_spritesheet_init(&mob_sprites[14], NULL, 240, 240, rr_sea_snail_head_draw, 240, 240, rr_sea_snail_body_draw, 0);

    rr_renderer_spritesheet_init(&mob_sprites[15], NULL, 192, 336, rr_seagull_body_draw, 
    432, 288, rr_seagull_wing2_draw, 432, 288, rr_seagull_wing1_draw, 0);

    rr_renderer_spritesheet_init(&mob_sprites[16], NULL, 384, 384, rr_kelp_draw, 0);
}