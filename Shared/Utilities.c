#include <Shared/Utilities.h>

#include <math.h>
#include <stdlib.h>

void rr_log_hex(uint8_t *start, uint8_t *end)
{
    while (start != end)
        printf("%02X ", *start++);
    puts("");
}

float rr_lerp(float start, float end, float t)
{
    t = rr_fclamp(t, 0, 1);

    return (end - start) * t + start;
}

float rr_angle_lerp(float start, float end, float t)
{
    t = rr_fclamp(t, 0, 1);

    start = fmod(start, 2 * M_PI);
    end = fmod(end, 2 * M_PI);
    if (fabs(end - start) < M_PI)
        return (end - start) * t + start;
    else
    {
        if (end > start)
            start += 2 * M_PI;
        else
            end += 2 * M_PI;
        return fmod((end - start) * t + start + 2 * M_PI, 2 * M_PI);
    }
}

float rr_frand() { return (double)rand() / ((double)RAND_MAX+1.0); }

float rr_fclamp(float v, float s, float e)
{
    if (v < s)
        v = s;
    else if (v > e)
        v = e;
    return v;
}