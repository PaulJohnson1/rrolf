#pragma once

#include <Client/Renderer/Renderer.h>
#include <Client/Particle.h>
#include <Client/Socket.h>
#include <Client/Ui/Ui.h>
#include <Shared/Entity.h>
#include <Shared/Rivet.h>
#include <Shared/StaticData.h>
#include <Shared/pb.h>

#define RR_DEBUG_POLL_SIZE 10

struct rr_game_debug_info
{
    uint8_t frame_pos;
    uint8_t websocket_pos;
    long tick_times[RR_DEBUG_POLL_SIZE];
    long frame_times[RR_DEBUG_POLL_SIZE];
    long message_sizes[RR_DEBUG_POLL_SIZE];
};

struct rr_game_loadout_petal
{
    uint8_t id;
    uint8_t rarity;
};

struct rr_game_squad_client
{
    struct rr_game_loadout_petal loadout[20];
    char name[18];
    uint8_t in_use;
    uint8_t ready;
};

struct rr_game_crafting_data
{
    float animation;
    uint32_t count;
    uint32_t success_count;
    uint8_t crafting_id;
    uint8_t crafting_rarity;
};

// anything cross reload
struct rr_game_cache
{
    double experience;
    uint32_t mob_kills[rr_mob_id_max][rr_rarity_id_max];
    float map_props;
    float wave_start_percent;
    struct rr_game_loadout_petal loadout[20];
    uint8_t use_mouse;
    uint8_t displaying_debug_information;
    uint8_t show_ui_hitbox;
    uint8_t screen_shake;
    uint8_t slots_unlocked;
    uint8_t low_performance_mode;
    char nickname[128];
};

struct rr_game
{
    struct rr_particle_manager particle_manager;
    struct rr_game_crafting_data crafting_data;
    struct rr_game_debug_info debug_info;
    struct rr_game_cache cache;

    struct rr_rivet_account rivet_account;
    struct rr_game_squad_client squad_members[RR_SQUAD_MEMBER_COUNT];
    struct rr_websocket socket;

    struct rr_ui_element *petal_tooltips[rr_petal_id_max][rr_rarity_id_max];
    struct rr_ui_element *mob_tooltips[rr_mob_id_max][rr_rarity_id_max];
    struct rr_ui_element *squad_player_tooltips[RR_SQUAD_MEMBER_COUNT];
    struct rr_ui_element *rivet_info_tooltip;
    struct rr_ui_element *link_account_tooltip;
    struct rr_ui_element *inventory_tooltip;
    struct rr_ui_element *gallery_tooltip;
    struct rr_ui_element *craft_tooltip;
    struct rr_ui_element *settings_tooltip;
    struct rr_renderer *renderer;
    struct rr_input_data *input_data;
    struct rr_simulation *simulation;
    struct rr_simulation *deletion_simulation;
    struct rr_component_player_info *player_info;
    struct rr_ui_element *window;
    struct rr_ui_element *prev_focused;
    struct rr_ui_element *focused;
    struct rr_ui_element *pressed;

    uint32_t inventory[rr_petal_id_max][rr_rarity_id_max];
    EntityIdx player_infos[RR_SQUAD_MEMBER_COUNT];
    uint64_t dev_flag;
    float lerp_delta;
    
    uint8_t squad_pos;
    uint8_t socket_ready;
    uint8_t socket_pending;
    uint8_t rivet_lobby_pending;
    uint8_t joined_squad;
    uint8_t simulation_ready;
    uint8_t bottom_ui_open; // 0 = none, 1 = inv, 2 = crafting
    uint8_t top_ui_open;    // 0 = none, 1 = settings, 2 = changelog
    uint8_t block_ui_input;
    uint8_t ticks_until_text_cache;
    uint8_t selected_biome;
    uint8_t is_mobile;

    uint8_t squad_private;
    char squad_code[7];
    char connect_code[7];
};

void rr_game_init(struct rr_game *);
void rr_game_tick(struct rr_game *, float);
void rr_game_connect_socket(struct rr_game *);
void rr_simulation_read_binary(struct rr_game *, struct proto_bug *);

void rr_game_websocket_on_event_function(enum rr_websocket_event_type,
                                         void *, void *,
                                         uint64_t);
