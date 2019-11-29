#include "modeling.h"
#include "queue_list.h"
#include "logic.h"
#include "info.h"
#include "universal.h"
#include "error_codes.h"
#include "request.h"
#include "array.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    queue_list_t queue;
    free_zone_t free_zone;
    info_t info;
    double rand_sum;
    srand(time(NULL));
    for (int i = 0; i < 1000; i++)
    {
        rand_sum += (double)rand() / (double)RAND_MAX;
    }
    printf("%lf, %lf", rand_sum, rand_sum / 1000 * 4);
    getchar();
    return 0;
}