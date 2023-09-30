#include <Shared/Component/Centipede.h>

#include <string.h>

#include <Shared/Entity.h>
#include <Shared/SimulationCommon.h>
#include <Shared/pb.h>

void rr_component_centipede_init(struct rr_component_centipede *this,
                                 struct rr_simulation *simulation)
{
    memset(this, 0, sizeof *this);
}

#ifdef RR_SERVER
#include <Server/Simulation.h>
#endif

void rr_component_centipede_free(struct rr_component_centipede *this,
                                 struct rr_simulation *simulation)
{
#ifdef RR_SERVER
    if (rr_simulation_entity_alive(simulation, this->parent_node))
    {
        struct rr_component_centipede *parent_node =
            rr_simulation_get_centipede(simulation, this->parent_node);
        parent_node->child_node = RR_NULL_ENTITY;
    }
    if (rr_simulation_entity_alive(simulation, this->child_node))
    {
        struct rr_component_centipede *child_node =
            rr_simulation_get_centipede(simulation, this->child_node);
        child_node->parent_node = RR_NULL_ENTITY;
    }
#endif
}

#ifdef RR_SERVER
void rr_component_centipede_write(struct rr_component_centipede *this,
                                  struct proto_bug *encoder, int is_creation,
                                  struct rr_component_player_info *client)
{
}

#endif

#ifdef RR_CLIENT
void rr_component_centipede_read(struct rr_component_centipede *this,
                                 struct proto_bug *encoder)
{
}
#endif