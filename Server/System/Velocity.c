#include <Server/System/Velocity.h>

#include <math.h>

#include <Server/Simulation.h>
#include <Shared/Entity.h>
#include <Shared/Vector.h>
#include <Shared/StaticData.h>

static void system(EntityIdx id, void *simulation)
{
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, id);
    rr_vector_scale(&physical->velocity, physical->friction);
    if (physical->webbed)
        physical->acceleration_scale *= 0.2;
    if (physical->stun_ticks > 0)
    {
        if (!rr_simulation_has_petal(simulation, id))
            physical->acceleration_scale = 0;
        --physical->stun_ticks;
    }
    struct rr_vector accel = {
        physical->acceleration.x * physical->acceleration_scale,
        physical->acceleration.y * physical->acceleration_scale};
    rr_vector_add(&physical->velocity, &accel);
    physical->acceleration_scale = 1;
    physical->webbed = 0;
    struct rr_vector vel = {physical->velocity.x, physical->velocity.y};
    struct rr_vector add = {vel.x, vel.y};
    rr_vector_set_magnitude(&add, physical->radius);
    float mag = rr_vector_get_magnitude(&vel);
    while (1)
    {
        if (mag >= physical->radius)
        {
            mag -= physical->radius;
            rr_component_physical_set_x(physical, physical->x + add.x);
            rr_component_physical_set_y(physical, physical->y + add.y);
            rr_vector_sub(&vel, &add);
        }
        else
        {
            rr_component_physical_set_x(physical, physical->x + vel.x);
            rr_component_physical_set_y(physical, physical->y + vel.y);
        }
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
        #define offset(a,b) \
        ((x + a < 0 || y + b < 0 || x + a >= RR_MAZE_DIM || y + b >= RR_MAZE_DIM) ? 0 : RR_MAZE_HELL_CREEK[y+b][x+a])
        if (RR_MAZE_HELL_CREEK[y][x] != 1)
        {
            uint8_t tile = RR_MAZE_HELL_CREEK[y][x];
            if (tile == 0)
            {
                struct rr_vector vel = {physical->x - ((x + 0.5) * RR_MAZE_GRID_SIZE), physical->y - ((y + 0.5) * RR_MAZE_GRID_SIZE)};
                struct rr_vector proj = {vel.x, vel.y};
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
        if (x > 0 && RR_MAZE_HELL_CREEK[y][x-1] != 1 && physical->x - x * RR_MAZE_GRID_SIZE < physical->radius)
        {
            uint8_t tile = RR_MAZE_HELL_CREEK[y][x-1];
            if (tile == 0)
            {
                rr_component_physical_set_x(physical, x * RR_MAZE_GRID_SIZE + physical->radius);
                
            }
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
        if (y > 0 && RR_MAZE_HELL_CREEK[y-1][x] != 1 && physical->y - y * RR_MAZE_GRID_SIZE < physical->radius)
        {
            uint8_t tile = RR_MAZE_HELL_CREEK[y-1][x];
            if (tile == 0)
            {
                rr_component_physical_set_y(physical, y * RR_MAZE_GRID_SIZE + physical->radius);
                
            }
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
        if (x + 1 < RR_MAZE_DIM && RR_MAZE_HELL_CREEK[y][x+1] != 1 && (x + 1) * RR_MAZE_GRID_SIZE - physical->x < physical->radius)
        {
            uint8_t tile = RR_MAZE_HELL_CREEK[y][x+1];
            if (tile == 0)
            {
                rr_component_physical_set_x(physical, (x + 1) * RR_MAZE_GRID_SIZE - physical->radius);
                
            }
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
        if (y + 1 < RR_MAZE_DIM && RR_MAZE_HELL_CREEK[y+1][x] != 1 && (y + 1) * RR_MAZE_GRID_SIZE - physical->y < physical->radius)
        {
            uint8_t tile = RR_MAZE_HELL_CREEK[y+1][x];
            if (tile == 0)
            {
                rr_component_physical_set_y(physical, (y + 1) * RR_MAZE_GRID_SIZE - physical->radius);
                
            }
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
        if (mag < physical->radius)
            break;
    }
    if (rr_simulation_has_flower(simulation, id))
    {
        if (physical->acceleration.x != 0.0f ||
            physical->acceleration.y != 0.0f)
        {
            rr_component_flower_set_eye_angle(
                rr_simulation_get_flower(simulation, id),
                rr_vector_theta(&physical->acceleration));
        }
    }
    rr_vector_set(&physical->acceleration, 0, 0);
}

void rr_system_velocity_tick(struct rr_simulation *simulation)
{
    rr_simulation_for_each_physical(simulation, simulation, system);
}
