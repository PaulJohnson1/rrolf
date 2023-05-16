#include <Client/InputData.h>

#include <string.h>

void rr_input_data_init(struct rr_input_data *this)
{
    memset(this, 0, sizeof(*this));
}
