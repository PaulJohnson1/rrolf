#include <Client/Ui/Ui.h>

#include <stdio.h>
#include <stdlib.h>

#include <Client/Ui/Engine.h>

#include <Shared/StaticData.h>

struct rr_ui_element *rr_ui_petal_tooltip_init(uint8_t id, uint8_t rarity)
{
    char *cd = malloc((sizeof *cd) * 16);
    if (RR_PETAL_DATA[id].cooldown == 0)
        cd[0] = 0;
    else if (RR_PETAL_DATA[id].secondary_cooldown > 1)
        cd[sprintf(cd, "↻ %.1f + %.1fs",
                   (RR_PETAL_DATA[id].cooldown * 2 / 5) * 0.1,
                   (RR_PETAL_DATA[id].secondary_cooldown * 2 / 5) * 0.1)] = 0;
    else if (id == rr_petal_id_seed)
        cd[sprintf(cd, "↻ %.1f + %.1fs",
                   (RR_PETAL_DATA[id].cooldown * 2 / 5) * 0.1,
                   108 / RR_PETAL_RARITY_SCALE[rarity].damage)] = 0;
    else
        cd[sprintf(cd, "↻ %.1fs", (RR_PETAL_DATA[id].cooldown * 2 / 5) * 0.1)] =
            0;
    char *hp = malloc((sizeof *hp) * 16);
    hp[sprintf(hp, "%.1f", RR_PETAL_DATA[id].health *
                   RR_PETAL_RARITY_SCALE[rarity].health)] = 0;
    char *dmg = malloc((sizeof *dmg) * 16);
    dmg[sprintf(dmg, "%.1f",
                RR_PETAL_DATA[id].damage *
                    RR_PETAL_RARITY_SCALE[rarity].damage /
                    RR_PETAL_DATA[id].count[rarity])] = 0;

    struct rr_ui_element *this = rr_ui_set_background(
        rr_ui_v_container_init(
            rr_ui_tooltip_container_init(), 10, 5,
            rr_ui_flex_container_init(
                rr_ui_set_justify(
                    rr_ui_text_init(RR_PETAL_NAMES[id], 24, 0xffffffff), -1, 0),
                rr_ui_set_justify(rr_ui_text_init(cd, 16, 0xffffffff), 1, 0),
                30),
            rr_ui_set_justify(rr_ui_text_init(RR_RARITY_NAMES[rarity], 16,
                                              RR_RARITY_COLORS[rarity]),
                              -1, 0),
            rr_ui_static_space_init(10),
            rr_ui_set_justify(
                rr_ui_text_init(RR_PETAL_DESCRIPTIONS[id], 16, 0xffffffff), -1,
                0),
            NULL),
        0x80000000);
    if (RR_PETAL_DATA[id].health != 0)
    {
        rr_ui_container_add_element(
            this, 
        rr_ui_set_justify(rr_ui_h_container_init(
                                  rr_ui_container_init(), 0, 0,
                                  rr_ui_text_init("Health: ", 12, 0xff44ff44),
                                  rr_ui_text_init(hp, 12, 0xffffffff), NULL),
                              -1, 0));
        rr_ui_container_add_element(
            this, 
        rr_ui_set_justify(rr_ui_h_container_init(
                                rr_ui_container_init(), 0, 0,
                                rr_ui_text_init("Damage: ", 12, 0xffff4444),
                                rr_ui_text_init(dmg, 12, 0xffffffff), NULL),
                            -1, 0));
    }
    if (id == rr_petal_id_shell)
    {
        char *extra = malloc((sizeof *extra) * 8);
        extra[sprintf(extra, "%.1f",
                      25 * RR_PETAL_RARITY_SCALE[rarity].damage)] = 0;
        rr_ui_container_add_element(
            this, rr_ui_set_justify(
                      rr_ui_h_container_init(
                          rr_ui_container_init(), 0, 0,
                          rr_ui_text_init("Damage when shot: ", 12, 0xffff4444),
                          rr_ui_text_init(extra, 12, 0xffffffff), NULL),
                      -1, 0));
    }
    else if (id == rr_petal_id_magnet)
    {
        char *extra = malloc((sizeof *extra) * 8);
        extra[sprintf(extra, "+%.0f", 75 + 30 * RR_PETAL_RARITY_SCALE[rarity].health)] = 0;
        rr_ui_container_add_element(
            this, rr_ui_set_justify(
                      rr_ui_h_container_init(
                          rr_ui_container_init(), 0, 0,
                          rr_ui_text_init("Pickup range: ", 12, 0xff44ffdd),
                          rr_ui_text_init(extra, 12, 0xffffffff), NULL),
                      -1, 0));
    }
    else if (id == rr_petal_id_leaf)
    {
        char *extra = malloc((sizeof *extra) * 8);
        extra[sprintf(extra, "%.1f/s",
                      25 * 0.04 * RR_PETAL_RARITY_SCALE[rarity].damage)] = 0;
        rr_ui_container_add_element(
            this,
            rr_ui_set_justify(rr_ui_h_container_init(
                                  rr_ui_container_init(), 0, 0,
                                  rr_ui_text_init("Heal: ", 12, 0xffffff44),
                                  rr_ui_text_init(extra, 12, 0xffffffff), NULL),
                              -1, 0));
    }
    else if (id == rr_petal_id_egg && rarity > 0)
    {
        rr_ui_container_add_element(
            this, rr_ui_set_justify(
                      rr_ui_h_container_init(
                          rr_ui_container_init(), 0, 0,
                          rr_ui_text_init("Spawns: ", 12, 0xffe07422),
                          rr_ui_text_init(RR_RARITY_NAMES[rarity - 1], 12,
                                          RR_RARITY_COLORS[rarity - 1]),
                          rr_ui_text_init(" T-Rex", 12, 0xffffffff), NULL),
                      -1, 0));
    }
    else if (id == rr_petal_id_light)
    {
        char *extra = malloc((sizeof *extra) * 16);
        extra[sprintf(extra, "%.1f rad/s", (0.012 + 0.008 * rarity) * 25)] = 0;
        rr_ui_container_add_element(
            this, rr_ui_set_justify(
                      rr_ui_h_container_init(
                          rr_ui_container_init(), 0, 0,
                          rr_ui_text_init("Petal rotation: ", 12, 0xffd11b67),
                          rr_ui_text_init(extra, 12, 0xffffffff), NULL),
                      -1, 0));
    }
    else if (id == rr_petal_id_uranium)
    {
        char *extra = malloc((sizeof *extra) * 16);
        extra[sprintf(extra, "%.1f hp/s",
                      RR_PETAL_DATA[id].damage *
                          RR_PETAL_RARITY_SCALE[rarity].damage)] = 0;
        rr_ui_container_add_element(
            this, rr_ui_set_justify(
                      rr_ui_h_container_init(
                          rr_ui_container_init(), 0, 0,
                          rr_ui_text_init("Self damage: ", 12, 0xffbf29c2),
                          rr_ui_text_init(extra, 12, 0xffffffff), NULL),
                      -1, 0));
    }
    else if (id == rr_petal_id_feather)
    {
        char *extra = malloc((sizeof *extra) * 16);
        extra[sprintf(extra, "%.1f%%", 4 + 2.5 * rarity)] = 0;
        rr_ui_container_add_element(
            this, rr_ui_set_justify(
                      rr_ui_h_container_init(
                          rr_ui_container_init(), 0, 0,
                          rr_ui_text_init("Speed increase: ", 12, 0xff5682c4),
                          rr_ui_text_init(extra, 12, 0xffffffff), NULL),
                      -1, 0));
    }
    else if (id == rr_petal_id_azalea)
    {
        char *extra = malloc((sizeof *extra) * 8);
        extra[sprintf(extra, "%.1f",
                      10 * RR_PETAL_RARITY_SCALE[rarity].damage)] = 0;
        rr_ui_container_add_element(
            this,
            rr_ui_set_justify(rr_ui_h_container_init(
                                  rr_ui_container_init(), 0, 0,
                                  rr_ui_text_init("Heal: ", 12, 0xffffff44),
                                  rr_ui_text_init(extra, 12, 0xffffffff), NULL),
                              -1, 0));
    }
    else if (id == rr_petal_id_bone)
    {
        char *extra = malloc((sizeof *extra) * 8);
        extra[sprintf(extra, "%.1f",
                      2.5 * RR_PETAL_RARITY_SCALE[rarity].health)] = 0;
        rr_ui_container_add_element(
            this, rr_ui_set_justify(
                      rr_ui_h_container_init(
                          rr_ui_container_init(), 0, 0,
                          rr_ui_text_init("Damage reduction: ", 12, 0xff666666),
                          rr_ui_text_init(extra, 12, 0xffffffff), NULL),
                      -1, 0));
    }
    else if (id == rr_petal_id_web)
    {
        char *extra = malloc((sizeof *extra) * 8);
        extra[sprintf(extra, "%.0f",
                      50 + RR_PETAL_RARITY_SCALE[rarity].health * 12)] = 0;
        rr_ui_container_add_element(
            this, rr_ui_set_justify(
                      rr_ui_h_container_init(
                          rr_ui_container_init(), 0, 0,
                          rr_ui_text_init("Web radius: ", 12, 0xffafafaf),
                          rr_ui_text_init(extra, 12, 0xffffffff), NULL),
                      -1, 0));
        extra = malloc((sizeof *extra) * 8);
        extra[sprintf(extra, "%ds", 5 + rarity)] = 0;
        rr_ui_container_add_element(
            this, rr_ui_set_justify(
                      rr_ui_h_container_init(
                          rr_ui_container_init(), 0, 0,
                          rr_ui_text_init("Web duration: ", 12, 0xff2596be),
                          rr_ui_text_init(extra, 12, 0xffffffff), NULL),
                      -1, 0));
    }
    else if (id == rr_petal_id_crest)
    {
        char *extra = malloc((sizeof *extra) * 8);
        extra[sprintf(extra, "%.0f%%",
                      100 - 100 / (1.1 + 0.15 * rarity))] = 0;
        rr_ui_container_add_element(
            this, rr_ui_set_justify(
                      rr_ui_h_container_init(
                          rr_ui_container_init(), 0, 0,
                          rr_ui_text_init("Aggro decrease: ", 12, 0xffe38329),
                          rr_ui_text_init(extra, 12, 0xffffffff), NULL),
                      -1, 0));
    }
    else if (id == rr_petal_id_beak)
    {
        char *extra = malloc((sizeof *extra) * 8);
        extra[sprintf(extra, "%.1fs", 1 + 0.5 * rarity)] = 0;
        rr_ui_container_add_element(
            this, rr_ui_set_justify(
                      rr_ui_h_container_init(
                          rr_ui_container_init(), 0, 0,
                          rr_ui_text_init("Stun: ", 12, 0xff4266f5),
                          rr_ui_text_init(extra, 12, 0xffffffff), NULL),
                      -1, 0));
    }
    else if (id == rr_petal_id_lightning)
    {
        char *extra = malloc((sizeof *extra) * 8);
        extra[sprintf(extra, "%.1f", RR_PETAL_DATA[id].damage *
                    RR_PETAL_RARITY_SCALE[rarity].damage /
                    RR_PETAL_DATA[id].count[rarity] * 0.5)] = 0;
        rr_ui_container_add_element(
            this, rr_ui_set_justify(
                      rr_ui_h_container_init(
                          rr_ui_container_init(), 0, 0,
                          rr_ui_text_init("Lightning: ", 12, 0xff00cfcf),
                          rr_ui_text_init(extra, 12, 0xffffffff), NULL),
                      -1, 0));
        extra = malloc((sizeof *extra) * 8);
        extra[sprintf(extra, "%d", 1 + rarity)] = 0;
        rr_ui_container_add_element(
            this, rr_ui_set_justify(
                      rr_ui_h_container_init(
                          rr_ui_container_init(), 0, 0,
                          rr_ui_text_init("Bounces: ", 12, 0xfffc00cf),
                          rr_ui_text_init(extra, 12, 0xffffffff), NULL),
                      -1, 0));
    }
    else if (id == rr_petal_id_third_eye)
    {
        char *extra = malloc((sizeof *extra) * 8);
        extra[sprintf(extra, "%.0f%%",
                      100 / (0.9 - 0.07 * rarity) - 100)] = 0;
        rr_ui_container_add_element(
            this, rr_ui_set_justify(
                      rr_ui_h_container_init(
                          rr_ui_container_init(), 0, 0,
                          rr_ui_text_init("Vision increase: ", 12, 0xff4266f5),
                          rr_ui_text_init(extra, 12, 0xffffffff), NULL),
                      -1, 0));
    }
    else if (id == rr_petal_id_mandible)
    {
        char *extra = malloc((sizeof *extra) * 8);
        extra[sprintf(extra, "%.1f",
                      50 * RR_PETAL_RARITY_SCALE[rarity].damage)] = 0;
        rr_ui_container_add_element(
            this, rr_ui_set_justify(
                      rr_ui_h_container_init(
                          rr_ui_container_init(), 0, 0,
                          rr_ui_text_init("Extra Damage: ", 12, 0xff12bef1),
                          rr_ui_text_init(extra, 12, 0xffffffff), NULL),
                      -1, 0));
    }
    return this;
}