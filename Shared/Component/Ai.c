#include <Shared/Component/Ai.h>

#include <string.h>

#include <Shared/pb.h>
#include <Shared/Entity.h>
#include <Shared/SimulationCommon.h>

void rr_component_ai_init(struct rr_component_ai *this, struct rr_simulation *simulation)
{
    memset(this, 0, sizeof *this);
    RR_SERVER_ONLY(this->ai_state = rr_ai_state_idle;)
}

void rr_component_ai_free(struct rr_component_ai *this, struct rr_simulation *simulation)
{
}

#ifdef RR_SERVER
void rr_component_ai_write(struct rr_component_ai *this, struct proto_bug *encoder, int is_creation)
{
}

#endif

#ifdef RR_CLIENT
void rr_component_ai_read(struct rr_component_ai *this, struct proto_bug *encoder)
{
}
#endif