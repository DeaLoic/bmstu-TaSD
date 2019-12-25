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
    int n;
    int m;
    printf("Input size of matrix: \n");

    if (scanf("%d %d", &(n), &(m)) == 2  && n > 0 && m > 0)
    {

        change_size_smatrix(&smatrix, n, m, 0);
        error_code = input_smatrix(&smatrix);
    }
    else
    {
    	printf("Incorrect size\n");
    	error_code = INPUT_ERROR;
    }

    if (!error_code)
    {
        sparse_matrix smatrix_row;
        set_null_matrix(&smatrix_row);
        change_size_smatrix(&smatrix_row, 1, smatrix.m, 0);
        printf("\n");
        printf("Input vector-row: \n");
        error_code = input_smatrix(&smatrix_row);
        if (!error_code)
        {
        	printf("\nSource vector-row:\n");
            print_smatrix_source(&smatrix_row);
            printf("\nSource matrix:\n");
            print_smatrix_source(&smatrix);

            sparse_matrix sres;
            set_null_matrix(&sres);
            change_size_smatrix(&sres, 1, smatrix.m, smatrix.m);

            uint64_t end = 0;
            uint64_t start = tick();

            multiply_matrix_row(&smatrix_row, &smatrix, &sres);
            end = tick() - start;
            printf("Result time compact imagination: %" PRIu64 " processors ticks\n", end);

            print_smatrix_source(&sres);
            printf("\n");

            matrix_t matrix;
            matrix_t matrix_row;
            matrix_t matrix_res;

		    init_null_matrix(&matrix_row);
		    init_null_matrix(&matrix);
		    init_null_matrix(&matrix_res);

            sparse_to_classic_matrix(&smatrix, &matrix);
            sparse_to_classic_matrix(&smatrix_row, &matrix_row);
            printf("\n");

            create_matrix(&matrix_res, smatrix_row.n, smatrix.m);
            printf("\n");
            start = tick();
            multiply_matrix(&matrix_row, &matrix, &matrix_res);
            end = tick() - start;
            printf("result time normal imagination: %" PRIu64 " processors ticks\n", end);
            
            //output_matrix(&matrix_res);

            compare_time(100);
            delete_smatrix_content(&sres);
        }
        delete_smatrix_content(&smatrix_row);
    }

    delete_smatrix_content(&smatrix);

    getchar();
    return error_code;
}