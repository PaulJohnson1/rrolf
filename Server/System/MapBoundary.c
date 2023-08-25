#include <Server/System/MapBoundary.h>

#include <Server/Simulation.h>

#include <Shared/Component/Physical.h>
#include <Shared/Entity.h>
#include <Shared/Vector.h>

static void rr_system_map_boundary_foreach_function(EntityIdx id,
                                                    void *simulation)
{
    struct rr_simulation *this = simulation;
    if (rr_simulation_has_projectile(this, id) ||
        rr_simulation_has_web(this, id) || rr_simulation_has_petal(this, id))
        return;
    struct rr_component_physical *physical =
        rr_simulation_get_physical(this, id);
    struct rr_component_arena *arena = rr_simulation_get_arena(this, 1);
    if (physical->x < physical->radius)
        rr_component_physical_set_x(physical, physical->radius);
    else if (physical->x > RR_ARENA_LENGTH - physical->radius)
        rr_component_physical_set_x(physical, RR_ARENA_LENGTH - physical->radius);
    if (physical->y < physical->radius)
        rr_component_physical_set_y(physical, physical->radius);
    else if (physical->y > RR_ARENA_LENGTH - physical->radius)
        rr_component_physical_set_y(physical, RR_ARENA_LENGTH - physical->radius);
    int32_t x = physical->x / RR_MAZE_GRID_SIZE;
    int32_t y = physical->y / RR_MAZE_GRID_SIZE;
    //add a check for in-wall
    if (RR_MAZE_HELL_CREEK[x][y] != 1)
    {
        uint8_t tile = RR_MAZE_HELL_CREEK[x][y];
        if (tile == 0)
        {
            struct rr_vector vel = {physical->x - ((x + 0.5) * RR_MAZE_GRID_SIZE), physical->y - ((y + 0.5) * RR_MAZE_GRID_SIZE)};
            rr_vector_normalize(&vel);
            physical->velocity.x += 10 * vel.x;
            physical->velocity.y += 10 * vel.y;
        }
        else
        {
            uint8_t left = (tile >> 1) & 1;
            uint8_t top = tile & 1;
            uint8_t inverse = ((tile >> 3) & 1);
            float cx = (x + left) * RR_MAZE_GRID_SIZE;
            float cy = (y + top) * RR_MAZE_GRID_SIZE;
            struct rr_vector dist = {physical->x - cx, physical->y - cy};
            if (rr_vector_get_magnitude(&dist) > RR_MAZE_GRID_SIZE - physical->radius && inverse == 0)
            {
                rr_vector_set_magnitude(&dist, RR_MAZE_GRID_SIZE - physical->radius);
                rr_component_physical_set_x(physical, cx + dist.x);
                rr_component_physical_set_y(physical, cy + dist.y);
            }
            if (rr_vector_get_magnitude(&dist) < RR_MAZE_GRID_SIZE + physical->radius && inverse == 1)
            {
                rr_vector_set_magnitude(&dist, RR_MAZE_GRID_SIZE + physical->radius);
                rr_component_physical_set_x(physical, cx + dist.x);
                rr_component_physical_set_y(physical, cy + dist.y);
            }
        }
    }
    if (x > 0 && RR_MAZE_HELL_CREEK[x - 1][y] != 1 && physical->x - x * RR_MAZE_GRID_SIZE < physical->radius)
    {
        uint8_t tile = RR_MAZE_HELL_CREEK[x-1][y];
        if (tile == 0)
            rr_component_physical_set_x(physical, x * RR_MAZE_GRID_SIZE + physical->radius);
        else
        {
            uint8_t left = (tile >> 1) & 1;
            uint8_t top = tile & 1;
            uint8_t inverse = ((tile >> 3) & 1);
            float cx = (x - 1 + left) * RR_MAZE_GRID_SIZE;
            float cy = (y + top) * RR_MAZE_GRID_SIZE;
            struct rr_vector dist = {physical->x - cx, physical->y - cy};
            if (rr_vector_get_magnitude(&dist) > RR_MAZE_GRID_SIZE - physical->radius && inverse == 0)
            {
                rr_vector_set_magnitude(&dist, RR_MAZE_GRID_SIZE - physical->radius);
                rr_component_physical_set_x(physical, cx + dist.x);
                rr_component_physical_set_y(physical, cy + dist.y);
            }
            if (rr_vector_get_magnitude(&dist) < RR_MAZE_GRID_SIZE + physical->radius && inverse == 1)
            {
                rr_vector_set_magnitude(&dist, RR_MAZE_GRID_SIZE + physical->radius);
                rr_component_physical_set_x(physical, cx + dist.x);
                rr_component_physical_set_y(physical, cy + dist.y);
            }
        }
    }
    if (y > 0 && RR_MAZE_HELL_CREEK[x][y - 1] != 1 && physical->y - y * RR_MAZE_GRID_SIZE < physical->radius)
    {
        uint8_t tile = RR_MAZE_HELL_CREEK[x][y-1];
        if (tile == 0)
            rr_component_physical_set_y(physical, y * RR_MAZE_GRID_SIZE + physical->radius);
        else
        {
            uint8_t left = (tile >> 1) & 1;
            uint8_t top = tile & 1;
            uint8_t inverse = ((tile >> 3) & 1);
            float cx = (x + left) * RR_MAZE_GRID_SIZE;
            float cy = (y - 1 + top) * RR_MAZE_GRID_SIZE;
            struct rr_vector dist = {physical->x - cx, physical->y - cy};
            if (rr_vector_get_magnitude(&dist) > RR_MAZE_GRID_SIZE - physical->radius && inverse == 0)
            {
                rr_vector_set_magnitude(&dist, RR_MAZE_GRID_SIZE - physical->radius);
                rr_component_physical_set_x(physical, cx + dist.x);
                rr_component_physical_set_y(physical, cy + dist.y);
            }
            if (rr_vector_get_magnitude(&dist) < RR_MAZE_GRID_SIZE + physical->radius && inverse == 1)
            {
                rr_vector_set_magnitude(&dist, RR_MAZE_GRID_SIZE + physical->radius);
                rr_component_physical_set_x(physical, cx + dist.x);
                rr_component_physical_set_y(physical, cy + dist.y);
            }
        }
    }
    if (x + 1 < RR_MAZE_DIM && RR_MAZE_HELL_CREEK[x + 1][y] != 1 && (x + 1) * RR_MAZE_GRID_SIZE - physical->x < physical->radius)
    {
        uint8_t tile = RR_MAZE_HELL_CREEK[x+1][y];
        if (tile == 0)
            rr_component_physical_set_x(physical, (x + 1) * RR_MAZE_GRID_SIZE - physical->radius);
        else
        {
            uint8_t left = (tile >> 1) & 1;
            uint8_t top = tile & 1;
            uint8_t inverse = ((tile >> 3) & 1);
            float cx = (x + 1 + left) * RR_MAZE_GRID_SIZE;
            float cy = (y + top) * RR_MAZE_GRID_SIZE;
            struct rr_vector dist = {physical->x - cx, physical->y - cy};
            if (rr_vector_get_magnitude(&dist) > RR_MAZE_GRID_SIZE - physical->radius && inverse == 0)
            {
                rr_vector_set_magnitude(&dist, RR_MAZE_GRID_SIZE - physical->radius);
                rr_component_physical_set_x(physical, cx + dist.x);
                rr_component_physical_set_y(physical, cy + dist.y);
            }
            if (rr_vector_get_magnitude(&dist) < RR_MAZE_GRID_SIZE + physical->radius && inverse == 1)
            {
                rr_vector_set_magnitude(&dist, RR_MAZE_GRID_SIZE + physical->radius);
                rr_component_physical_set_x(physical, cx + dist.x);
                rr_component_physical_set_y(physical, cy + dist.y);
            }
        }
    }
    if (y + 1 < RR_MAZE_DIM && RR_MAZE_HELL_CREEK[x][y + 1] != 1 && (y + 1) * RR_MAZE_GRID_SIZE - physical->y < physical->radius)
    {
        uint8_t tile = RR_MAZE_HELL_CREEK[x][y+1];
        if (tile == 0)
            rr_component_physical_set_y(physical, (y + 1) * RR_MAZE_GRID_SIZE - physical->radius);
        else
        {
            uint8_t left = (tile >> 1) & 1;
            uint8_t top = tile & 1;
            uint8_t inverse = ((tile >> 3) & 1);
            float cx = (x + left) * RR_MAZE_GRID_SIZE;
            float cy = (y + 1 + top) * RR_MAZE_GRID_SIZE;
            struct rr_vector dist = {physical->x - cx, physical->y - cy};
            if (rr_vector_get_magnitude(&dist) > RR_MAZE_GRID_SIZE - physical->radius && inverse == 0)
            {
                rr_vector_set_magnitude(&dist, RR_MAZE_GRID_SIZE - physical->radius);
                rr_component_physical_set_x(physical, cx + dist.x);
                rr_component_physical_set_y(physical, cy + dist.y);
            }
            if (rr_vector_get_magnitude(&dist) < RR_MAZE_GRID_SIZE + physical->radius && inverse == 1)
            {
                rr_vector_set_magnitude(&dist, RR_MAZE_GRID_SIZE + physical->radius);
                rr_component_physical_set_x(physical, cx + dist.x);
                rr_component_physical_set_y(physical, cy + dist.y);
            }
        }
    }
}

void rr_system_map_boundary_tick(struct rr_simulation *simulation)
{
    rr_simulation_for_each_physical(simulation, simulation,
                                    rr_system_map_boundary_foreach_function);
}
