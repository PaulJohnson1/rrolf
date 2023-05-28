#include <Client/Renderer/ComponentRender.h>

#include <Client/Simulation.h>
#include <Client/Renderer/Renderer.h>

void rr_component_health_render(EntityIdx entity, struct rr_simulation *simulation, struct rr_renderer *renderer)
{
    struct rr_component_physical *physical = rr_simulation_get_physical(simulation, entity);
    struct rr_component_health *health = rr_simulation_get_health(simulation, entity);
    if (health->hidden)
        return;
    if (rr_simulation_has_flower(simulation, health->parent_id))
    {
        struct rr_component_relations *relations = rr_simulation_get_relations(simulation, health->parent_id);

        if (relations->owner == simulation->player_info)
            if (health->health == health->max_health)
                return;
    }

    rr_renderer_translate(renderer, physical->lerp_x, physical->lerp_y + physical->radius + 30);
    float length = 40;

    if (rr_simulation_has_mob(simulation, health->parent_id))
    {
        struct rr_component_mob *mob = rr_simulation_get_mob(simulation, entity);
        length += mob->rarity * 5;
        rr_renderer_set_fill(renderer, RR_RARITY_COLORS[mob->rarity]);
        rr_renderer_set_stroke(renderer, 0xff222222);
        rr_renderer_set_text_size(renderer, 14);
        rr_renderer_set_line_width(renderer, 1.68);
        rr_renderer_set_text_align(renderer, 2);
        rr_renderer_set_text_baseline(renderer, 0);
        rr_renderer_stroke_text(renderer, RR_RARITY_NAMES[mob->rarity], length, 6);
        rr_renderer_fill_text(renderer, RR_RARITY_NAMES[mob->rarity], length, 6);        
    }

    rr_renderer_set_line_cap(renderer, 1);
    rr_renderer_set_stroke(renderer, 0xff222222);
    rr_renderer_set_line_width(renderer, 10);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -length, 0);
    rr_renderer_line_to(renderer, length, 0);
    rr_renderer_stroke(renderer);

    rr_renderer_set_stroke(renderer, 0xff75dd34);
    rr_renderer_set_line_width(renderer, 7);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -length, 0);
    rr_renderer_line_to(renderer, -length + 2 * length * health->lerp_health / health->max_health, 0);
    rr_renderer_stroke(renderer);
}