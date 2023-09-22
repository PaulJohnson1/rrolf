#pragma once

#include <Shared/Entity.h>

struct rr_simulation;

void rr_system_ai_tick(struct rr_simulation *);
void rr_system_camera_tick(struct rr_simulation *);
void rr_system_centipede_tick(struct rr_simulation *);
void rr_system_collision_detection_tick(struct rr_simulation *);
void rr_system_collision_resolution_tick(struct rr_simulation *);
void rr_system_drops_tick(struct rr_simulation *);
void rr_system_health_tick(struct rr_simulation *);
void rr_system_petal_behavior_tick(struct rr_simulation *);
void rr_system_velocity_tick(struct rr_simulation *);
void rr_system_web_tick(struct rr_simulation *);