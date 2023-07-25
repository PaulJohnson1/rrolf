#include <Client/Assets/Init.h>

#include <Client/Game.h>
#include <Client/Renderer/Renderer.h>

static void mob_triceratops_init(struct rr_game *this)
{
     rr_renderer_init(&this->mob_triceratops_head);
    rr_renderer_set_dimensions(&this->mob_triceratops_head, 192, 336);
    rr_renderer_draw_svg(&this->mob_triceratops_head,
#include <Client/Assets/Mob/Triceratops/Head.h>
                         , 0, 0);

    rr_renderer_init(&this->mob_triceratops_body);
    rr_renderer_set_dimensions(&this->mob_triceratops_body, 192, 336);
    rr_renderer_draw_svg(&this->mob_triceratops_body,
#include <Client/Assets/Mob/Triceratops/Body.h>
                         , 0, 0);

    rr_renderer_init(&this->mob_triceratops_legs[0]);
    rr_renderer_set_dimensions(&this->mob_triceratops_legs[0], 240, 240);
    rr_renderer_draw_svg(&this->mob_triceratops_legs[0],
#include <Client/Assets/Mob/Triceratops/Leg1.h>
                         , 0, 0);

    rr_renderer_init(&this->mob_triceratops_legs[1]);
    rr_renderer_set_dimensions(&this->mob_triceratops_legs[1], 240, 240);
    rr_renderer_draw_svg(&this->mob_triceratops_legs[1],
#include <Client/Assets/Mob/Triceratops/Leg2.h>
                         , 0, 0);

    rr_renderer_init(&this->mob_triceratops_tail);
    rr_renderer_set_dimensions(&this->mob_triceratops_tail, 192, 336);
    rr_renderer_draw_svg(&this->mob_triceratops_tail,
#include <Client/Assets/Mob/Triceratops/Tail.h>
                         , 0, 0);
}

static void mob_pteranodon_init(struct rr_game *this)
{
    rr_renderer_init(&this->mob_pteranodon_wings[0]);
    rr_renderer_set_dimensions(&this->mob_pteranodon_wings[0], 432, 288);
    rr_renderer_draw_svg(&this->mob_pteranodon_wings[0],
#include <Client/Assets/Mob/Pteranodon/Wing1.h>
                         , 0, 0);

    rr_renderer_init(&this->mob_pteranodon_wings[1]);
    rr_renderer_set_dimensions(&this->mob_pteranodon_wings[1], 432, 288);
    rr_renderer_draw_svg(&this->mob_pteranodon_wings[1],
#include <Client/Assets/Mob/Pteranodon/Wing2.h>
                         , 0, 0);

    rr_renderer_init(&this->mob_pteranodon_body);
    rr_renderer_set_dimensions(&this->mob_pteranodon_body, 192, 336);
    rr_renderer_draw_svg(&this->mob_pteranodon_body,
#include <Client/Assets/Mob/Pteranodon/Body.h>
                         , 0, 0);
}

static void mob_t_rex_init(struct rr_game *this)
{
    rr_renderer_init(&this->mob_trex_head);
    rr_renderer_set_dimensions(&this->mob_trex_head, 144, 244);
    rr_renderer_draw_svg(&this->mob_trex_head,
#include <Client/Assets/Mob/Rex/Head.h>
                         , 0, 0);

    rr_renderer_init(&this->mob_trex_legs[0]);
    rr_renderer_set_dimensions(&this->mob_trex_legs[0], 240, 240);
    rr_renderer_draw_svg(&this->mob_trex_legs[0],
#include <Client/Assets/Mob/Rex/Leg1.h>
                         , 0, 0);

    rr_renderer_init(&this->mob_trex_legs[1]);
    rr_renderer_set_dimensions(&this->mob_trex_legs[1], 240, 240);
    rr_renderer_draw_svg(&this->mob_trex_legs[1],
#include <Client/Assets/Mob/Rex/Leg2.h>
                         , 0, 0);

    rr_renderer_init(&this->mob_trex_body);
    rr_renderer_set_dimensions(&this->mob_trex_body, 192, 336);
    rr_renderer_draw_svg(&this->mob_trex_body,
#include <Client/Assets/Mob/Rex/Body.h>
                         , 0, 0);

    rr_renderer_init(&this->mob_trex_tail);
    rr_renderer_set_dimensions(&this->mob_trex_tail, 192, 336);
    rr_renderer_draw_svg(&this->mob_trex_tail,
#include <Client/Assets/Mob/Rex/Tail.h>
                         , 0, 0);
}

static void mob_dakotaraptor_init(struct rr_game *this)
{
    rr_renderer_init(&this->mob_dakotaraptor_head);
    rr_renderer_set_dimensions(&this->mob_dakotaraptor_head, 144, 240);
    rr_renderer_draw_svg(&this->mob_dakotaraptor_head,
#include <Client/Assets/Mob/Dakotaraptor/Head.h>
                         , 0, 0);

    rr_renderer_init(&this->mob_dakotaraptor_body);
    rr_renderer_set_dimensions(&this->mob_dakotaraptor_body, 192, 336);
    rr_renderer_draw_svg(&this->mob_dakotaraptor_body,
#include <Client/Assets/Mob/Dakotaraptor/Body.h>
                         , 0, 0);

    rr_renderer_init(&this->mob_dakotaraptor_tail);
    rr_renderer_set_dimensions(&this->mob_dakotaraptor_tail, 192, 336);
    rr_renderer_draw_svg(&this->mob_dakotaraptor_tail,
#include <Client/Assets/Mob/Dakotaraptor/Tail.h>
                         , 0, 0);

    rr_renderer_init(&this->mob_dakotaraptor_wings[0]);
    rr_renderer_set_dimensions(&this->mob_dakotaraptor_wings[0], 144, 240);
    rr_renderer_draw_svg(&this->mob_dakotaraptor_wings[0],
#include <Client/Assets/Mob/Dakotaraptor/Wing1.h>
                         , 0, 0);

    rr_renderer_init(&this->mob_dakotaraptor_wings[1]);
    rr_renderer_set_dimensions(&this->mob_dakotaraptor_wings[1], 144, 240);
    rr_renderer_draw_svg(&this->mob_dakotaraptor_wings[1],
#include <Client/Assets/Mob/Dakotaraptor/Wing2.h>
                         , 0, 0);
}

static void mob_stump_and_fern_init(struct rr_game *this)
{
    rr_renderer_init(&this->mob_stump);
    rr_renderer_set_dimensions(&this->mob_stump, 400, 300);
    rr_renderer_draw_svg(&this->mob_stump,
#include <Client/Assets/Mob/Stump.h>
                         , 0, 0);
    
    rr_renderer_init(&this->mob_fern);
    rr_renderer_set_dimensions(&this->mob_fern, 200, 200);
    rr_renderer_draw_svg(&this->mob_fern,
#include <Client/Assets/Mob/Fern.h>
                         , 0, 0);
}

static void mob_pachycephalosaurus_init(struct rr_game *this)
{
    rr_renderer_init(&this->mob_pachycephalosaurus_head);
    rr_renderer_set_dimensions(&this->mob_pachycephalosaurus_head, 192, 336);
    rr_renderer_draw_svg(&this->mob_pachycephalosaurus_head,
#include <Client/Assets/Mob/Pachycephalosaurus/Head.h>
                         , 0, 0);

    rr_renderer_init(&this->mob_pachycephalosaurus_body);
    rr_renderer_set_dimensions(&this->mob_pachycephalosaurus_body, 192, 336);
    rr_renderer_draw_svg(&this->mob_pachycephalosaurus_body,
#include <Client/Assets/Mob/Pachycephalosaurus/Body.h>
                         , 0, 0);

    rr_renderer_init(&this->mob_pachycephalosaurus_tail);
    rr_renderer_set_dimensions(&this->mob_pachycephalosaurus_tail, 192, 336);
    rr_renderer_draw_svg(&this->mob_pachycephalosaurus_tail,
#include <Client/Assets/Mob/Pachycephalosaurus/Tail.h>
                         , 0, 0);

    rr_renderer_init(&this->mob_pachycephalosaurus_legs[0]);
    rr_renderer_set_dimensions(&this->mob_pachycephalosaurus_legs[0], 240, 240);
    rr_renderer_draw_svg(&this->mob_pachycephalosaurus_legs[0],
#include <Client/Assets/Mob/Pachycephalosaurus/Leg1.h>
                         , 0, 0);

    rr_renderer_init(&this->mob_pachycephalosaurus_legs[1]);
    rr_renderer_set_dimensions(&this->mob_pachycephalosaurus_legs[1], 240, 240);
    rr_renderer_draw_svg(&this->mob_pachycephalosaurus_legs[1],
#include <Client/Assets/Mob/Pachycephalosaurus/Leg2.h>
                         , 0, 0);
}

static void mob_ornithomimus_init(struct rr_game *this)
{
    rr_renderer_init(&this->mob_ornithomimus_head);
    rr_renderer_set_dimensions(&this->mob_ornithomimus_head, 144, 240);
    rr_renderer_draw_svg(&this->mob_ornithomimus_head,
#include <Client/Assets/Mob/Ornithomimus/Head.h>
                         , 0, 0);

    rr_renderer_init(&this->mob_ornithomimus_body);
    rr_renderer_set_dimensions(&this->mob_ornithomimus_body, 144, 240);
    rr_renderer_draw_svg(&this->mob_ornithomimus_body,
#include <Client/Assets/Mob/Ornithomimus/Body.h>
                         , 0, 0);

    rr_renderer_init(&this->mob_ornithomimus_tail);
    rr_renderer_set_dimensions(&this->mob_ornithomimus_tail, 192, 336);
    rr_renderer_draw_svg(&this->mob_ornithomimus_tail,
#include <Client/Assets/Mob/Ornithomimus/Tail.h>
                         , 0, 0);

    rr_renderer_init(&this->mob_ornithomimus_wings[0]);
    rr_renderer_set_dimensions(&this->mob_ornithomimus_wings[0], 144, 240);
    rr_renderer_draw_svg(&this->mob_ornithomimus_wings[0],
#include <Client/Assets/Mob/Ornithomimus/Wing1.h>
                         , 0, 0);

    rr_renderer_init(&this->mob_ornithomimus_wings[1]);
    rr_renderer_set_dimensions(&this->mob_ornithomimus_wings[1], 144, 240);
    rr_renderer_draw_svg(&this->mob_ornithomimus_wings[1],
#include <Client/Assets/Mob/Ornithomimus/Wing2.h>
                         , 0, 0);
}

static void tiles_init(struct rr_game *this)
{
    rr_renderer_init(&this->tiles[0]);
    rr_renderer_set_dimensions(&this->tiles[0], 256, 256);
    rr_renderer_draw_svg(&this->tiles[0],
#include <Client/Assets/Tile/1.h>
                         , 0, 0);

    rr_renderer_init(&this->tiles[1]);
    rr_renderer_set_dimensions(&this->tiles[1], 256, 256);
    rr_renderer_draw_svg(&this->tiles[1],
#include <Client/Assets/Tile/2.h>
                         , 0, 0);

    rr_renderer_init(&this->tiles[2]);
    rr_renderer_set_dimensions(&this->tiles[2], 256, 256);
    rr_renderer_draw_svg(&this->tiles[2],
#include <Client/Assets/Tile/3.h>
                         , 0, 0);

    this->tiles_size = 3;
    rr_renderer_init(&this->background_features[0]);
    rr_renderer_set_dimensions(&this->background_features[0], 100, 100);
    rr_renderer_draw_svg(&this->background_features[0],
#include <Client/Assets/MapFeature/Moss.h>
                         , 0, 0);

    rr_renderer_init(&this->background_features[1]);
    rr_renderer_set_dimensions(&this->background_features[1], 200, 200);
    rr_renderer_draw_svg(&this->background_features[1],
#include <Client/Assets/MapFeature/WaterLettuce.h>
                         , 0, 0);

    rr_renderer_init(&this->background_features[2]);
    rr_renderer_set_dimensions(&this->background_features[2], 200, 200);
    rr_renderer_draw_svg(&this->background_features[2],
#include <Client/Assets/MapFeature/Fern1.h>
                         , 0, 0);

    rr_renderer_init(&this->background_features[3]);
    rr_renderer_set_dimensions(&this->background_features[3], 200, 200);
    rr_renderer_draw_svg(&this->background_features[3],
#include <Client/Assets/MapFeature/Fern2.h>
                         , 0, 0);

    rr_renderer_init(&this->background_features[4]);
    rr_renderer_set_dimensions(&this->background_features[4], 200, 200);
    rr_renderer_draw_svg(&this->background_features[4],
#include <Client/Assets/MapFeature/Fern3.h>
                         , 0, 0);

    rr_renderer_init(&this->background_features[5]);
    rr_renderer_set_dimensions(&this->background_features[5], 200, 200);
    rr_renderer_draw_svg(&this->background_features[5],
#include <Client/Assets/MapFeature/Fern3.h>
                         , 0, 0);

    rr_renderer_init(&this->background_features[6]);
    rr_renderer_set_dimensions(&this->background_features[6], 200, 200);
    rr_renderer_draw_svg(&this->background_features[6],
#include <Client/Assets/MapFeature/Fern4.h>
                         , 0, 0);

    rr_renderer_init(&this->background_features[7]);
    rr_renderer_set_dimensions(&this->background_features[7], 200, 200);
    rr_renderer_draw_svg(&this->background_features[7],
#include <Client/Assets/MapFeature/PalmTree.h>
                         , 0, 0);

    rr_renderer_init(&this->background_features[8]);
    rr_renderer_set_dimensions(&this->background_features[8], 450, 450);
    rr_renderer_draw_svg(&this->background_features[8],
#include <Client/Assets/MapFeature/BeechTree.h>
                         , 0, 0);
}

void rr_assets_init(struct rr_game *this)
{
    mob_triceratops_init(this);
    mob_pteranodon_init(this);
    mob_t_rex_init(this);
    mob_dakotaraptor_init(this);
    mob_stump_and_fern_init(this);
    mob_pachycephalosaurus_init(this);
    mob_ornithomimus_init(this);
    tiles_init(this);
}