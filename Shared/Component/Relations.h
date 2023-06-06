#pragma once

#include <Shared/Component/Common.h>
#include <Shared/Entity.h>
#include <Shared/Utilities.h>

struct rr_simulation;
struct proto_bug;
RR_CLIENT_ONLY(struct rr_renderer;)

struct rr_component_relations
{
                   EntityIdx parent_id;
                   EntityIdx owner;
                   uint32_t team;
    RR_SERVER_ONLY(EntityIdx root_owner;)
    RR_SERVER_ONLY(uint32_t protocol_state;)
};

void rr_component_relations_init(struct rr_component_relations *, struct rr_simulation *);
void rr_component_relations_free(struct rr_component_relations *, struct rr_simulation *);

RR_SERVER_ONLY(void rr_component_relations_update_root_owner(struct rr_simulation *, struct rr_component_relations *);)

RR_SERVER_ONLY(void rr_component_relations_write(struct rr_component_relations *, struct proto_bug *, int);)
RR_CLIENT_ONLY(void rr_component_relations_read(struct rr_component_relations *, struct proto_bug *);)

RR_DECLARE_PUBLIC_FIELD(relations, EntityIdx, owner)
RR_DECLARE_PUBLIC_FIELD(relations, uint32_t, team)