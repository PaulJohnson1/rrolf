#include <Server/EntityAllocation.h>

#include <math.h>
#include <stdlib.h>

#include <Shared/Utilities.h>

EntityIdx rr_simulation_alloc_player(EntityIdx entity,
                                     struct rr_simulation *this)
{
    struct rr_component_player_info *player_info =
        rr_simulation_get_player_info(this, entity);
    EntityIdx flower_id = rr_simulation_alloc_entity(this);
    struct rr_component_physical *physical =
        rr_simulation_add_physical(this, flower_id);
    struct rr_component_health *health =
        rr_simulation_add_health(this, flower_id);
    struct rr_component_relations *relations =
        rr_simulation_add_relations(this, flower_id);
    float distance = sqrt((float)rand() / (float)RAND_MAX) *
                     rr_simulation_get_arena(this, 1)->radius;
    float angle = (float)rand() / (float)RAND_MAX * M_PI * 2.0f;
    rr_component_physical_set_x(physical, cos(angle) * distance);
    rr_component_physical_set_y(physical, sin(angle) * distance);
    rr_component_physical_set_radius(physical, 25.0f);
    physical->friction = 0.75;
    if (rand() < RAND_MAX / 1000)
        rr_component_physical_set_angle(physical, rr_frand() * M_PI * 2);

    rr_simulation_add_flower(this, flower_id);
    rr_component_health_set_max_health(health, 100);
    rr_component_health_set_health(health, 100);
    health->damage = 10;
    rr_component_relations_set_team(relations, rr_simulation_team_id_players);
    rr_component_relations_set_owner(relations, entity);
    rr_component_player_info_set_camera_x(player_info, physical->x);
    rr_component_player_info_set_camera_y(player_info, physical->y);
    rr_component_player_info_set_flower_id(player_info, flower_id);
    return flower_id;
}

EntityIdx rr_simulation_alloc_petal(struct rr_simulation *this, float x, float y, uint8_t id,
                                    uint8_t rarity, EntityIdx owner)
{
    struct rr_petal_data const *data = &RR_PETAL_DATA[id];
    EntityIdx petal_id = rr_simulation_alloc_entity(this);
    struct rr_component_physical *physical =
        rr_simulation_add_physical(this, petal_id);
    struct rr_component_petal *petal = rr_simulation_add_petal(this, petal_id);
    struct rr_component_relations *relations =
        rr_simulation_add_relations(this, petal_id);
    struct rr_component_health *health =
        rr_simulation_add_health(this, petal_id);
    rr_component_physical_set_radius(physical, 10);
    rr_component_physical_set_angle(physical, rr_frand() * M_PI * 2);
    rr_component_physical_set_x(physical, x);
    rr_component_physical_set_y(physical, y);
    physical->mass = 5;
    physical->friction = 0.75;
    if (id == rr_petal_id_club)
    {
        rr_component_physical_set_radius(physical, 15);
        physical->mass = 100;
    }

    rr_component_petal_set_id(petal, id);
    rr_component_petal_set_rarity(petal, rarity);

    rr_component_relations_set_owner(relations,
                                     owner); // flower owns petal, not player
    rr_component_relations_set_team(
        relations, rr_simulation_get_relations(this, owner)->team);

    float scale_h = RR_PETAL_RARITY_SCALE[rarity].health;
    float scale_d = RR_PETAL_RARITY_SCALE[rarity].damage;

    rr_component_health_set_max_health(health, scale_h * data->health);
    rr_component_health_set_health(health, scale_h * data->health);
    rr_component_health_set_hidden(health, 1);
    health->damage = scale_d * data->damage / RR_PETAL_DATA[id].count[rarity];

    if (data->secondary_cooldown > 0)
    {
        struct rr_component_projectile *projectile =
            rr_simulation_add_projectile(this, petal_id);
        petal->effect_delay = data->secondary_cooldown;
    }
    else if (id == rr_petal_id_uranium)
    {
        petal->effect_delay = 25;
    }
    return petal_id;
}

EntityIdx rr_simulation_alloc_mob(struct rr_simulation *this,
float x, float y,
                                  enum rr_mob_id mob_id,
                                  enum rr_rarity_id rarity_id,
                                  enum rr_simulation_team_id team_id)
{
    EntityIdx entity = rr_simulation_alloc_entity(this);

    struct rr_component_arena *arena = rr_simulation_get_arena(this, 1);
    if (team_id == rr_simulation_team_id_mobs)
    {
        arena->mob_count++;
        arena->mob_counters[mob_id * rr_rarity_id_max + rarity_id]++;
    }

    struct rr_component_mob *mob = rr_simulation_add_mob(this, entity);
    struct rr_component_physical *physical =
        rr_simulation_add_physical(this, entity);
    struct rr_component_health *health = rr_simulation_add_health(this, entity);
    struct rr_component_relations *relations =
        rr_simulation_add_relations(this, entity);
    struct rr_component_ai *ai = rr_simulation_add_ai(this, entity);
    // init team elsewhere
    rr_component_mob_set_id(mob, mob_id);
    rr_component_mob_set_rarity(mob, rarity_id);
    struct rr_mob_rarity_scale const *rarity_scale =
        RR_MOB_RARITY_SCALING + rarity_id;
    struct rr_mob_data const *mob_data = RR_MOB_DATA + mob_id;
    rr_component_physical_set_radius(physical,
                                     mob_data->radius * rarity_scale->radius);
    rr_component_physical_set_angle(physical, rr_frand() * 2 * M_PI);
    rr_component_physical_set_x(physical, x);
    rr_component_physical_set_y(physical, y);
    physical->friction = 0.8;
    physical->mass = 100.0f * RR_MOB_RARITY_SCALING[rarity_id].damage;
    rr_component_health_set_max_health(health,
                                       mob_data->health * rarity_scale->health);
    rr_component_health_set_health(health,
                                   mob_data->health * rarity_scale->health);
    health->damage = mob_data->damage * rarity_scale->damage;

    rr_component_relations_set_team(relations, team_id);

    switch (mob_id)
    {
    case rr_mob_id_pteranodon:
        ai->ai_aggro_type = rr_ai_aggro_type_pteranodon;
        break;
    case rr_mob_id_triceratops:
        ai->ai_aggro_type = rr_ai_aggro_type_triceratops;
        break;
    case rr_mob_id_fern:
    case rr_mob_id_stump:
        ai->ai_aggro_type = rr_ai_aggro_type_none;
        break;
    case rr_mob_id_trex:
    case rr_mob_id_dakotaraptor:
        ai->ai_aggro_type = rr_ai_aggro_type_t_rex;
        break;
    case rr_mob_id_ankylosaurus:
        ai->ai_aggro_type = rr_ai_aggro_type_ankylosaurus;
        break;
    case rr_mob_id_pachycephalosaurus:
        ai->ai_aggro_type = rr_ai_aggro_type_pachycephalosaurus;
        break;
    case rr_mob_id_ornithomimus:
        ai->ai_aggro_type = rr_ai_aggro_type_default;
        break;
    case rr_mob_id_meteor:
        ai->ai_aggro_type = rr_ai_aggro_type_meteor;
        break;
    default:
        RR_UNREACHABLE("forgot to set ai aggro type");
    };
    /*
    if (mob_id == 255 && 0)
    {
        // ai->ai_type = rr_ai_type_neutral;
        EntityIdx prev_node = entity;
        struct rr_component_centipede *centipede =
            rr_simulation_add_centipede(this, entity);
        struct rr_vector extension;
        rr_vector_from_polar(&extension, physical->radius * 2, physical->angle);
        EntityIdx new_entity = RR_NULL_ENTITY;
        for (uint64_t i = 0; i < 5; ++i)
        {
            new_entity = rr_simulation_alloc_mob(this, 255, rarity_id, team_id);
            centipede->child_node = new_entity;
            centipede = rr_simulation_add_centipede(this, new_entity);
            struct rr_component_physical *new_phys =
                rr_simulation_get_physical(this, new_entity);
            rr_component_physical_set_x(new_phys,
                                        physical->x + extension.x * (i + 1));
            rr_component_physical_set_y(new_phys,
                                        physical->y + extension.y * (i + 1));
            centipede->parent_node = entity;
            entity = new_entity;
        }
    }
    */

    return entity;
}

EntityIdx rr_simulation_alloc_entity(struct rr_simulation *this)
{
    for (EntityIdx i = 1; i < RR_MAX_ENTITY_COUNT; i++)
    {
        if (!rr_simulation_has_entity(this, i))
        {
            if (rr_bitset_get_bit(this->recently_deleted, i))
                continue;
            rr_bitset_set(this->entity_tracker, i);
#ifndef NDEBUG
            printf("created with id %d\n", i);
#endif
            return i;
        }
    }

    RR_UNREACHABLE("ran out of entity ids");
}
