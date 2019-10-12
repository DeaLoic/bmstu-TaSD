#include <stdio.h>
#include <inttypes.h>
#include "universal.h"
#include "sparse_matrix.h"
#include "matrix.h"
#include "error_codes.h"
#include "logic.h"

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
            print_smatrix_source(&smatrix);
            sparse_matrix sres;
            set_null_matrix(&sres);
            change_size_smatrix(&sres, 1, smatrix.m, smatrix.m);

            uint64_t start = tick();
            multiply_matrix_row(&smatrix_row, &smatrix, &sres);
            printf("result time compact imagination: %" PRIu64 " processors ticks\n", tick() - start);

            print_smatrix_pretty(&sres);

            matrix_t matrix;
            matrix_t matrix_row;
            matrix_t matrix_res;

		    init_null_matrix(&matrix_row);
		    init_null_matrix(&matrix);
		    init_null_matrix(&matrix_res);

            sparse_to_classic_matrix(&smatrix, &matrix);
            sparse_to_classic_matrix(&smatrix_row, &matrix_row);

            create_matrix(&matrix_res, smatrix_row.n, smatrix.m);
            start = tick();
            multiply_matrix(&matrix_row, &matrix, &matrix);
            printf("result time normal imagination: %" PRIu64 " processors ticks\n", tick() - start);
            
            output_matrix(&matrix_res);
            //compare_time(1000);
            delete_smatrix_content(&sres);
        }
        delete_smatrix_content(&smatrix_row);
    }

    delete_smatrix_content(&smatrix);

    getchar();getchar();
    return error_code;
}