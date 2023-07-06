#include <Client/Ui/Ui.h>

#include <stdio.h>

#include <Client/Game.h>
#include <Client/Ui/Engine.h>

struct rr_ui_element *rr_ui_rivet_init(struct rr_game *game)
{
    return rr_ui_h_container_init(rr_ui_container_init(), 1, 5, 2,
                                  rr_ui_text_init(game->rivet_account.name, 15, 0xffffffff),
                                  rr_ui_text_init(game->rivet_account.account_number, 15, 0xffcccccc));
}
