#include <fenv.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <Server/Server.h>
#include <Shared/Utilities.h>
#include <Shared/StaticData.h>

int main()
{
#ifndef NDEBUG
    feenableexcept(FE_DIVBYZERO | FE_INVALID);
#endif
    struct rr_server *s = malloc(sizeof *s);
    rr_server_init(s);
    rr_server_run(s);
    rr_server_free(s);
}
