#include <Client/Simulation.h>

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <sys/time.h>

#include <Client/System/Interpolation.h>
#include <Shared/Bitset.h>
#include <Shared/pb.h>

long last = 0;
int ttt = 0;
void rr_simulation_init(struct rr_simulation *this)
{
    memset(this, 0, sizeof *this);
}

void rr_simulation_entity_create_with_id(struct rr_simulation *this, EntityIdx entity)
{
    rr_bitset_set(this->entity_tracker, entity);
}

void rr_simulation_read_binary(struct rr_simulation *this, struct proto_bug *encoder)
{
    struct timeval start;
    struct timeval end;

    gettimeofday(&start, NULL);
    EntityIdx id = 0;
    while (1)
    {
        id = proto_bug_read_varuint(encoder, "entity deletion id");
        if (id == RR_NULL_ENTITY)
            break;
        assert(id < RR_MAX_ENTITY_COUNT);
        assert(rr_bitset_get_bit(this->entity_tracker, id));
        rr_simulation_request_entity_deletion(this, id);
    }

    //assuming that player info is written first (is it though)
    while (1)
    {
        id = proto_bug_read_varuint(encoder, "entity update id");
        if (id == RR_NULL_ENTITY)
            break;
        uint8_t is_creation = !rr_bitset_get_bit(this->entity_tracker, id);
        uint32_t component_flags = proto_bug_read_varuint(encoder, "entity component flags");

        if (is_creation)
        {
#ifndef NDEBUG
            printf("create entity with id %d, components %d\n", id, component_flags);
#endif
            rr_bitset_set(this->entity_tracker, id);
#define XX(COMPONENT, ID)            \
    if (component_flags & (1 << ID)) \
        rr_simulation_add_##COMPONENT(this, id);
    RR_FOR_EACH_COMPONENT
#undef XX
        }

#define XX(COMPONENT, ID)\
    if (component_flags & (1 << ID))\
        rr_component_##COMPONENT##_read(rr_simulation_get_##COMPONENT(this, id), encoder);
    RR_FOR_EACH_COMPONENT
#undef XX
    }

    this->player_info = proto_bug_read_varuint(encoder, "pinfo id");
    this->game_over = proto_bug_read_uint8(encoder, "game over");
    rr_bitset_for_each_bit(this->pending_deletions, this->pending_deletions + (RR_BITSET_ROUND(RR_MAX_ENTITY_COUNT)), this, __rr_simulation_pending_deletion_free_components);
    rr_bitset_for_each_bit(this->pending_deletions, this->pending_deletions + (RR_BITSET_ROUND(RR_MAX_ENTITY_COUNT)), this, __rr_simulation_pending_deletion_unset_entity);
    memset(this->pending_deletions, 0, RR_BITSET_ROUND(RR_MAX_ENTITY_COUNT) * sizeof *this->pending_deletions);

    gettimeofday(&end, NULL);
    long elapsed_time = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    //printf("tick took %ld microseconds\n", elapsed_time);
    long now_time = (end.tv_sec) * 1000000 + (end.tv_usec);
    if (ttt++ == 10) 
    {printf("%ld ms tick\n", (now_time - last) / 10000);ttt=0;last = now_time;}
    
}

void rr_simulation_tick(struct rr_simulation *this, float delta)
{
    rr_system_interpolation_tick(this, delta);
}
