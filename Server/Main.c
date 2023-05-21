#include <fenv.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <Server/Server.h>
#include <Shared/Encoder.h>
#include <Shared/Utilities.h>
#include <Shared/StaticData.h>

int main()
{
#ifndef NDEBUG
    // feenableexcept(FE_DIVBYZERO | FE_INVALID);
#endif
    rr_set_petal_data(0, 0, 0, 0);
    rr_set_petal_data(1, 10, 20, 50);
    rr_set_petal_data(2, 0, 0, 0);
    struct rr_server s;
    rr_server_init(&s);
    rr_server_run(&s);
    rr_server_free(&s);
}
