#pragma once

#include <Shared/Entity.h>
#include <Shared/Vector.h>

struct rr_simulation;
struct rr_binary_encoder;

// check if there's rr_component_physical_set function before setting a field
struct rr_component_physical
{
    EntityIdx parentID;
    float radius;
    float x;
    float y;
    float angle;
    float friction;
    float restitution;
    float mass;
    uint32_t deletion_tick;
    uint32_t query_id;
    struct rr_vector velocity;
    struct rr_vector acceleration;
    uint64_t protocol_state;
};

void rr_component_physical_write(struct rr_component_physical *, struct rr_binary_encoder *, int is_creation);
void rr_component_physical_read(struct rr_component_physical *, struct rr_binary_encoder *);

void rr_component_physical_set_x(struct rr_component_physical *, float);
void rr_component_physical_set_y(struct rr_component_physical *, float);
void rr_component_physical_set_angle(struct rr_component_physical *, float);
void rr_component_physical_set_radius(struct rr_component_physical *, float);
