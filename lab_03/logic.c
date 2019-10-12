#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"
#include "sparse_matrix.h"
#include "error_codes.h"
#include "universal.h"

int sparse_to_classic_matrix(sparse_matrix *smatrix, matrix_t *matrix)
{
    int error_code = SUCCES;
    delete_matrix(matrix);
    error_code = create_matrix(matrix, smatrix->n, smatrix->m);
    if (!error_code)
    {
        for (int i = 0; i < smatrix->n; i++)
        {
            if (smatrix->rows_start[i] != -1)
            {
                for (int j = 0; j < cnt_nonzero_in_row(smatrix, i); j++)
                {
                    ((matrix->body)[i][smatrix->column_for_values[smatrix->rows_start[i] + j]]) = ((smatrix->values)[(smatrix->rows_start)[i] + j]);
                    //printf("i %d, j %d, el %d, el %d\n", i, smatrix->rows_start[i] + j, ((matrix->body)[i][smatrix->column_for_values[smatrix->rows_start[i] + j]]), ((smatrix->values)[(smatrix->rows_start)[i] + j]));
                }
            }
        }
    }

    return error_code;
}

int create_random_smatrix(sparse_matrix *smatrix, int n, int m, int percent_of_sparsed)
{
    srand(time(0));
    int error_code = change_size_smatrix(smatrix, n, m, 0);
    int res;
    int cnt_nonzero = 0;
    int is_row_empty = 1;
    for (int i = 0; i < n && !error_code; i++)
    {
        smatrix->rows_start[i] = cnt_nonzero;
        is_row_empty = 1;
                
        for (int j = 0; j < m && !error_code; j++)
        {
            res = rand() % 100;
            if (res < (100 - percent_of_sparsed))
            {
                is_row_empty = 0;
                if (cnt_nonzero == smatrix->cnt_non_zero)
                {
                    error_code = change_size_smatrix(smatrix, smatrix->n, smatrix->m, cnt_nonzero * 2 + 1);
                }

                smatrix->column_for_values[cnt_nonzero] = j;
                smatrix->values[cnt_nonzero] = res + 1;
                cnt_nonzero++;
            }
        }
        
        if (is_row_empty)
        {
            smatrix->rows_start[i] = -1;
        }
    }
    if (!error_code)
    {
        error_code = change_size_smatrix(smatrix, smatrix->n, smatrix->m, cnt_nonzero);
    }
    else
    {
        delete_smatrix_content(smatrix);
    }
    
    return error_code;
}

int cnt_time(int size, int percent)
{
    sparse_matrix smatrix_row;
    sparse_matrix smatrix;
    sparse_matrix sres;
    set_null_matrix(&sres);
    set_null_matrix(&smatrix);
    set_null_matrix(&smatrix_row);

    create_random_smatrix(&smatrix_row, 1, size, percent);
    create_random_smatrix(&smatrix, size, size, percent);

    matrix_t matrix_row;
    matrix_t matrix_res;
    matrix_t matrix;
    init_null_matrix(&matrix_row);
    init_null_matrix(&matrix);
    init_null_matrix(&matrix_res);


    sparse_to_classic_matrix(&smatrix, &matrix);
    sparse_to_classic_matrix(&smatrix_row, &matrix_row);

    create_matrix(&matrix_res, smatrix_row.n, smatrix.m);

    printf("\nPercent %d%%\n", percent);

    change_size_smatrix(&sres, smatrix_row.n, smatrix.m, smatrix_row.n * smatrix.m);
    //printf("%d %d %d %d %d %d\n", matrix_res.n, matrix_res.m, matrix.n, matrix.m, matrix_res.n, matrix_res.m);

    uint64_t standart_tick = tick();
    multiply_matrix_row(&smatrix_row, &smatrix, &sres);
    standart_tick = tick() - standart_tick;
    printf("Compact matrix imagine.  %I64d processor time\n", standart_tick);
    change_size_smatrix(&sres, sres.n, sres.m, sres.cnt_non_zero);

    standart_tick = tick();
    multiply_matrix(&matrix_row, &matrix, &matrix_res);
    standart_tick = tick() - standart_tick;

    printf("Standart matrix imagine. %I64d processor time\n", standart_tick);

    delete_smatrix_content(&smatrix_row);
    delete_smatrix_content(&smatrix);
    delete_smatrix_content(&sres);

    delete_matrix(&matrix_row);
    delete_matrix(&matrix_res);
    delete_matrix(&matrix);

    return SUCCES;
}

int compare_time(int size)
{
    int percent = 75;
    int twice_percent = 85;
    int triple_percent = 95;
    
    printf("\nSize: %dx%d\n", size, size);

    cnt_time(size, percent);
    cnt_time(size, twice_percent);
    cnt_time(size, triple_percent);

    printf("\nSize: %dx%d\n", size * 5, size * 5);

    cnt_time(size * 5, percent);
    cnt_time(size * 5, twice_percent);
    cnt_time(size * 5, triple_percent);

    printf("\nSize: %dx%d\n", size * 10, size * 10);

    cnt_time(size * 10, percent);
    cnt_time(size * 10, twice_percent);
    cnt_time(size * 10, triple_percent);

    return SUCCES;
}

