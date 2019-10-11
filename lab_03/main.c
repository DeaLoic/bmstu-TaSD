#include <stdio.h>
#include "sparse_matrix.h"
#include "error_codes.h"

int main()
{
    sparse_matrix smatrix;

    int error_code = SUCCES;

    set_null_matrix(&smatrix);
    error_code = input_smatrix(&smatrix);
    if (!error_code)
    {
        sparse_matrix smatrix_row;
        set_null_matrix(&smatrix_row);
        change_size_smatrix(&smatrix_row, 1, smatrix.m, 0);
        printf("Input no-zero elements in vector-row: ");
        error_code = input_smatrix_row(&smatrix_row);
        if (!error_code)
        {
            print_smatrix_pretty(&smatrix_row);
            printf("\n");
            print_smatrix_pretty(&smatrix);
            sparse_matrix sres;
            set_null_matrix(&sres);
            change_size_smatrix(&sres, 1, smatrix.m, 0);
            multiply_matrix_row(&smatrix_row, &smatrix, &sres);
            print_smatrix_pretty(&sres);
            delete_smatrix_content(&sres);
        }
        delete_smatrix_content(&smatrix_row);
    }

    delete_smatrix_content(&smatrix);

    getchar();getchar();
    return error_code;
}