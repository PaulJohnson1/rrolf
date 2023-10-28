#include <Client/Ui/Engine.h>
#include <Client/Ui/Ui.h>

struct rr_ui_element *rr_ui_anti_afk_container_init()
{
    struct rr_ui_element *e = rr_ui_v_container_init(
        rr_ui_container_init(), 0, 15, rr_ui_text_init("AFK Check", 20, -1),
        rr_ui_text_init("Are you here?", 20, 0xffffffff),
        rr_ui_labeled_button_init("I'm here", 10, 0), 0);

    e->x = 100;
    e->y = 100;
    // e->

    return e;
}
