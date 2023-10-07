#include <Client/Storage.h>

#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

#include <Client/Game.h>
#include <Shared/Binary.h>

char storage_buf1[8 * 1024] = {0};
char storage_buf2[8 * 1024] = {0};

uint32_t rr_local_storage_get_string(char *name)
{
#ifdef EMSCRIPTEN
    return EM_ASM_INT(
        {
            let string = Module.ReadCstr($0);
            if (!window.localStorage[string])
                return 0;
            string = new TextEncoder().encode(window.localStorage[string]);
            HEAPU8.set(string, $1);
            return string.length;
        },
        name, storage_buf1);
#endif

    return 0;
}

void rr_local_storage_store_string(char *name, char *contents)
{
#ifdef EMSCRIPTEN
    EM_ASM(
        {
            const string = Module.ReadCstr($0);
            const string2 = Module.ReadCstr($1);
            window.localStorage[string] = string2;
        },
        name, contents);
#endif
}

void rr_local_storage_store_bytes(char *label, void const *bytes, uint64_t size)
{
    int new_size = rr_base_64_encode(storage_buf1, bytes, size);
#ifdef EMSCRIPTEN
    EM_ASM(
        {
            const string = Module.ReadCstr($0);
            const bytes = new TextDecoder().decode(HEAPU8.subarray($1, $1 + $2 - 1));

            window.localStorage[string] = bytes;
        },
        label, storage_buf1, new_size);
#endif
}

uint32_t rr_local_storage_get_bytes(char *label, void *bytes)
{
#ifdef EMSCRIPTEN
    int len = EM_ASM_INT(
        {
            const string = Module.ReadCstr($0);
            let bytes = window.localStorage[string];
            if (!bytes)
                return 0;
            HEAPU8.set(new TextEncoder().encode(bytes), $1);
            return bytes.length;
        },
        label, storage_buf1);
    return rr_base_64_decode(bytes, storage_buf1);
#endif
    return 0;
}

#define STORE_ID_RARITY(encoder, start, id_count, rarity_count) \
{ \
    for (uint8_t id = 0; id < id_count; ++id) \
    { \
        for (uint8_t rarity = 0; rarity < rarity_count; ++rarity) \
        { \
            if (start[id][rarity] == 0) \
                continue; \
            rr_binary_encoder_write_uint8(encoder, id + 1); \
            rr_binary_encoder_write_uint8(encoder, rarity); \
            rr_binary_encoder_write_varuint(encoder, start[id][rarity]); \
        } \
    } \
    rr_binary_encoder_write_uint8(encoder, 0); \
}

#define STORE_LOADOUT \
{ \
    for (uint32_t n = 0; n < 20; ++n) \
    { \
        if (this->cache.loadout[n].id == 0) \
            continue; \
        rr_binary_encoder_write_uint8(&encoder, n + 1); \
        rr_binary_encoder_write_uint8(&encoder, this->cache.loadout[n].id); \
        rr_binary_encoder_write_uint8(&encoder, this->cache.loadout[n].rarity); \
    } \
    rr_binary_encoder_write_uint8(&encoder, 0); \
}

#define READ_LOADOUT \
{ \
    uint8_t pos = rr_binary_encoder_read_uint8(&decoder); \
    while (pos && pos <= 20) \
    { \
        this->cache.loadout[pos - 1].id = rr_binary_encoder_read_uint8(&decoder); \
        this->cache.loadout[pos - 1].rarity = rr_binary_encoder_read_uint8(&decoder); \
        pos = rr_binary_encoder_read_uint8(&decoder); \
    } \
}

#define GET_ID_RARITY(encoder, start) \
{ \
    uint8_t id = rr_binary_encoder_read_uint8(encoder); \
    while(id) \
    { \
        uint8_t rarity = rr_binary_encoder_read_uint8(encoder); \
        uint32_t count = rr_binary_encoder_read_varuint(encoder); \
        start[id - 1][rarity] = count; \
        id = rr_binary_encoder_read_uint8(encoder); \
    } \
}

void rr_game_cache_data(struct rr_game *this)
{
    struct rr_binary_encoder encoder;
    rr_binary_encoder_init(&encoder, (uint8_t *) storage_buf2);
    rr_binary_encoder_write_uint8(&encoder, this->cache.displaying_debug_information);
    rr_binary_encoder_write_uint8(&encoder, this->cache.screen_shake);
    rr_binary_encoder_write_uint8(&encoder, this->cache.show_ui_hitbox);
    rr_binary_encoder_write_uint8(&encoder, this->cache.use_mouse);
    rr_binary_encoder_write_nt_string(&encoder, this->cache.nickname);
    rr_binary_encoder_write_float64(&encoder, this->cache.experience);
    rr_binary_encoder_write_varuint(&encoder, this->dev_flag);
    STORE_LOADOUT;
    STORE_ID_RARITY(&encoder, this->inventory, rr_petal_id_max, rr_rarity_id_max);
    STORE_ID_RARITY(&encoder, this->cache.mob_kills, rr_mob_id_max, rr_rarity_id_max);
    rr_local_storage_store_bytes("account_data", encoder.start, encoder.at - encoder.start);
}

void rr_game_cache_load(struct rr_game *this)
{
    struct rr_binary_encoder decoder;
    rr_local_storage_get_bytes("account_data", storage_buf2);
    rr_binary_encoder_init(&decoder, (uint8_t *) storage_buf2);
    this->cache.displaying_debug_information = rr_binary_encoder_read_uint8(&decoder);
    this->cache.screen_shake = rr_binary_encoder_read_uint8(&decoder);
    this->cache.show_ui_hitbox = rr_binary_encoder_read_uint8(&decoder);
    this->cache.use_mouse = rr_binary_encoder_read_uint8(&decoder);
    rr_binary_encoder_read_nt_string(&decoder, this->cache.nickname);
    this->cache.experience = rr_binary_encoder_read_float64(&decoder);
    this->dev_flag = rr_binary_encoder_read_varuint(&decoder);
    READ_LOADOUT;
    GET_ID_RARITY(&decoder, this->inventory);
    GET_ID_RARITY(&decoder, this->cache.mob_kills);
}