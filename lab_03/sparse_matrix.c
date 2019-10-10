
#include <stdio.h>
#include "array.h"
#include "error_codes.h"
#include "sparse_matrix.h"
#include "universal.h"

int create_smatrix(sparse_matrix *smatrix)
{
    smatrix->n = 1;
    smatrix->m = 1;
    smatrix->values = NULL;
    smatrix->column_for_values = NULL;
    smatrix->rows_start = NULL;

    int error_code = create_array(&(smatrix->values), 1, sizeof(int));
    if (!error_code)
    {
        smatrix->values[0] = 1;
        error_code = create_array(&(smatrix->column_for_values), 1, sizeof(int));
    }
    if (!error_code)
    {
        smatrix->column_for_values[0] = 0;
        create_array(&(smatrix->rows_start), 1, sizeof(int));
    }
    if (!error_code)
    {
        smatrix->rows_start[0] = 0;
    }
    else
    {
        delete_smatrix_content(smatrix);
    }

    return error_code;
}

int delete_smatrix_content(sparse_matrix *smatrix)
{
    delete_array(&(smatrix->values));
    delete_array(&(smatrix->column_for_values));
    delete_array(&(smatrix->rows_start));
    smatrix->n = 0;
    smatrix->m = 0;

    return SUCCES;
}

int input_smatrix(sparse_matrix *smatrix, FILE *source)
{
    int error_code = INCORRECT_INPUT;
    if (is_smatrix_correct(smatrix))
    {
        error_code = SUCCES;
        
        int temp_elem = 0;
        int col = 0;
        
        int i = 0;
        char temp_char;
        int is_row_empty = 1;
        int readed_elems = 0;

        printf("Input col_number and element through the gap: \"col_number element\"\n");
        for (int row = 0; row < smatrix->n && !error_code; row++)
        {
            printf("Input row No %3d: ", row);
            temp_char = getchar();
            is_row_empty = 1;
            readed_elems = 0;
            (smatrix->rows_start)[row] = i;
            while (!error_code && temp_char != '\n' && (readed_elems) < smatrix->m && i < smatrix->cnt_non_zero)
            {
                ungetc(temp_char, stdin);
                if (scanf("%d %d", &col, &temp_elem) == 2 && col < smatrix->m && 0 <= col)
                {
                    (smatrix->values)[i] = temp_elem;
                    (smatrix->column_for_values)[i] = col;
                    i++;
                    readed_elems++;
                    is_row_empty = 0;
                }
                else
                {
                    error_code = INCORRECT_INPUT;
                }

                temp_char = getchar();
            }

            if (is_row_empty)
            {
                smatrix->rows_start[row] = -1;
            }

            printf("end");
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
        smatrix->cnt_non_zero = non_zero;
        error_code = change_size_array(&(smatrix->rows_start), n, sizeof(int));
    }
    if (!error_code)
    {
        smatrix->n = n;
        smatrix->m = m;
    }
    else
    {
        error_code = MEMORY_ERROR;
    }
    
    return error_code;
}

int is_in(int_arr_t arr, int n, int64_t elem)
{
    int pos = -1;
    for (int i = 0; i < n; i++)
    {
        if (pos == -1 && arr[i] == elem)
        {
            pos = i;
        }
    }

    return pos;
}

int cnt_nonzero_in_row(sparse_matrix *smatrix, int row)
{
    int len = 0;
    if (smatrix->rows_start[row] != -1)
    {
        while (row + len < smatrix->n && smatrix->rows_start[row + len] == -1)
        {
            len += 1;
        }
        if (row + len == smatrix->n)
        {
            len = smatrix->cnt_non_zero - smatrix->rows_start[row];
        }
        else
        {
            len = smatrix->rows_start[row + len] - smatrix->rows_start[row];
        }
    }

    return len;    
}

int print_smatrix_pretty(sparse_matrix *smatrix)
{
    int pos;

    for (int i = 0; i < smatrix->n; i++)
    {
        for (int j = 0; j < smatrix->m; j++)
        {
            pos = is_in(smatrix->column_for_values + smatrix->rows_start[i], cnt_nonzero_in_row(smatrix, i), j);
            if (pos != -1)
            {
                printf("%d ", smatrix->values[pos]);
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

int is_smatrix_correct(sparse_matrix *smatrix)
{
    return (smatrix && smatrix->n > 0 && smatrix->m > 0);
}