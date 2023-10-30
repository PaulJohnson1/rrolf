#include <Shared/Component/Flower.h>

#include <stdio.h>
#include <string.h>

#include <Shared/Entity.h>
#include <Shared/SimulationCommon.h>
#include <Shared/pb.h>

#define FOR_EACH_PUBLIC_FIELD                                                  \
    X(eye_angle, float32)                                                      \
    X(face_flags, uint8)                                                       \
    X(level, varuint)

enum
{
    state_flags_eye_angle = 0b000001,
    state_flags_face_flags = 0b000010,
    state_flags_level = 0b000100,
    state_flags_nickname = 0b001000,
    state_flags_all = 0b001111
};

void rr_component_flower_init(struct rr_component_flower *this,
                              struct rr_simulation *simulation)
{
    memset(this, 0, sizeof *this);
}

#ifdef RR_SERVER
#include <Server/Simulation.h>
#endif

void rr_component_flower_free(struct rr_component_flower *this,
                              struct rr_simulation *simulation)
{
#ifdef RR_SERVER
    if (rr_simulation_entity_alive(simulation, rr_simulation_get_relations(simulation, this->parent_id)->owner))
    {
        EntityHash p_id = rr_simulation_get_relations(simulation, this->parent_id)->owner;
        struct rr_component_player_info *player_info = rr_simulation_get_player_info(simulation, p_id);
        rr_component_player_info_set_flower_id(player_info, RR_NULL_ENTITY);
    }
#endif
}

#ifdef RR_SERVER
void rr_component_flower_write(struct rr_component_flower *this,
                               struct proto_bug *encoder, int is_creation,
                               struct rr_component_player_info *client)
{
    uint64_t state = this->protocol_state | (state_flags_all * is_creation);
    proto_bug_write_varuint(encoder, state, "flower component state");
#define X(NAME, TYPE) RR_ENCODE_PUBLIC_FIELD(NAME, TYPE);
    FOR_EACH_PUBLIC_FIELD
#undef X
    if (state & state_flags_nickname)
        proto_bug_write_string(encoder, this->nickname, 16, "nickname");
}

RR_DEFINE_PUBLIC_FIELD(flower, uint8_t, face_flags)
RR_DEFINE_PUBLIC_FIELD(flower, float, eye_angle)
RR_DEFINE_PUBLIC_FIELD(flower, uint32_t, level)
#endif

#ifdef RR_CLIENT
void rr_component_flower_read(struct rr_component_flower *this,
                              struct proto_bug *encoder)
{
    uint64_t state = proto_bug_read_varuint(encoder, "flower component state");
#define X(NAME, TYPE) RR_DECODE_PUBLIC_FIELD(NAME, TYPE);
    FOR_EACH_PUBLIC_FIELD
#undef X
    if (state & state_flags_nickname)
        proto_bug_read_string(encoder, this->nickname, 16, "nickname");
}
#endif