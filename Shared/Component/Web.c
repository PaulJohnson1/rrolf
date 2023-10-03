#include <Shared/Component/Web.h>

#include <string.h>

#include <Shared/Entity.h>
#include <Shared/SimulationCommon.h>
#include <Shared/pb.h>

void rr_component_web_init(struct rr_component_web *this,
                           struct rr_simulation *simulation)
{
    memset(this, 0, sizeof *this);
    RR_SERVER_ONLY(this->slow_factor = 1;)
}

void rr_component_web_free(struct rr_component_web *this,
                           struct rr_simulation *simulation)
{
}

#ifdef RR_SERVER
void rr_component_web_write(struct rr_component_web *this,
                            struct proto_bug *encoder, int is_creation,
                            struct rr_component_player_info *client)
{
}

#endif

#ifdef RR_CLIENT
void rr_component_web_read(struct rr_component_web *this,
                           struct proto_bug *encoder)
{
}
#endif