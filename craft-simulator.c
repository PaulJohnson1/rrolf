#include <math.h>

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

double chance = 0.001386177720390883;
struct craft_data
{
    int fails;
    int successes;
    int count;
};

void *craft(void *_data)
{
    struct craft_data *data = _data;
    int fails = data->fails;
    int count = data->count;
    while (count >= 5)
    {
        if (data->successes +=
            ((double)rand() / RAND_MAX < (1 + fails) * chance))
            count -= 5;
        else
        {
            count -= (rand() & 3) + 1;
            fails = 0;
        }
    }
    data->fails = fails;
    data->count = count;
    printf("%d %d %d\n", data->count, data->fails, data->successes);
    return NULL;
}

int main()
{
    struct craft_data data = {0, 0, 1000000000};
    pthread_t thread_id;
    printf("Before Thread\n");
    pthread_create(&thread_id, NULL, craft, &data);
    pthread_detach(thread_id);
    printf("After Thread\n");
}