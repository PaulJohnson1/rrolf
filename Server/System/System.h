// Copyright (C) 2024  Paul Johnson

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.

// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include <Shared/Entity.h>

struct rr_simulation;

extern void rr_system_ai_tick(struct rr_simulation *);
extern void rr_system_camera_tick(struct rr_simulation *);
extern void rr_system_centipede_tick(struct rr_simulation *);
extern void rr_system_collision_detection_tick(struct rr_simulation *);
extern void rr_system_collision_resolution_tick(struct rr_simulation *);
extern void rr_system_drops_tick(struct rr_simulation *);
extern void rr_system_health_tick(struct rr_simulation *);
extern void rr_system_petal_behavior_tick(struct rr_simulation *);
extern void rr_system_velocity_tick(struct rr_simulation *);
extern void rr_system_web_tick(struct rr_simulation *);
