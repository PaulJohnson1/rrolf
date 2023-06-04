#include <Shared/Component/Projectile.h>

#include <string.h>

#include <Shared/pb.h>
#include <Shared/Entity.h>
#include <Shared/SimulationCommon.h>

enum
{
    state_flags_all = 0b000000
};

void rr_component_projectile_init(struct rr_component_projectile *this, struct rr_simulation *simulation)
{
    memset(this, 0, sizeof *this);
}

void rr_component_projectile_free(struct rr_component_projectile *this, struct rr_simulation *simulation)
{
}

#ifdef RR_SERVER
void rr_component_projectile_write(struct rr_component_projectile *this, struct proto_bug *encoder, int is_creation)
{
}

#endif

#ifdef RR_CLIENT
void rr_component_projectile_read(struct rr_component_projectile *this, struct proto_bug *encoder)
{
}
#endif