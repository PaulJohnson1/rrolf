#pragma once

#include <Shared/Entity.h>

struct rr_game;
struct rr_simulation;
struct rr_component_player_info;

void rr_component_arena_render(EntityIdx, struct rr_game *, struct rr_simulation *);
void rr_component_drop_render(EntityIdx, struct rr_game *, struct rr_simulation *);
void rr_component_flower_render(EntityIdx, struct rr_game *, struct rr_simulation *);
void rr_component_health_render(EntityIdx, struct rr_game *, struct rr_simulation *);
void rr_component_mob_render(EntityIdx, struct rr_game *, struct rr_simulation *);
void rr_component_petal_render(EntityIdx, struct rr_game *, struct rr_simulation *);
void rr_component_web_render(EntityIdx, struct rr_game *, struct rr_simulation *);

void render_background(struct rr_component_player_info *, struct rr_game *);
