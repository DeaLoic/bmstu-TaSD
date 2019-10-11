#include <stdio.h>
#include "sparse_matrix.h"
#include "error_codes.h"
#include "logic.h"

int main()
{
    int side = 10;
    int percent = 33;
    compare_time(side, percent);

    getchar();getchar();
    return SUCCES;
}