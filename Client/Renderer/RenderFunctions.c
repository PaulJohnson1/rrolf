#include <Client/Renderer/RenderFunctions.h>

#include <math.h>
#include <stdio.h>

#include <Client/Assets/Render.h>
#include <Client/Assets/RenderFunctions.h>
#include <Client/Game.h>
#include <Client/Renderer/Renderer.h>
#include <Shared/StaticData.h>

// clang-format off
void rr_renderer_render_mob(struct rr_renderer *renderer, struct rr_game *game,
                            uint8_t id, float animation_tick, float turning_value, uint8_t flags)
{
    if (game->cache.ourpetsnake_mode)
    {
        rr_renderer_set_fill(renderer, 0xff888888);
        rr_renderer_set_stroke(renderer, 0xff6c6c6c);
        rr_renderer_set_line_width(renderer, 5);
        rr_renderer_begin_path(renderer);
        rr_renderer_arc(renderer, 0, 0, RR_MOB_DATA[id].radius);
        rr_renderer_fill(renderer);
        rr_renderer_stroke(renderer);
        return;
    }
    struct rr_renderer_context_state original_state;
    struct rr_renderer_context_state state;

    rr_renderer_context_state_init(renderer, &original_state);
    switch (id)
    {
    case rr_mob_id_triceratops:
        rr_renderer_rotate(renderer, M_PI / 2);
        rr_renderer_scale(renderer, 0.2f);

        rr_renderer_context_state_init(renderer, &state);
            rr_renderer_translate(renderer, 0.0f, animation_tick * 10.0f);
            if (flags)
                rr_renderer_draw_image(renderer, &game->mob_triceratops_legs[0]);
            else
                rr_triceratops_leg1_draw(renderer);
        rr_renderer_context_state_free(renderer, &state);

        rr_renderer_context_state_init(renderer, &state);
            rr_renderer_translate(renderer, 0.0f, animation_tick * -10.0f);
            if (flags)
                rr_renderer_draw_image(renderer, &game->mob_triceratops_legs[1]);
            else
                rr_triceratops_leg2_draw(renderer);
        rr_renderer_context_state_free(renderer, &state);

        rr_renderer_context_state_init(renderer, &state);
            rr_renderer_translate(renderer,  0, 75);
            rr_renderer_rotate(renderer, turning_value);
            rr_renderer_translate(renderer,  0, -75 + 155);
            if (flags)
                rr_renderer_draw_image(renderer, &game->mob_triceratops_tail);
            else
                rr_triceratops_tail_draw(renderer);
        rr_renderer_context_state_free(renderer, &state);

        if (flags)
            rr_renderer_draw_image(renderer, &game->mob_triceratops_body);
        else
            rr_triceratops_body_draw(renderer);

        rr_renderer_context_state_init(renderer, &state);
            rr_renderer_translate(renderer,  0, -75);
            rr_renderer_translate(renderer,  0, 75 - 145);
            if (flags)
                rr_renderer_draw_image(renderer, &game->mob_triceratops_head);
            else
                rr_triceratops_head_draw(renderer);
        rr_renderer_context_state_free(renderer, &state);
        break;
    case rr_mob_id_trex:
        rr_renderer_rotate(renderer, M_PI / 2);
        rr_renderer_scale(renderer, 0.22f);

        rr_renderer_context_state_init(renderer, &state);
            rr_renderer_translate(renderer, 0.0f, animation_tick * 10.0f);
            if (flags & 1)
                rr_renderer_draw_image(renderer, flags & 2 ? &game->mob_trex_friendly_legs[0] : &game->mob_trex_legs[0]);
            else
                rr_t_rex_leg1_draw(renderer);
        rr_renderer_context_state_free(renderer, &state);

        rr_renderer_context_state_init(renderer, &state);
            rr_renderer_translate(renderer, 0.0f, animation_tick * -10.0f);
            if (flags & 1)
                rr_renderer_draw_image(renderer, flags & 2 ? &game->mob_trex_friendly_legs[1] : &game->mob_trex_legs[1]);
            else
                rr_t_rex_leg2_draw(renderer);
        rr_renderer_context_state_free(renderer, &state);

    rr_renderer_context_state_init(renderer, &state);
        rr_renderer_translate(renderer,  0, 75);
        rr_renderer_rotate(renderer, turning_value);
        rr_renderer_translate(renderer,  0, -75 + 150);
        if (flags & 1)
            rr_renderer_draw_image(renderer, flags & 2 ? &game->mob_trex_friendly_tail : &game->mob_trex_tail);
        else
            rr_t_rex_tail_draw(renderer);
    rr_renderer_context_state_free(renderer, &state);
    
    if (flags & 1)
        rr_renderer_draw_image(renderer, flags & 2 ? &game->mob_trex_friendly_body : &game->mob_trex_body);
    else
        rr_t_rex_body_draw(renderer);
    
    rr_renderer_translate(renderer, 0, -125);
    if (flags & 1)
        rr_renderer_draw_image(renderer, flags & 2 ? &game->mob_trex_friendly_head : &game->mob_trex_head);
    else
        rr_t_rex_head_draw(renderer);
    break;
    case rr_mob_id_fern:
        rr_renderer_scale(renderer, 0.12f);
        if (flags)
            rr_renderer_draw_image(renderer, &game->mob_fern);
        else
            rr_fern_draw(renderer);
        break;
    case rr_mob_id_tree:
        rr_renderer_rotate(renderer, M_PI / 2);
        rr_renderer_scale(renderer, 0.30f);
        if (flags)
            rr_renderer_draw_image(renderer, &game->mob_tree);
        else
            rr_tree_draw(renderer);
        break;
    case rr_mob_id_pteranodon:
        rr_renderer_rotate(renderer, M_PI / 2);
        rr_renderer_scale(renderer, 0.15f);

        rr_renderer_context_state_init(renderer, &state);
            rr_renderer_rotate(renderer, animation_tick * 0.1f);
            rr_renderer_translate(renderer, 175, 0);
            if (flags)
                rr_renderer_draw_image(renderer, &game->mob_pteranodon_wings[0]);
            else
                rr_pteranodon_wing1_draw(renderer);
        rr_renderer_context_state_free(renderer, &state);

        rr_renderer_context_state_init(renderer, &state);
            rr_renderer_rotate(renderer, animation_tick * -0.1f);
            rr_renderer_translate(renderer, -175, 0);
            if (flags)
                rr_renderer_draw_image(renderer, &game->mob_pteranodon_wings[1]);
            else
                rr_pteranodon_wing2_draw(renderer);
        rr_renderer_context_state_free(renderer, &state);
        if (flags)
            rr_renderer_draw_image(renderer, &game->mob_pteranodon_body);
        else
            rr_pteranodon_body_draw(renderer);
        break;
    case rr_mob_id_dakotaraptor:
        rr_renderer_rotate(renderer, M_PI / 2);
        rr_renderer_scale(renderer, 0.16f);

        rr_renderer_context_state_init(renderer, &state);
            rr_renderer_translate(renderer, -65, 0);
            rr_renderer_rotate(renderer, animation_tick * 0.1f);
            if (flags)
                rr_renderer_draw_image(renderer, &game->mob_dakotaraptor_wings[0]);
            else
                rr_dakotaraptor_wing1_draw(renderer);
        rr_renderer_context_state_free(renderer, &state);
        
        rr_renderer_context_state_init(renderer, &state);
            rr_renderer_translate(renderer, 65, 0);
            rr_renderer_rotate(renderer, animation_tick * -0.1f);
            if (flags)
                rr_renderer_draw_image(renderer, &game->mob_dakotaraptor_wings[1]);
            else
                rr_dakotaraptor_wing2_draw(renderer);
        rr_renderer_context_state_free(renderer, &state);

        rr_renderer_context_state_init(renderer, &state);
            rr_renderer_translate(renderer, 0, 155);
            rr_renderer_rotate(renderer, turning_value);
            rr_renderer_translate(renderer,  0, 0);
            if (flags)
                rr_renderer_draw_image(renderer, &game->mob_dakotaraptor_tail);
            else
                rr_dakotaraptor_tail_draw(renderer);
        rr_renderer_context_state_free(renderer, &state);

        if (flags)
            rr_renderer_draw_image(renderer, &game->mob_dakotaraptor_body);
        else
            rr_dakotaraptor_body_draw(renderer);

        rr_renderer_context_state_init(renderer, &state);
            rr_renderer_translate(renderer, 0, -125);
            if (flags)
                rr_renderer_draw_image(renderer, &game->mob_dakotaraptor_head);
            else
                rr_dakotaraptor_head_draw(renderer);
        rr_renderer_context_state_free(renderer, &state);
        break;
    case rr_mob_id_pachycephalosaurus:
        rr_renderer_rotate(renderer, M_PI / 2);
        rr_renderer_scale(renderer, 0.16f);

        rr_renderer_context_state_init(renderer, &state);
            rr_renderer_translate(renderer, 0.0f, animation_tick * 10.0f);
            if (flags)
                rr_renderer_draw_image(renderer, &game->mob_pachycephalosaurus_legs[0]);
            else
                rr_pachycephalosaurus_leg1_draw(renderer);
        rr_renderer_context_state_free(renderer, &state);

        rr_renderer_context_state_init(renderer, &state);
            rr_renderer_translate(renderer, 0.0f, animation_tick * -10.0f);
            if (flags)
                rr_renderer_draw_image(renderer, &game->mob_pachycephalosaurus_legs[1]);
            else
                rr_pachycephalosaurus_leg2_draw(renderer);
        rr_renderer_context_state_free(renderer, &state);

        rr_renderer_context_state_init(renderer, &state);
            rr_renderer_translate(renderer, 0, 155);
            rr_renderer_rotate(renderer, turning_value);
            if (flags)
                rr_renderer_draw_image(renderer, &game->mob_pachycephalosaurus_tail);
            else
                rr_pachycephalosaurus_tail_draw(renderer);
        rr_renderer_context_state_free(renderer, &state);

        if (flags)
            rr_renderer_draw_image(renderer, &game->mob_pachycephalosaurus_body);
        else
            rr_pachycephalosaurus_body_draw(renderer);
        
        rr_renderer_context_state_init(renderer, &state);
            rr_renderer_translate(renderer, 0, -135);
            if (flags)
                rr_renderer_draw_image(renderer, &game->mob_pachycephalosaurus_head);
            else
                rr_pachycephalosaurus_head_draw(renderer);
        rr_renderer_context_state_free(renderer, &state);
        break;
    case rr_mob_id_ornithomimus:
        rr_renderer_rotate(renderer, M_PI / 2);
        rr_renderer_scale(renderer, 0.16f);

        rr_renderer_context_state_init(renderer, &state);
            rr_renderer_translate(renderer, 70, 0);
            rr_renderer_rotate(renderer, animation_tick * 0.1f);
            if (flags)
                rr_renderer_draw_image(renderer, &game->mob_ornithomimus_wings[0]);
            else
                rr_ornithomimus_wing1_draw(renderer);
        rr_renderer_context_state_free(renderer, &state);
        
        rr_renderer_context_state_init(renderer, &state);
            rr_renderer_translate(renderer, -70, 0);
            rr_renderer_rotate(renderer, animation_tick * -0.1f);
            if (flags)
                rr_renderer_draw_image(renderer, &game->mob_ornithomimus_wings[1]);
            else
                rr_ornithomimus_wing2_draw(renderer);
        rr_renderer_context_state_free(renderer, &state);

        rr_renderer_context_state_init(renderer, &state);
            rr_renderer_translate(renderer, 0, 155);
            rr_renderer_rotate(renderer, turning_value);
            if (flags)
                rr_renderer_draw_image(renderer, &game->mob_ornithomimus_tail);
            else
                rr_ornithomimus_tail_draw(renderer);
        rr_renderer_context_state_free(renderer, &state);

        if (flags)
            rr_renderer_draw_image(renderer, &game->mob_ornithomimus_body);
        else
            rr_ornithomimus_body_draw(renderer);
        
        rr_renderer_context_state_init(renderer, &state);
            rr_renderer_translate(renderer, 0, -145);
            if (flags)
                rr_renderer_draw_image(renderer, &game->mob_ornithomimus_head); //fix
            else
                rr_ornithomimus_head_draw(renderer);
        rr_renderer_context_state_free(renderer, &state);
        break;
    case rr_mob_id_ankylosaurus:
        rr_renderer_rotate(renderer, M_PI / 2);
        rr_renderer_scale(renderer, 0.2f);

        rr_renderer_context_state_init(renderer, &state);
            rr_renderer_translate(renderer, 0, 155);
            rr_renderer_rotate(renderer, turning_value);
            if (flags)
                rr_renderer_draw_image(renderer, &game->mob_ankylosaurus_tail);
            else
                rr_ankylosaurus_tail_draw(renderer);
        rr_renderer_context_state_free(renderer, &state);

        if (flags)
            rr_renderer_draw_image(renderer, &game->mob_ankylosaurus_body);
        else
            rr_ankylosaurus_body_draw(renderer);
        
        rr_renderer_context_state_init(renderer, &state);
            rr_renderer_translate(renderer, 0, -145);
            if (flags)
                rr_renderer_draw_image(renderer, &game->mob_ankylosaurus_head); //fix
            else
                rr_ankylosaurus_head_draw(renderer);
        rr_renderer_context_state_free(renderer, &state);
        break;
    case rr_mob_id_meteor:
        rr_renderer_scale(renderer, 0.4f);
        if (flags)
            rr_renderer_draw_image(renderer, &game->mob_meteor);
        else
            rr_meteor_draw(renderer);
        break;
    case rr_mob_id_quetzalcoatlus:
        rr_renderer_rotate(renderer, M_PI / 2);
        rr_renderer_scale(renderer, 0.2f);

        rr_renderer_context_state_init(renderer, &state);
            rr_renderer_rotate(renderer, animation_tick * 0.1f);
            rr_renderer_translate(renderer, 150, 25);
            if (flags)
                rr_renderer_draw_image(renderer, &game->mob_quetzalcoatlus_wings[0]);
            else
                rr_quetzalcoatlus_wing1_draw(renderer);
        rr_renderer_context_state_free(renderer, &state);

        rr_renderer_context_state_init(renderer, &state);
            rr_renderer_rotate(renderer, animation_tick * -0.1f);
            rr_renderer_translate(renderer, -150, 25);
            if (flags)
                rr_renderer_draw_image(renderer, &game->mob_quetzalcoatlus_wings[1]);
            else
                rr_quetzalcoatlus_wing2_draw(renderer);
        rr_renderer_context_state_free(renderer, &state);
        if (flags)
            rr_renderer_draw_image(renderer, &game->mob_quetzalcoatlus_body);
        else
            rr_quetzalcoatlus_body_draw(renderer);
        rr_renderer_translate(renderer, 0, -165);
        if (flags)
            rr_renderer_draw_image(renderer, &game->mob_quetzalcoatlus_head);
        else
            rr_quetzalcoatlus_head_draw(renderer);
        break;
    case rr_mob_id_pectinodon:
        rr_renderer_rotate(renderer, M_PI / 2);
        rr_renderer_scale(renderer, 0.16f);

        rr_renderer_context_state_init(renderer, &state);
            rr_renderer_translate(renderer, -90, 25);
            rr_renderer_rotate(renderer, animation_tick * 0.1f);
            if (flags)
                rr_renderer_draw_image(renderer, &game->mob_pectinodon_wings[0]);
            else
                rr_pectinodon_wing1_draw(renderer);
        rr_renderer_context_state_free(renderer, &state);
        
        rr_renderer_context_state_init(renderer, &state);
            rr_renderer_translate(renderer, 90, 25);
            rr_renderer_rotate(renderer, animation_tick * -0.1f);
            if (flags)
                rr_renderer_draw_image(renderer, &game->mob_pectinodon_wings[1]);
            else
                rr_pectinodon_wing2_draw(renderer);
        rr_renderer_context_state_free(renderer, &state);

        rr_renderer_context_state_init(renderer, &state);
            rr_renderer_translate(renderer, 0, 155);
            rr_renderer_rotate(renderer, turning_value);
            rr_renderer_translate(renderer,  0, 0);
            if (flags)
                rr_renderer_draw_image(renderer, &game->mob_pectinodon_tail);
            else
                rr_pectinodon_tail_draw(renderer);
        rr_renderer_context_state_free(renderer, &state);
        rr_renderer_context_state_init(renderer, &state);
            rr_renderer_translate(renderer, 0, -75);
            if (flags)
                rr_renderer_draw_image(renderer, &game->mob_pectinodon_body);
            else
                rr_pectinodon_body_draw(renderer);
        rr_renderer_context_state_free(renderer, &state);
        rr_renderer_context_state_init(renderer, &state);
            rr_renderer_translate(renderer, 0, -200);
            if (flags)
                rr_renderer_draw_image(renderer, &game->mob_pectinodon_head);
            else
                rr_pectinodon_head_draw(renderer);
        rr_renderer_context_state_free(renderer, &state);
        break;
    default:
        break;
    }

    rr_renderer_context_state_free(renderer, &original_state);
}

// clang-format on
