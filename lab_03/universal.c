#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

void universal_swap(void *first, void *second, size_t size)
{
    void *buf = malloc(size);
    if (buf)
    {
        memcpy(buf, first, size);
        memcpy(first, second, size);
        memcpy(second, buf, size);
        free(buf);
    }
}

int compare_int64(int64_t *first, int64_t *second)
{
    int exit_code = -1;
    if (*first == *second)
    {
        exit_code = 0;
    }
    else if (*first > *second)
    {
        exit_code = 1;
    }

    return exit_code;
}

int fscanf_int64(FILE* source, int64_t *elem)
{
    return fscanf(source, "%" SCNd64, elem);
}

void fprintf_int64(FILE* source, int64_t *elem)
{
    fprintf(source, "%" PRId64, *elem);
}
