#include <Shared/Component/PlayerInfo.h>

#include <stdlib.h>
#include <string.h>

#ifdef RR_SERVER
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

#include <Server/Client.h>
#endif
#include <Shared/Api.h>
#include <Shared/Component/Health.h>
#include <Shared/Rivet.h>
#include <Shared/SimulationCommon.h>
#include <Shared/StaticData.h>
#include <Shared/pb.h>

#define FOR_EACH_PUBLIC_FIELD                                                  \
    X(camera_y, float32)                                                       \
    X(camera_fov, float32)                                                     \
    X(flower_id, varuint)                                                      \
    X(camera_x, float32)                                                       \
    X(slot_count, varuint)                                                     \
    X(client_id, uint8)

enum
{
    state_flags_client_id = 0b0000001,
    state_flags_camera_y = 0b0000010,
    state_flags_camera_fov = 0b0000100,
    state_flags_flower_id = 0b0001000,
    state_flags_camera_x = 0b0010000,
    state_flags_slot_count = 0b0100000,
    state_flags_petals = 0b1000000,
    state_flags_all = 0b1111111
};

#ifdef RR_SERVER
struct api_join_captures
{
    char const *rivet_uuid;
    char *petals_string;
};

void *api_join(void *_captures)
{
    struct api_join_captures *captures = _captures;
    rr_api_merge_petals(captures->rivet_uuid, captures->petals_string);
    puts("api join thread end");
    return NULL;
}

void *sleeper(void *arg)
{
    usleep(10000000);
    return NULL;
}
#endif

void rr_component_player_info_init(struct rr_component_player_info *this,
                                   struct rr_simulation *simulation)
{
    memset(this, 0, sizeof *this);
    this->camera_fov = 0.9f;
    RR_SERVER_ONLY(this->modifiers.drop_pickup_radius = 25;)
}

void rr_component_player_info_free(struct rr_component_player_info *this,
                                   struct rr_simulation *simulation)
{
#ifdef RR_SERVER
    char petals_string[5000] = {0}; // Ensure this is large enough
    char buffer[100] = {0};         // Temporary buffer for each item

    for (struct rr_drop_picked_up *i = this->collected_this_run;
         i < this->collected_this_run_end; i++)
    {
        // Format each item into buffer
        snprintf(buffer, sizeof buffer, "%u:%u:%lu", i->id, i->rarity,
                 i->count);

        // If not the first item, append a comma before the item
        if (i != this->collected_this_run)
        {
            strncat(petals_string, ",",
                    5000 - strlen(petals_string) - 1);
        }

        // Append the item
        strncat(petals_string, buffer,
                5000 - strlen(petals_string) - 1);
    }
    puts("api join start");
    if (1)
    {
        rr_api_merge_petals(this->client->rivet_account.uuid, petals_string);
    }
    else
    {
        /*
        struct api_join_captures captures;
        captures.rivet_uuid = this->client->rivet_account.uuid;
        captures.petals_string = petals_string;
=======
        char *malloc_string = malloc(sizeof petals_string);
        char *malloc_uuid = malloc(sizeof this->client->rivet_account.uuid);
        memcpy(malloc_string, &petals_string, sizeof petals_string);
        memcpy(malloc_uuid, &this->client->rivet_account.uuid, sizeof this->client->rivet_account.uuid);
        struct api_join_captures *captures = malloc(sizeof *captures);
        captures->rivet_uuid = malloc_uuid;
        captures->petals_string = malloc_string;
>>>>>>> e52dac9bf67d3b6db5440698b48194adb5e76a8f
        pthread_t thread_id;
        int result = pthread_create(&thread_id, NULL, api_join, &captures);
        pthread_detach(thread_id);
        */
    }

    if (this->flower_id != RR_NULL_ENTITY)
        rr_component_health_set_health(
            rr_simulation_get_health(simulation, this->flower_id), 0);
    free(this->collected_this_run);
#endif
}

#ifdef RR_SERVER
void rr_component_player_info_set_slot_cd(struct rr_component_player_info *this,
                                          uint8_t pos, uint8_t cd)
{
    this->protocol_state |=
        (this->slots[pos].client_cooldown != cd) * state_flags_petals;
    this->slots[pos].client_cooldown = cd;
}

void rr_component_player_info_petal_swap(struct rr_component_player_info *this,
                                         struct rr_simulation *simulation,
                                         uint8_t pos)
{
    struct rr_component_player_info_petal_slot *slot = &this->slots[pos];
    struct rr_component_player_info_petal_slot *s_slot =
        &this->secondary_slots[pos];
    for (uint32_t i = 0; i < slot->count; ++i)
    {
        EntityIdx id = slot->petals[i].simulation_id;
        if (id != RR_NULL_ENTITY && rr_simulation_has_entity(simulation, id))
        {
            rr_simulation_request_entity_deletion(simulation, id);

            slot->petals[i].simulation_id = RR_NULL_ENTITY;
        }
    }
    uint8_t temp = slot->id;
    slot->id = s_slot->id;
    s_slot->id = temp;
    temp = slot->rarity;
    slot->rarity = s_slot->rarity;
    s_slot->rarity = temp;

    slot->count = RR_PETAL_DATA[slot->id].count[slot->rarity];
    for (uint32_t i = 0; i < slot->count; ++i)
        slot->petals[i].cooldown_ticks = RR_PETAL_DATA[slot->id].cooldown + 25;
    this->protocol_state |= state_flags_petals;
}

void rr_component_player_info_write(struct rr_component_player_info *this,
                                    struct proto_bug *encoder, int is_creation)
{
    uint64_t state = this->protocol_state | (state_flags_all * is_creation);
    proto_bug_write_varuint(encoder, state, "player_info component state");
#define X(NAME, TYPE) RR_ENCODE_PUBLIC_FIELD(NAME, TYPE);
    FOR_EACH_PUBLIC_FIELD
#undef X
    if (state & state_flags_petals)
    {
        for (uint32_t i = 0; i < this->slot_count; ++i)
        {
            proto_bug_write_uint8(encoder, this->slots[i].id, "p_id");
            proto_bug_write_uint8(encoder, this->slots[i].rarity, "p_rar");
            proto_bug_write_uint8(encoder, this->slots[i].client_cooldown,
                                  "p_ccd");

            proto_bug_write_uint8(encoder, this->secondary_slots[i].id, "p_id");
            proto_bug_write_uint8(encoder, this->secondary_slots[i].rarity,
                                  "p_rar");
        }
    }
}

RR_DEFINE_PUBLIC_FIELD(player_info, float, camera_x)
RR_DEFINE_PUBLIC_FIELD(player_info, float, camera_y)
RR_DEFINE_PUBLIC_FIELD(player_info, float, camera_fov)
RR_DEFINE_PUBLIC_FIELD(player_info, uint32_t, slot_count)
RR_DEFINE_PUBLIC_FIELD(player_info, EntityIdx, flower_id);
RR_DEFINE_PUBLIC_FIELD(player_info, uint8_t, client_id);
#endif

#ifdef RR_CLIENT
void rr_component_player_info_read(struct rr_component_player_info *this,
                                   struct proto_bug *encoder)
{
    uint64_t state =
        proto_bug_read_varuint(encoder, "player_info component state");
#define X(NAME, TYPE) RR_DECODE_PUBLIC_FIELD(NAME, TYPE);
    FOR_EACH_PUBLIC_FIELD
#undef X
    if (state & state_flags_petals)
    {
        for (uint32_t i = 0; i < this->slot_count; ++i)
        {
            this->slots[i].id = proto_bug_read_uint8(encoder, "p_id");
            this->slots[i].rarity = proto_bug_read_uint8(encoder, "p_rar");
            this->slots[i].client_cooldown =
                proto_bug_read_uint8(encoder, "p_ccd");

            this->secondary_slots[i].id = proto_bug_read_uint8(encoder, "p_id");
            this->secondary_slots[i].rarity =
                proto_bug_read_uint8(encoder, "p_rar");
        }
    }
}
#endif
