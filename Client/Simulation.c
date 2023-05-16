#include <Client/Simulation.h>

#include <assert.h>
#include <string.h>
#include <stdio.h>

#include <Shared/Bitset.h>

void rr_simulation_enitty_create_with_id(struct rr_simulation *this, EntityIdx entity)
{
    rr_bitset_set(this->entity_tracker, entity);
}
