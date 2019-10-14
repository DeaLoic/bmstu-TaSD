
#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#include "error_codes.h"
#include "sparse_matrix.h"
#include "universal.h"

int set_null_matrix(sparse_matrix *smatrix)
{
    smatrix->n = 0;
    smatrix->m = 0;
    smatrix->cnt_non_zero = 0;
    smatrix->values = NULL;
    smatrix->column_for_values = NULL;
    smatrix->rows_start = NULL;

    return SUCCES;
}

int delete_smatrix_content(sparse_matrix *smatrix)
{
    delete_array(&(smatrix->values));
    delete_array(&(smatrix->column_for_values));
    delete_array(&(smatrix->rows_start));
    smatrix->n = 0;
    smatrix->m = 0;
    smatrix->cnt_non_zero = 0;

    return SUCCES;
}

int input_smatrix(sparse_matrix *smatrix)
{
    int error_code = SUCCES;
    int cur_element = 0;
    int cur_col_index = 0;
    int cur_row_index = 0;
    int last_row_index = 0;
    int cnt_non_zero = 0;
    int stop = 0;
    char buff[128];

    printf("Input non zero elements in format (row col value)\nFor interrupt input enter -1 in row position\n0 <= row < %d\n0 <= col < %d", smatrix->n, smatrix->m);
    while (!stop && cnt_non_zero != (smatrix->n * smatrix->m))
    {
        fflush(stdin);
        while (!(scanf("%d %d %d", &cur_row_index, &cur_col_index, &cur_element) == 3 && ((cur_row_index >= last_row_index &&\
        	cur_col_index >= 0  && cur_col_index < smatrix->m && cur_element != 0) ||\
        	cur_row_index == -1)))
        {
            gets(buff);
        	fflush(stdin);
        	printf("Incorrect input. Try agains\n");
        }

        if (cur_row_index != -1)
        {
            if (smatrix->cnt_non_zero == cnt_non_zero)
            {
                error_code = change_size_smatrix(smatrix, smatrix->n, smatrix->m, cnt_non_zero + 20);
            }

            if (smatrix->rows_start[cur_row_index] == 0)
            {
                smatrix->rows_start[cur_row_index] = cnt_non_zero;
            }
            if (find_col_index(smatrix->column_for_values + smatrix->rows_start[cur_row_index], \
                        cnt_non_zero - smatrix->rows_start[cur_row_index], \
                        smatrix->rows_start[cur_row_index]) == -1)
            {

                smatrix->values[cnt_non_zero] = cur_element;
                smatrix->column_for_values[cnt_non_zero] = cur_col_index;
                cnt_non_zero++;

                last_row_index = cur_row_index;
            }
            else
            {
                printf("Incorrect input. Try again\n");
            }
        }
        else
        {
            printf("End of input. Succes write %d element(s)\n", cnt_non_zero);
            stop = 1;
        }
    }

    if (stop == 0)
    {
        printf("Matrix filled. Succes write %d element(s)\n", cnt_non_zero);
    }

    change_size_smatrix(smatrix, smatrix->n, smatrix->m, cnt_non_zero);
    print_smatrix_source(smatrix);

    for (int i = 1; i < smatrix->n; i++)
    {
        if (smatrix->rows_start[i] == 0)
        {
            smatrix->rows_start[i] = smatrix->rows_start[i - 1];
        }
    }

    return error_code;
}

int change_size_smatrix(sparse_matrix *smatrix, int n, int m, int non_zero)
{
    int error_code = change_size_array(&(smatrix->values), non_zero, sizeof(int));
    if (!error_code)
    {
        error_code = change_size_array(&(smatrix->column_for_values), non_zero, sizeof(int));
    }
    if (!error_code)
    {
        error_code = change_size_array(&(smatrix->rows_start), n, sizeof(int));
    }
    if (!error_code)
    {
        for (int i = smatrix->n; i < n; i++)
        {
        	if (i > 0)
        	{
        		smatrix->rows_start[i] = smatrix->rows_start[i - 1];
        	}
        	else
        	{
        		smatrix->rows_start[i] = 0;
        	}
            
        }
        smatrix->n = n;
        smatrix->m = m;
        smatrix->cnt_non_zero = non_zero;
    }
    else
    {
        change_size_array(&(smatrix->values), smatrix->cnt_non_zero, sizeof(int));
        change_size_array(&(smatrix->column_for_values), smatrix->cnt_non_zero, sizeof(int));
        error_code = MEMORY_ERROR;
    }
    
    return error_code;
}

int find_col_index(int_arr_t arr, int n, int col)
{
    int col_index = -1;

    for (int i = 0; i < n; i++)
    {
        if (arr[i] == col)
        {
            col_index = i;
            i = n;
        }
    }
    return col_index;
}

int print_smatrix_pretty(sparse_matrix *smatrix)
{
    int pos;
    int cur_len = 0;

    for (int i = 0; i < smatrix->n; i++)
    {
        for (int j = 0; j < smatrix->m; j++)
        {
            if (i == smatrix->n - 1)
            {
                cur_len = smatrix->cnt_non_zero - smatrix->rows_start[i];
            }
            else
            {
                cur_len = smatrix->rows_start[i + 1] - smatrix->rows_start[i];
            }

            pos = find_col_index(smatrix->column_for_values + smatrix->rows_start[i], cur_len, j);
            if (pos != -1)
            {
                printf("%d ", smatrix->values[pos + smatrix->rows_start[i]]);
            }
            else
            {
                printf("0 ");
            }
        }
        printf("\n");
    }

return SUCCES;
}

int print_smatrix_source(sparse_matrix *smatrix)
{
    print_array(smatrix->values, smatrix->cnt_non_zero, sizeof(int), stdout, (void (*)(FILE*, void*))fprintf_int);
    print_array(smatrix->column_for_values, smatrix->cnt_non_zero, sizeof(int), stdout, (void (*)(FILE*, void*))fprintf_int);
    print_array(smatrix->rows_start, smatrix->n, sizeof(int), stdout, (void (*)(FILE*, void*))fprintf_int);

    return SUCCES;
}

int multiply_matrix_row(sparse_matrix *matrix_row, sparse_matrix *smatrix, sparse_matrix *sres)
{
    
}

int multiply_row_col(sparse_matrix *matrix_row, sparse_matrix *smatrix, int row, int col)
{
    
}

int is_smatrix_correct(sparse_matrix *smatrix)
{
    return (smatrix && smatrix->n > 0 && smatrix->m > 0);
}