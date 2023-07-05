#include <Client/Ui/Engine.h>
#include <Client/Ui/Ui.h>

struct rr_ui_element *rr_ui_rivet_init()
{
    return rr_ui_h_container_init(
        rr_ui_container_init(), 1, 5, 2,
        rr_ui_text_init("rivet account name", 15, 0xffffffff),
        rr_ui_text_init("tag", 15, 0xffcccccc));
}
