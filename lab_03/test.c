#include <stdio.h>
#include "sparse_matrix.h"
#include "error_codes.h"
#include "logic.h"

int main()
{
    sparse_matrix smatrix;
    set_null_matrix(&smatrix);
    scanf("%d %d", &(smatrix.n), &(smatrix.m));
    input_smatrix(&smatrix);
    printf("\n");

    print_smatrix_pretty(&smatrix);
    print_smatrix_source(&smatrix);

    getchar();getchar();
    return SUCCES;
}