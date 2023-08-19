#include <Server/Server.h>

#include <assert.h>
#include <math.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#include <libwebsockets.h>

#include <Server/Client.h>
#include <Server/EntityAllocation.h>
#include <Server/Logs.h>
#include <Server/Simulation.h>
#include <Server/UpdateProtocol.h>
#include <Server/Waves.h>
#include <Shared/Api.h>
#include <Shared/Binary.h>
#include <Shared/Bitset.h>
#include <Shared/Component/Physical.h>
#include <Shared/Crypto.h>
#include <Shared/Rivet.h>
#include <Shared/Utilities.h>
#include <Shared/Vector.h>
#include <Shared/cJSON.h>
#include <Shared/pb.h>

#ifndef NDEBUG
#define MESSAGE_BUFFER_SIZE (32 * 1024 * 1024)
#else
#define MESSAGE_BUFFER_SIZE (1024 * 1024)
#endif

static uint8_t lws_message_data[MESSAGE_BUFFER_SIZE];
static uint8_t *outgoing_message = lws_message_data + LWS_PRE;

// static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void rr_api_on_open_result(char *bin, void *captures)
{
    struct rr_api_account *account = captures;
    struct rr_binary_encoder decoder;
    rr_binary_encoder_init(&decoder, (uint8_t *) bin);
    account->username = malloc(50 * (sizeof (char)));
    rr_binary_encoder_read_nt_string(&decoder, account->username);
    account->xp = rr_binary_encoder_read_float64(&decoder);
    account->maximum_wave = rr_binary_encoder_read_varuint(&decoder);
    uint8_t id = rr_binary_encoder_read_uint8(&decoder);
    while (id)
    {
        uint32_t count = rr_binary_encoder_read_varuint(&decoder);
        uint8_t rarity = rr_binary_encoder_read_uint8(&decoder);
        account->petals[id][rarity] = count;
        id = rr_binary_encoder_read_uint8(&decoder);
    }
    /*
    cJSON *parsed = cJSON_Parse(json);
    if (parsed == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
            fprintf(stderr, "Error before: %s\n", error_ptr);
        return;
    }

    cJSON *max_wave = cJSON_GetObjectItemCaseSensitive(parsed, "maximum_wave");
    cJSON *xp = cJSON_GetObjectItemCaseSensitive(parsed, "xp");
    cJSON *petals = cJSON_GetObjectItemCaseSensitive(parsed, "petals");
    cJSON *already_playing =
        cJSON_GetObjectItemCaseSensitive(parsed, "already_playing");
    cJSON *username = cJSON_GetObjectItemCaseSensitive(parsed, "username");
    cJSON *password = cJSON_GetObjectItemCaseSensitive(parsed, "password");
    for (cJSON *petal_key = petals->child; petal_key != NULL;
         petal_key = petal_key->next)
    {
        char *key = petal_key->string;
        char *sub_key1 = strtok(key, ":");
        char *sub_key2 = strtok(NULL, ":");

        if (sub_key1 && sub_key2)
        {
            int index1 = atoi(sub_key1);
            int index2 = atoi(sub_key2);

            account->petals[index1][index2] = petal_key->valueint;
        }
    }
    account->xp = xp->valuedouble;
    account->already_playing = already_playing->valueint;
    account->username = strdup(username->valuestring);
    account->password = strdup(password->valuestring);
    account->maximum_wave = max_wave->valueint;
    cJSON_Delete(parsed);
    */
}

// loadout validation
void rr_api_on_get_petals(char *bin, void *_client)
{
    puts("attempting petal validation");
    struct rr_server_client *client = _client;
    uint32_t inventory[rr_petal_id_max][rr_rarity_id_max] = {0};
    struct rr_binary_encoder decoder;
    rr_binary_encoder_init(&decoder, (uint8_t *) bin);
    rr_binary_encoder_read_nt_string(&decoder, client->rivet_account.uuid);
    puts(client->rivet_account.uuid);
    if (strlen(client->rivet_account.uuid) < 30)
    {
        memset(&client->loadout[0], 0, sizeof client->loadout);
        client->level = 1;
        client->max_wave = 0;
        puts("id is invalid");
        return;
    }
    float xp = rr_binary_encoder_read_float64(&decoder);
    uint32_t next_level = 2;
    while (xp >= xp_to_reach_level(next_level))
    {
        xp -= xp_to_reach_level(next_level);
        ++next_level;
    }
    #define min(a,b) (((a) < (b)) ? (a) : (b))
    client->level = min(next_level - 1, 150);
    #undef min
    uint32_t max_wave = rr_binary_encoder_read_varuint(&decoder);
    if (max_wave > 30)
        max_wave = 30;
    client->max_wave = max_wave;
    printf("client is level %d %d\n", client->level, client->max_wave);
    uint8_t id = rr_binary_encoder_read_uint8(&decoder);
    while (id)
    {
        uint32_t count = rr_binary_encoder_read_varuint(&decoder);
        uint8_t rarity = rr_binary_encoder_read_uint8(&decoder);
        inventory[id][rarity] = count;
        id = rr_binary_encoder_read_uint8(&decoder);
    }
    for (uint8_t i = 0; i < 20; ++i)
    {
        uint8_t id = client->loadout[i].id;
        if (id != 0)
        {
            uint8_t rarity = client->loadout[i].rarity;
            if (inventory[id][rarity] > 0)
                --inventory[id][rarity];
            else
            {
                memset(&client->loadout[0], 0, sizeof client->loadout);
                client->level = 1;
                client->max_wave = 0;
                puts("petals are invalid");
                return;
            }
        }
    }
    puts("petals are valid");
/*
   puts("attempting petal validation");
    struct rr_server_client *client = _client;
    uint32_t inventory[rr_petal_id_max][rr_rarity_id_max];
    memset(&inventory[0], 0, sizeof inventory);

    cJSON *parsed = cJSON_Parse(json);
    if (parsed == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
            fprintf(stderr, "Error before: %s\n", error_ptr);
        return;
    }

    cJSON *max_wave = cJSON_GetObjectItemCaseSensitive(parsed, "maximum_wave");
    if (max_wave == NULL)
        client->max_wave = 0;
    else
        client->max_wave = max_wave->valueint;

    cJSON *experience = cJSON_GetObjectItemCaseSensitive(parsed, "xp");
    double xp = 0;
    if (experience != NULL)
        xp = experience->valuedouble;

    uint32_t next_level = 2;
    while (xp >= xp_to_reach_level(next_level))
    {
        xp -= xp_to_reach_level(next_level);
        ++next_level;
    }
    #define min(a,b) (((a) < (b)) ? (a) : (b))

    client->level = min(next_level - 1, 150);
    #undef min
    printf("client is registered as level %d\n", next_level - 1);

    cJSON *petals = cJSON_GetObjectItemCaseSensitive(parsed, "petals");
    if (petals == NULL || !cJSON_IsObject(petals))
    {
        fprintf(stderr, "petals is missing or is not an object\n");
        cJSON_Delete(parsed);
        return;
    }

    for (cJSON *petal_key = petals->child; petal_key != NULL;
         petal_key = petal_key->next)
    {
        char *key = petal_key->string;
        char *sub_key1 = strtok(key, ":");
        char *sub_key2 = strtok(NULL, ":");

        if (sub_key1 && sub_key2)
        {
            int index1 = atoi(sub_key1);
            int index2 = atoi(sub_key2);

            inventory[index1][index2] = petal_key->valueint;
        }
    }

    cJSON_Delete(parsed);
    for (uint8_t i = 0; i < 20; ++i)
    {
        uint8_t id = client->loadout[i].id;
        if (id != 0)
        {
            uint8_t rarity = client->loadout[i].rarity;
            if (inventory[id][rarity] > 0)
                --inventory[id][rarity];
            else
            {
                memset(&client->loadout[0], 0, sizeof client->loadout);
                puts("petals are invalid");
                return;
            }
        }
    }
    puts("petals are valid");
    */
}

static void rr_server_client_create_player_info(struct rr_server_client *this,
                                                uint8_t pos)
{
    puts("creating player info");
    this->player_info = rr_simulation_add_player_info(
        &this->server->simulation,
        rr_simulation_alloc_entity(&this->server->simulation));
    this->player_info->client = this;
    this->player_info->level = this->level;
    rr_component_player_info_set_client_id(this->player_info, pos);
    #define min(a,b) (((a) < (b)) ? (a) : (b))
    rr_component_player_info_set_slot_count(this->player_info, min(10, 5 + this->level / RR_LEVELS_PER_EXTRA_SLOT));
    #undef min
    struct rr_component_arena *arena =
        rr_simulation_get_arena(&this->server->simulation, 1);
    for (uint64_t i = 0; i < this->player_info->slot_count; ++i)
    {
        uint8_t id = this->loadout[i].id;
        uint8_t rarity = this->player_info->slots[i].rarity =
            this->loadout[i].rarity;
        this->player_info->slots[i].id = id;
        this->player_info->slots[i].count = RR_PETAL_DATA[id].count[rarity];

        id = this->loadout[i + 10].id;
        rarity = this->loadout[i + 10].rarity;
        this->player_info->secondary_slots[i].id = id;
        this->player_info->secondary_slots[i].rarity = rarity;
    }
}

void rr_server_client_free(struct rr_server_client *this)
{
    char petals_string[50000] = {0}; // Ensure this is large enough
    char buffer[1000] = {0};         // Temporary buffer for each item
    uint32_t wave = 0;
    if (this->player_info != NULL)
    {
        if (this->server->simulation_active)
        {
            uint8_t first = 1;
            wave = rr_simulation_get_arena(&this->server->simulation, 1)->wave;
            for (uint8_t id = 1; id < rr_petal_id_max; ++id)
                for (uint8_t rarity = 0; rarity < rr_rarity_id_max; ++rarity)
                {
                    if (this->player_info->collected_this_run[id * rr_rarity_id_max + rarity] == 0)
                        continue;
                    // Format each item into buffer
                    snprintf(buffer, sizeof buffer, "%u:%u:%lu", id, rarity, this->player_info->collected_this_run[id * rr_rarity_id_max + rarity]);

                    // If not the first item, append a comma before the item
                    if (!first)
                    {
                        strncat(petals_string, ",",
                                5000 - strlen(petals_string) - 1);
                    }
                    first = 0;

                    // Append the item
                    strncat(petals_string, buffer,
                            5000 - strlen(petals_string) - 1);
                }
        }
        if (petals_string[0] == 0)
            memcpy(petals_string, "1:0:0", sizeof "1:0:0");
        puts(petals_string);
        // if (1)
        // {
        rr_api_on_close(this->rivet_account.uuid, petals_string, wave, "1:0:0");
        // }
        // else
        // {
        //     char *malloc_string = malloc(sizeof petals_string);
        //     char *malloc_uuid = malloc(sizeof
        //     this->client->rivet_account.uuid); memcpy(malloc_string,
        //     &petals_string, sizeof petals_string); memcpy(malloc_uuid,
        //     &this->client->rivet_account.uuid, sizeof
        //     this->client->rivet_account.uuid); struct api_join_captures
        //     *captures = malloc(sizeof *captures); captures->rivet_uuid =
        //     malloc_uuid; captures->petals_string = malloc_string; pthread_t
        //     thread_id; int result = pthread_create(&thread_id, NULL,
        //     api_join, &captures); pthread_detach(thread_id);
        // }
        if (this->server->simulation_active)
        {
            if (this->player_info->flower_id != RR_NULL_ENTITY)
                rr_simulation_request_entity_deletion(
                    &this->server->simulation, this->player_info->flower_id);
            __rr_simulation_pending_deletion_free_components(
                this->player_info->parent_id, &this->server->simulation);
            __rr_simulation_pending_deletion_unset_entity(
                this->player_info->parent_id, &this->server->simulation);
            // rr_simulation_request_entity_deletion(&this->server->simulation,
            //                                       this->player_info->parent_id);
        }
    }
    puts("client disconnected");
}

void rr_server_client_encrypt_message(struct rr_server_client *this,
                                      uint8_t *start, uint64_t size)
{
    this->clientbound_encryption_key =
        rr_get_hash(this->clientbound_encryption_key);
    rr_encrypt(start, size, this->clientbound_encryption_key);
}

void rr_server_client_write_message(struct rr_server_client *this,
                                    uint8_t *data, uint64_t size)
{
//     struct __rr_client_message *msg = malloc(sizeof *msg);
//     msg->data = malloc(size + LWS_PRE);
//     memcpy(msg->data + LWS_PRE, data, size);
//     msg->size = size;
//     msg->next = this->messages;
    // this->messages = msg;

    // struct __rr_client_message *msg = &this->messages[this->messages_size++];
    // uint8_t *malloced = malloc(size * (sizeof(char)) + LWS_PRE);
    // memcpy(malloced + LWS_PRE, data, size);
    // msg->data = malloced;
    // msg->size = size;

    // if (this->messages_size > 90)
    // {
    //     fputs("client message list > 90\n", stderr);
    //     abort();
    // }

    // lws_callback_on_writable(this->socket_handle);
    lws_write(this->socket_handle, data, size, LWS_WRITE_BINARY);
}

void rr_server_client_broadcast_update(struct rr_server_client *this)
{
    struct rr_server *server = this->server;
    struct proto_bug encoder;
    proto_bug_init(&encoder, outgoing_message);
    proto_bug_write_uint8(&encoder, 0, "header");
    rr_simulation_write_binary(&server->simulation, &encoder,
                               this->player_info);
    rr_server_client_encrypt_message(this, encoder.start,
                                     encoder.current - encoder.start);
    rr_server_client_write_message(this, encoder.start,
                                   encoder.current - encoder.start);
}

void rr_server_client_tick(struct rr_server_client *this)
{
    if (!this->received_first_packet)
    {
        if (this->response_time != 0)
        {
            --this->response_time;
        }
    }
    if (this->server->simulation_active)
    {
        if (rr_simulation_has_entity(&this->server->simulation,
                                     this->player_info->flower_id))
        {
            struct rr_component_physical *physical = rr_simulation_get_physical(
                &this->server->simulation, this->player_info->flower_id);
            rr_vector_set(&physical->acceleration, this->player_accel_x,
                          this->player_accel_y);
        }
        rr_server_client_broadcast_update(this);
    }
    else
    {
        struct proto_bug encoder;
        proto_bug_init(&encoder, outgoing_message);
        proto_bug_write_uint8(&encoder, 69, "header");
        proto_bug_write_uint8(
            &encoder, this->server->ticks_until_simulation_create, "countdown");
        uint8_t pos = 0;
        for (uint32_t i = 0; i < RR_SQUAD_MEMBER_COUNT; ++i)
        {
            struct rr_server_client *curr_client = &this->server->clients[i];
            if (curr_client == this)
                pos = i;
            proto_bug_write_uint8(
                &encoder,
                rr_bitset_get(&this->server->clients_in_use[0], i) &&
                    curr_client->verified,
                "bitbit");
            proto_bug_write_uint8(&encoder, curr_client->ready, "ready");
            proto_bug_write_varuint(&encoder,
                                    curr_client->requested_start_wave_percent *
                                            curr_client->max_wave +
                                        1,
                                    "requested start wave");
            uint32_t nick_len = strlen(&curr_client->client_nickname[0]);
            proto_bug_write_varuint(&encoder, nick_len, "nick size");
            proto_bug_write_string(&encoder, &curr_client->client_nickname[0],
                                   nick_len, "nick");
            for (uint8_t j = 0; j < 20; ++j)
            {
                proto_bug_write_uint8(&encoder, curr_client->loadout[j].id,
                                      "id");
                proto_bug_write_uint8(&encoder, curr_client->loadout[j].rarity,
                                      "rar");
            }
        }
        proto_bug_write_uint8(&encoder, pos, "sqpos");
        proto_bug_write_uint8(&encoder, this->server->private, "private");
        rr_server_client_encrypt_message(this, encoder.start,
                                         encoder.current - encoder.start);
        rr_server_client_write_message(this, encoder.start,
                                       encoder.current - encoder.start);
    }
}

static void delete_entity_function(EntityIdx entity, void *_captures)
{
    if (rr_simulation_has_entity(_captures, entity))
        rr_simulation_request_entity_deletion(_captures, entity);
}

void rr_server_init(struct rr_server *this)
{
    printf("server size: %lu\n", sizeof *this);
    memset(this, 0, sizeof *this);
    this->countdown_ticks = 25 * 240;
    rr_static_data_init();
}

void rr_server_free(struct rr_server *this)
{
    lws_context_destroy(this->server);
}

static void rr_simulation_tick_entity_resetter_function(EntityIdx entity,
                                                        void *captures)
{
    struct rr_simulation *this = captures;
#define XX(COMPONENT, ID)                                                      \
    if (rr_simulation_has_##COMPONENT(this, entity))                           \
        rr_simulation_get_##COMPONENT(this, entity)->protocol_state = 0;
    RR_FOR_EACH_COMPONENT
#undef XX
}

void rr_server_tick(struct rr_server *this)
{
    if (this->simulation_active)
        rr_simulation_tick(&this->simulation);

    uint8_t client_count = 0;
    for (uint64_t i = 0; i < RR_MAX_CLIENT_COUNT; i++)
        if (rr_bitset_get(this->clients_in_use, i) && this->clients[i].verified)
        {
            rr_server_client_tick(this->clients + i);
            ++client_count;
        }

    if (this->simulation_active)
    {
        if (!client_count)
        {
            this->simulation_active = 0;
#ifdef RIVET_BUILD
            exit(0);
#endif
            free(this->simulation.grid);
            rr_simulation_init(&this->simulation);
        }
        else
        {
            rr_simulation_for_each_entity(
                &this->simulation, &this->simulation,
                rr_simulation_tick_entity_resetter_function);
        }
    }
    else
    {
        uint8_t all_ready = 1;
        uint8_t has_client = 0;
        for (uint64_t i = 0; i < RR_MAX_CLIENT_COUNT; i++)
            if (rr_bitset_get(this->clients_in_use, i))
            {
                all_ready &= (this->clients[i].ready & 1);
                has_client = 1;
            }
        if (!has_client)
            this->countdown_ticks = 25 * 240;
        if (this->countdown_ticks > 0)
            --this->countdown_ticks;
        else
            all_ready = 1;

        if (client_count && all_ready)
        {
            if (--this->ticks_until_simulation_create == 0)
            {
                this->simulation_active = 1;
                rr_simulation_init(&this->simulation);
#ifdef RIVET_BUILD
                // players cannot join in the middle of a game (simulation)
                char *lobby_token = getenv("RIVET_LOBBY_TOKEN");
                rr_rivet_lobbies_set_closed(lobby_token, 1);
#endif
                float start_wave_total = 0;
                uint64_t client_count = 0;

                for (uint64_t i = 0; i < RR_MAX_CLIENT_COUNT; i++)
                    if (rr_bitset_get(this->clients_in_use, i))
                    {
                        rr_api_get_petals(
                            &this->clients[i].rivet_account.uuid[0],
                            RR_API_SECRET, &this->clients[i]);
                        rr_server_client_create_player_info(this->clients + i,
                                                            i);
                        rr_server_client_create_flower(this->clients + i);
                        client_count++;

                        start_wave_total +=
                            this->clients[i].requested_start_wave_percent *
                            this->clients[i].max_wave;
                    }
                float start_wave_mean = start_wave_total / client_count;
                struct rr_component_arena *arena =
                    rr_simulation_get_arena(&this->simulation, 1);
                rr_component_arena_set_wave(arena,
                                            (uint32_t)(start_wave_mean + 1));
                this->simulation.wave_points =
                    get_points_from_wave(arena->wave, client_count);
            }
        }
        else
            this->ticks_until_simulation_create =
#ifdef RIVET_BUILD
                125;
#else
                2;
#endif
    }
}

static int handle_lws_event(struct rr_server *this, struct lws *ws,
                            enum lws_callback_reasons reason, uint8_t *packet,
                            size_t size)
{
    switch (reason)
    {
    case LWS_CALLBACK_ESTABLISHED:
    {
        if (this->simulation_active)
        {
            lws_close_reason(ws, LWS_CLOSE_STATUS_GOINGAWAY,
                             (uint8_t *)"simulation active",
                             sizeof "simulation active" - 1);
            return -1;
        }
        for (uint64_t i = 0; i < RR_MAX_CLIENT_COUNT; i++)
            if (!rr_bitset_get_bit(this->clients_in_use, i))
            {
                rr_bitset_set(this->clients_in_use, i);
                rr_server_client_init(this->clients + i);
                this->clients[i].server = this;
                this->clients[i].file_descriptor = lws_get_socket_fd(ws);
                this->clients[i].socket_handle = ws;
                // send encryption key
                struct proto_bug encryption_key_encoder;
                proto_bug_init(&encryption_key_encoder, outgoing_message);
                proto_bug_write_uint64(&encryption_key_encoder,
                                       this->clients[i].requested_verification,
                                       "verification");
                proto_bug_write_uint32(&encryption_key_encoder, rr_get_rand(),
                                       "useless bytes");
                proto_bug_write_uint64(
                    &encryption_key_encoder,
                    this->clients[i].clientbound_encryption_key,
                    "c encryption key");
                proto_bug_write_uint64(
                    &encryption_key_encoder,
                    this->clients[i].serverbound_encryption_key,
                    "s encryption key");
                rr_encrypt(outgoing_message, 1024, 21094093777837637ull);
                rr_encrypt(outgoing_message, 8, 1);
                rr_encrypt(outgoing_message, 1024, 59731158950470853ull);
                rr_encrypt(outgoing_message, 1024, 64709235936361169ull);
                rr_encrypt(outgoing_message, 1024, 59013169977270713ull);
                rr_server_client_write_message(this->clients + i,
                                               outgoing_message, 1024);
                return 0;
            }

        lws_close_reason(ws, LWS_CLOSE_STATUS_GOINGAWAY,
                         (uint8_t *)"too many active clients",
                         sizeof "to many active clients" - 1);
        return -1;
    }
    case LWS_CALLBACK_CLOSED:
    {
        int file_descriptor = lws_get_socket_fd(ws);
        for (uint64_t i = 0; i < RR_MAX_CLIENT_COUNT; i++)
            if (rr_bitset_get(this->clients_in_use, i))
            {
                if (this->clients[i].file_descriptor == file_descriptor)
                {
                    rr_bitset_unset(this->clients_in_use, i);
#ifdef RIVET_BUILD
                    rr_rivet_players_disconnected(
                        getenv("RIVET_LOBBY_TOKEN"),
                        this->clients[i].rivet_account.token);
#endif
                    rr_server_client_free(this->clients + i);
                    char log[100] = {"ip: `"};
                    strcat(log, this->clients[i].ip_address);
                    strcat(log, "`");
                    // rr_discord_webhook_log("player status", "client
                    // disconnected", log, 0xff4444);
                    return 0;
                }
            }
        puts("client joined but instakicked");
        // RR_UNREACHABLE("couldn't remove client");
        break;
    }
    case LWS_CALLBACK_SERVER_WRITEABLE:
    {
        uint64_t i = 0;
        for (; i < RR_MAX_CLIENT_COUNT; i++)
        {
            if (!rr_bitset_get(this->clients_in_use, i))
                continue;
            if (this->clients[i].file_descriptor == lws_get_socket_fd(ws))
            {
                // struct rr_server_client *client = this->clients + i;
                // for (uint64_t j = 0; j < client->messages_size; j++)
                // {
                //     struct __rr_client_message *msg = &client->messages[j];
                //     int a =
                //         lws_write(client->socket_handle, msg->data + LWS_PRE,
                //                   msg->size, LWS_WRITE_BINARY);
                //     free(msg->data);
                // }
                // client->messages_size = 0;
                // struct __rr_client_message *msg = client->messages;
                // while (msg) {
                //     struct __rr_client_message *next_msg = msg->next;
                //     lws_write(client->socket_handle, msg->data + LWS_PRE, msg->size, LWS_WRITE_BINARY);
                //     free(msg->data);
                //     free(msg);
                //     msg = next_msg;
                // }
                // client->messages = NULL;
            }
        }
        break;
    }
    case LWS_CALLBACK_RECEIVE:
    {
        if (size == 0)
            break;
        struct rr_server_client *client = NULL;
        uint64_t i = 0;
        for (; i < RR_MAX_CLIENT_COUNT; i++)
        {
            if (!rr_bitset_get(this->clients_in_use, i))
                continue;
            if (this->clients[i].file_descriptor == lws_get_socket_fd(ws))
            {
                client = &this->clients[i];
                break;
            }
        }
        if (client == NULL)
        {
            puts("null client????");
            return 0;
        }

        rr_decrypt(packet, size, client->serverbound_encryption_key);
        client->serverbound_encryption_key =
            rr_get_hash(rr_get_hash(client->serverbound_encryption_key));

        struct proto_bug encoder;
        proto_bug_init(&encoder, packet);

        if (!client->received_first_packet)
        {
            client->received_first_packet = 1;
            if (size < 16)
            {
                fputs("invlid size\n", stderr);
                lws_close_reason(ws, LWS_CLOSE_STATUS_GOINGAWAY,
                                 (uint8_t *)"invalid size",
                                 sizeof "invalid size");
                return -1;
            }

            proto_bug_read_uint64(&encoder, "useless bytes");
            uint64_t received_verification =
                proto_bug_read_uint64(&encoder, "verification");
            if (received_verification != client->requested_verification)
            {
                fputs("invalid verification\n", stderr);
                lws_close_reason(ws, LWS_CLOSE_STATUS_GOINGAWAY,
                                 (uint8_t *)"invalid v", sizeof "invalid v");
                return -1;
            }

            uint64_t encountered_size =
                proto_bug_read_varuint(&encoder, "rivet token size");
            uint64_t uuid_encountered_size =
                proto_bug_read_varuint(&encoder, "uuid size");
            if (encountered_size > 250 || uuid_encountered_size > 95)
            {
                printf("%lu %lu\n", size,
                       encountered_size + uuid_encountered_size);
                fputs("invalid size3\n", stderr);
                lws_close_reason(ws, LWS_CLOSE_STATUS_GOINGAWAY,
                                 (uint8_t *)"invalid size3",
                                 sizeof "invalid size3");
                return -1;
            }
            if (16 + encountered_size + uuid_encountered_size >= size)
            {
                printf("%lu %lu\n", size,
                       encountered_size + uuid_encountered_size);
                fputs("invalid size2\n", stderr);
                lws_close_reason(ws, LWS_CLOSE_STATUS_GOINGAWAY,
                                 (uint8_t *)"invalid size2",
                                 sizeof "invalid size2");
                return -1;
            }

            memset(&client->rivet_account, 0,
                   sizeof(struct rr_rivet_account));
            // Read rivet token
            client->rivet_account.token[encountered_size] = 0;
            proto_bug_read_string(&encoder,
                                  client->rivet_account.token,
                                  encountered_size, "rivet token");
            // Read uuid
            client->rivet_account.uuid[uuid_encountered_size] = 0;
            proto_bug_read_string(&encoder, client->rivet_account.uuid,
                                  uuid_encountered_size, "rivet uuid");
            puts(client->rivet_account.uuid);

            for (uint32_t j = 0; j < RR_MAX_CLIENT_COUNT; ++j)
            {
                if (!rr_bitset_get(this->clients_in_use, j))
                    continue;
                if (&this->clients[j] == client)
                    continue;
                if (strcmp(client->rivet_account.uuid, this->clients[j].rivet_account.uuid) == 0)
                {
                    fputs("skid multibox\n", stderr);
                    lws_close_reason(ws, LWS_CLOSE_STATUS_GOINGAWAY,
                                        (uint8_t *)"skid multibox",
                                        sizeof "skid multibox");
                    return -1;
                }
            }
            uint64_t dev_flag = proto_bug_read_varuint(&encoder, "dev flag");
            if (dev_flag == 494538643243)
                client->ready |= 2;

#ifdef RIVET_BUILD
            printf("client connecting with token: %s\n",
                    client->rivet_account.token);
            if (!rr_rivet_players_connected(
                    getenv("RIVET_LOBBY_TOKEN"),
                    client->rivet_account.token))
            {
                fputs("rivet error\n", stderr);
                lws_close_reason(ws, LWS_CLOSE_STATUS_GOINGAWAY,
                                (uint8_t *)"rivet error",
                                sizeof "rivet error");
                return -1;
            }
#endif
            struct rr_api_account account = {0};
            rr_api_on_open(client->rivet_account.uuid, &account);

            printf("%u\n", account.already_playing);

            if (0 && account.already_playing)
            {
                fputs("already playing\n", stderr);
                lws_close_reason(ws, LWS_CLOSE_STATUS_GOINGAWAY,
                                 (uint8_t *)"already playing",
                                 sizeof "already playing");
                return -1;
            }
            client->max_wave = account.maximum_wave;

            puts("socket verified");
            client->verified = 1;

            return 0;
        }
        switch (proto_bug_read_uint8(&encoder, "header"))
        {
        case 0:
        {
            if (size < 9)
            {
                puts("unsafe input packet with small length");
                return 0;
            }
            if (client->player_info == NULL)
                break;
            if (client->player_info->flower_id == 0)
                break;
            proto_bug_read_uint8(&encoder, "movement type");
            uint64_t movementFlags =
                proto_bug_read_uint8(&encoder, "movement kb flags");
            float x = 0;
            float y = 0;

            if ((movementFlags & 64) == 0)
            {
                if (movementFlags & 1)
                    y--;
                if (movementFlags & 2)
                    x--;
                if (movementFlags & 4)
                    y++;
                if (movementFlags & 8)
                    x++;
                if ((x != 0 || y != 0) && x == x && y == y &&
                    fabsf(x) < 10000 && fabsf(y) < 10000)
                {
                    float mag_1 = 2.5 / sqrtf(x * x + y * y);
                    client->player_accel_x = x * mag_1;
                    client->player_accel_y = y * mag_1;
                }
                else
                {
                    client->player_accel_x = 0;
                    client->player_accel_y = 0;
                }
            }
            else
            {
                if (size < 9)
                {
                    return 0;
                }
                x = proto_bug_read_float32(&encoder, "mouse x");
                y = proto_bug_read_float32(&encoder, "mouse y");
                if ((x != 0 || y != 0) && x == x && y == y &&
                    fabsf(x) < 10000 && fabsf(y) < 10000)
                {
                    float mag_1 = sqrtf(x * x + y * y);
                    float scale = (mag_1 - 25) / 50;
                    if (scale > 1)
                        scale = 1;
                    else if (scale < 0)
                        scale = 0;
                    client->player_accel_x = x / mag_1 * scale * 2.5;
                    client->player_accel_y = y / mag_1 * scale * 2.5;
                }
                else
                {
                    client->player_accel_x = 0;
                    client->player_accel_y = 0;
                }
            }
            client->player_info->input = (movementFlags >> 4) & 3;
            break;
        }
        case 2:
        {
            if (size < 2)
            {
                puts("someone sent a petal switch packet with size < 2");
                return 0;
            }
            else if (size > 70)
            {
                puts("someone sent a petal switch packet with size > 70");
                return 0;
            }
            if (client->player_info->flower_id == RR_NULL_ENTITY)
                return 0;
            uint8_t pos = proto_bug_read_uint8(&encoder, "petal switch");
            while (pos != 0 && pos <= 10 &&
                   encoder.current - encoder.start <= size)
            {
                rr_component_player_info_petal_swap(client->player_info,
                                                    &this->simulation, pos - 1);
                pos = proto_bug_read_uint8(&encoder, "petal switch");
            }
            break;
        }
        case 3:
        {
#ifndef RIVET_BUILD
            if (size < 2)
                return 0;
            puts("cheat used");
            uint8_t cheat_type = proto_bug_read_uint8(&encoder, "cheat type");
            if (cheat_type == 1)
            {
                // increment
                struct rr_component_arena *arena =
                    rr_simulation_get_arena(&this->simulation, 1);
                rr_component_arena_set_wave_tick(arena, 0);
                rr_component_arena_set_wave(arena, arena->wave + 1);
                this->simulation.wave_points =
                    get_points_from_wave(arena->wave, 1);
                rr_simulation_for_each_mob(&this->simulation, &this->simulation,
                                           delete_entity_function);
                rr_simulation_for_each_drop(&this->simulation,
                                            &this->simulation,
                                            delete_entity_function);
                rr_simulation_for_each_petal(&this->simulation,
                                             &this->simulation,
                                             delete_entity_function);
            }
            if (cheat_type == 2)
            {
                // decrement
                struct rr_component_arena *arena =
                    rr_simulation_get_arena(&this->simulation, 1);
                rr_component_arena_set_wave_tick(arena, 0);
                rr_component_arena_set_wave(arena, arena->wave - 1);
                rr_simulation_for_each_mob(&this->simulation, &this->simulation,
                                           delete_entity_function);
                rr_simulation_for_each_drop(&this->simulation,
                                            &this->simulation,
                                            delete_entity_function);
                rr_simulation_for_each_petal(&this->simulation,
                                             &this->simulation,
                                             delete_entity_function);
            }
            if (cheat_type == 3)
            {
            }
#endif
            break;
        }
        case 69:
        {
            client->ready ^= 1;
            break;
        }
        case 70:
        {
            float requested_start_wave =
                proto_bug_read_float32(&encoder, "requested wave");
            if (!(requested_start_wave <= 0.75 && requested_start_wave >= 0))
                break;
            client->requested_start_wave_percent = requested_start_wave;

            uint8_t loadout_count =
                proto_bug_read_uint8(&encoder, "loadout count");

            if (loadout_count > 10)
                break;

            for (uint8_t i = 0; i < loadout_count; i++)
            {
                uint8_t id = proto_bug_read_uint8(&encoder, "id");
                uint8_t rarity = proto_bug_read_uint8(&encoder, "rarity");
                if (id >= rr_petal_id_max)
                    break;
                if (rarity >= rr_rarity_id_max)
                    break;
                client->loadout[i].rarity = rarity;
                client->loadout[i].id = id;
                id = proto_bug_read_uint8(&encoder, "id");
                rarity = proto_bug_read_uint8(&encoder, "rarity");
                if (id >= rr_petal_id_max)
                    break;
                if (rarity >= rr_rarity_id_max)
                    break;
                client->loadout[i + 10].rarity = rarity;
                client->loadout[i + 10].id = id;
            }

            break;
        }
        case 71:
        {
            uint64_t nickname_size =
                proto_bug_read_varuint(&encoder, "nick length");

            if (nickname_size > 16)
            {
                puts("nick too long");
                return 0;
            }

            memset(&client->client_nickname, 0,
                   sizeof(client->client_nickname));

            client->client_nickname[nickname_size] =
                0; // don't forget the null terminator lol
            proto_bug_read_string(&encoder, client->client_nickname,
                                  nickname_size, "nick");
            break;
        }
        case 72:
        {
            if (i == 0 && !this->simulation_active)
            {
                this->private = proto_bug_read_uint8(&encoder, "private") != 0;
#ifdef RIVET_BUILD
                // players cannot join in the middle of a game (simulation)
                char *lobby_token = getenv("RIVET_LOBBY_TOKEN");
                rr_rivet_lobbies_set_closed(lobby_token, this->private);
#else
                printf("setting to %d\n", this->private);
#endif
            }
            break;
        }
        default:
            break;
        }
        return 0;
    }
    default:
        return 0;
    }

    return 0;
}

static int lws_callback(struct lws *ws, enum lws_callback_reasons reason,
                        void *user, void *packet, size_t size)
{
    switch (reason)
    {
    case LWS_CALLBACK_ESTABLISHED:
    case LWS_CALLBACK_SERVER_WRITEABLE:
    case LWS_CALLBACK_RECEIVE:
    case LWS_CALLBACK_CLOSED:
        break;
    default:
        return 0;
    }
    // assert(pthread_mutex_lock(&mutex) == 0);

    struct rr_server *this =
        (struct rr_server *)lws_context_user(lws_get_context(ws));
    int close = handle_lws_event(this, ws, reason, packet, size);
    if (close)
        return close;
    // assert(pthread_mutex_unlock(&mutex) == 0);
    return 0;
}

void *thread_func(void *arg)
{
    struct rr_server *this = (struct rr_server *)arg;
    while (1)
    {
        lws_service(this->server, 0);
    }
    return 0;
}

static void lws_log(int level, char const *log) { printf("%d %s", level, log); }

void rr_server_run(struct rr_server *this)
{
    struct lws_context_creation_info info;
    memset(&info, 0, sizeof(info));

    info.protocols = (struct lws_protocols[]){
        {"g", lws_callback, sizeof(uint8_t), MESSAGE_BUFFER_SIZE, 0, NULL, 0},
        {0}};

    info.port = 1234;
    info.user = this;
    info.pt_serv_buf_size = MESSAGE_BUFFER_SIZE;
    lws_set_log_level(0, lws_log);

    this->server = lws_create_context(&info);
    assert(this->server);

    // pthread_t service_thread;
    // int ret = pthread_create(&service_thread, NULL, thread_func, this);
    // if (ret != 0)
    // {
    //     perror("Error creating service thread");
    //     return;
    // }

    // pthread_detach(service_thread);

    this->ticks_until_simulation_create =
#ifdef RIVET_BUILD
        125;
#else
        24;
#endif
    while (1)
    {
        struct timeval start;
        struct timeval end;

        gettimeofday(&start,
                     NULL); // gettimeofday actually starts from unix
                            // timestamp 0 (goofy)
        lws_service(this->server, -1);
        rr_server_tick(this);
        gettimeofday(&end, NULL);

        uint64_t elapsed_time = (end.tv_sec - start.tv_sec) * 1000000 +
                                (end.tv_usec - start.tv_usec);
        //if (elapsed_time > 1000)
            //fprintf(stderr, "tick took %lu microseconds\n", elapsed_time);
        int64_t to_sleep = 40000 - elapsed_time;
        if (to_sleep > 0)
            usleep(to_sleep);
    }
}
