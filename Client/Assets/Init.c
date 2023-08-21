#include <Client/Assets/Init.h>

#include <Client/Assets/Render.h>
#include <Client/Assets/RenderFunctions.h>
#include <Client/Game.h>
#include <Client/Renderer/Renderer.h>


void rr_assets_init(struct rr_game *this)
{
    rr_renderer_tiles_init();
    rr_renderer_petal_cache_init();
    rr_renderer_mob_cache_init();
    rr_renderer_background_cache_init();
    rr_renderer_text_cache_init();
}