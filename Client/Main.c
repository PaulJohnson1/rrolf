#include <Client/Renderer.h>

#include <stdio.h>

int main()
{
    struct rr_renderer renderer;
    rr_renderer_init(&renderer);
    printf("hello%p \n", &renderer);
    return 0;
}