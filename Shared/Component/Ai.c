#include <Shared/Component/Ai.h>

#include <string.h>

#include <Shared/Encoder.h>
#include <Shared/Entity.h>
#include <Shared/SimulationCommon.h>

enum
{
    state_flags_all = 0b000000
};

void rr_component_ai_init(struct rr_component_ai *this)
{
    memset(this, 0, sizeof *this);
}

void rr_component_ai_free(struct rr_component_ai *this)
{
}

#ifdef RR_SERVER
void rr_component_ai_write(struct rr_component_ai *this, struct rr_encoder *encoder, int is_creation)
{
}

#endif

#ifdef RR_CLIENT
void rr_component_ai_read(struct rr_component_ai *this, struct rr_encoder *encoder)
{
}
#endif