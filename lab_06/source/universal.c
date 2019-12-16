#include "universal.h"
#include <stdio.h>

int int_compare(void* first, void *second)
{
    int result = 0;
    int first_i = *((int*)first);
    int second_i = *((int*)second);

    if (first_i < second_i)
    {
        result = -1;
    }
    else if (first_i > second_i)
    {
        result = 1;
    }

    return result;
}

void print_int(void *first)
{
    int first_i = *((int *)first);
    printf("%d", first_i);
}