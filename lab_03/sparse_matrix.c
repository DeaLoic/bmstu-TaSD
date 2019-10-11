
#include <stdio.h>
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

int input_smatrix_row(sparse_matrix *matrix_row)
{
    int error_code = INPUT_ERROR;
    printf("Input count of nonzero elements (max %d (len)): ", matrix_row->m);
    if (scanf("%d", &(matrix_row->cnt_non_zero)) && matrix_row->cnt_non_zero >= 0 && matrix_row->cnt_non_zero <= matrix_row->m && \
        !change_size_smatrix(matrix_row, 1, matrix_row->m, matrix_row->cnt_non_zero))
    {
        error_code = SUCCES;

        int temp_col = 0;
        int temp_elem = 0;
        
        if (matrix_row->cnt_non_zero)
        {
            printf("Input nonzero elements in format (column_index value): \n");
            matrix_row->rows_start[0] = 0;
        }

        for (int i = 0; i < matrix_row->cnt_non_zero && !error_code; i++)
        {
            if (scanf("%d %d", &temp_col, &temp_elem) && temp_col >= 0 && temp_col < matrix_row->m && temp_elem != 0\
            && is_col_busy(matrix_row->column_for_values, i, temp_col) == -1)
            {
                matrix_row->column_for_values[i] = temp_col;
                matrix_row->values[i] = temp_elem;
            }
            else
            {
                error_code = INCORRECT_INPUT;
                printf("Incorrect input (zero value, column already busy, incorrect col index)\n");
            }
        }
    }
    return error_code;
}

int input_smatrix(sparse_matrix *smatrix)
{
    int error_code = SUCCES;
        
    int cnt_non_zero_rows = 0;
    printf("Input n, m, number of nonzero rows and count of nonzero elements\n");
    if (scanf("%d", &(smatrix->n)) == 1 && smatrix->n > 0 && scanf("%d", &(smatrix->m)) == 1 && smatrix->m > 0 &&
            scanf("%d", &cnt_non_zero_rows) == 1 && cnt_non_zero_rows >= 0 && cnt_non_zero_rows <= smatrix->n &&
            scanf("%d", &(smatrix->cnt_non_zero)) && smatrix->cnt_non_zero >= 0 && smatrix->cnt_non_zero <= cnt_non_zero_rows * smatrix->m && \
            !change_size_smatrix(smatrix, smatrix->n, smatrix->m, smatrix->cnt_non_zero) && !feof(stdin) && getchar() == '\n')
    {
        printf("Pls, input numbers of row from low to high\n");
    }
    else
    {
        error_code = INPUT_ERROR;
        printf("Incorrect input\n");
    }

    int temp_elem = 0;
    int temp_col = 0;
    
    int row = -1;
    int i = 0;
    char temp_char;
    int readed_elems = 0;
    int temp_row = -1;
    for (int row_cnt = 0; row_cnt < cnt_non_zero_rows && !error_code; row_cnt++)
    {
        printf("Input non-zero-row index: ");

        if (scanf("%d", &temp_row) == 1 && temp_row > row && temp_row < smatrix->n && !feof(stdin) && getchar() == '\n')
        {
            row = temp_row;
            temp_char = ' ';
            readed_elems = 0;
            (smatrix->rows_start)[row] = i;
            printf("Input elements for row number %d through the gap in format(col_index_1 element_1 col_index_2 element_2):\n", row);
        }
        else
        {
            error_code = INPUT_ERROR;
            printf("Incorrect input. Next time - input numbers of row from low to high\n");
        }

        while (!error_code && temp_char != '\n' && !feof(stdin) && (readed_elems) < smatrix->m && i < smatrix->cnt_non_zero)
        {
            ungetc(temp_char, stdin);
            if (scanf("%d %d", &temp_col, &temp_elem) == 2 && temp_col < smatrix->m && 0 <= temp_col && temp_elem != 0 &&\
                is_col_busy(smatrix->column_for_values, i, temp_col) == -1)
            {
                (smatrix->values)[i] = temp_elem;
                (smatrix->column_for_values)[i] = temp_col;
                i++;
                readed_elems++;
            }
            else
            {
                error_code = INPUT_ERROR;
                printf("Incorrect input. Input non-zero elements according the format\n");
            }
            if (!feof(stdin))
            {
                temp_char = getchar();
            }
        }
    }
    if (i != smatrix->cnt_non_zero)
    {
        error_code = INPUT_ERROR;
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
            smatrix->rows_start[i] = -1;
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

int is_col_busy(int_arr_t arr, int n, int col)
{
    int pos = -1;
    for (int i = 0; i < n; i++)
    {
        if (pos == -1 && arr[i] == col)
        {
            pos = i;
        }
    }

    return pos;
}

int cnt_nonzero_in_row(sparse_matrix *smatrix, int row)
{
    int len = 1;
    if (smatrix->rows_start[row] != -1)
    {
    	// printf("nonzero row start %d ", smatrix->rows_start[row]);
        while (row + len < smatrix->n && smatrix->rows_start[row + len] == -1)
        {
            len += 1;
        }
        // printf("%d \n", len);
        if (row + len == smatrix->n)
        {
            len = smatrix->cnt_non_zero - smatrix->rows_start[row];
        }
        else
        {
            len = smatrix->rows_start[row + len] - (smatrix->rows_start)[row];
        }
    }
    else
    {
        len = 0;
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
        	// printf("\nCnt nonzero %d, col %d, row %d, is_in %d ", cnt_nonzero_in_row(smatrix, i), j, i, is_in(smatrix->column_for_values + smatrix->rows_start[i], cnt_nonzero_in_row(smatrix, i), j));
            pos = is_col_busy(smatrix->column_for_values + smatrix->rows_start[i], cnt_nonzero_in_row(smatrix, i), j);
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
    int cnt_nonzero = 0;
    int error_code = SUCCES;

    change_size_smatrix(sres, matrix_row->n, matrix_row->m, cnt_nonzero);

    int is_zero_row = 0;
    int res = 0;
    for (int i = 0; i < sres->n; i++)
    {
        sres->rows_start[i] = cnt_nonzero;
        is_zero_row = 1;

        for (int j = 0; j < sres->m; j++)
        {
            res = multiply_row_col(matrix_row, smatrix, i, j);
            if (res)
            {
                if (cnt_nonzero == sres->cnt_non_zero)
                {
                    error_code = change_size_smatrix(sres, matrix_row->n, matrix_row->m, cnt_nonzero * 2 + 1);
                }

                is_zero_row = 0;

                cnt_nonzero++;
                (sres->cnt_non_zero)++;
                sres->column_for_values[cnt_nonzero] = j;
                sres->values[cnt_nonzero] = res;
            }
        }

        if (is_zero_row)
        {
            sres->rows_start[i] = -1;
        }
    }

    return error_code;
}

int multiply_row_col(sparse_matrix *matrix_row, sparse_matrix *smatrix, int row, int col)
{
    int res = 0;
    int cur_pos_col_in_row = 0;
    int cur_col_in_row = 0;
    int cur_elem_smatrix_pos = 0;

    for (int i = 0; i < cnt_nonzero_in_row(matrix_row, row); i++)
    {
        cur_pos_col_in_row = (matrix_row->rows_start[row]) + i;
        cur_col_in_row = (matrix_row->column_for_values[cur_pos_col_in_row]);
        if (smatrix->rows_start[cur_col_in_row] != -1)
        {
            cur_elem_smatrix_pos = is_col_busy(smatrix->column_for_values + smatrix->rows_start[cur_col_in_row], cnt_nonzero_in_row(smatrix, cur_col_in_row), col);
            if (cur_elem_smatrix_pos != -1)
            {
                cur_elem_smatrix_pos += smatrix->rows_start[cur_col_in_row];
                res += (matrix_row->values[cur_pos_col_in_row]) * (smatrix->values[cur_elem_smatrix_pos]);
            }
        }
    }

    return res;
}

int is_smatrix_correct(sparse_matrix *smatrix)
{
    return (smatrix && smatrix->n > 0 && smatrix->m > 0);
}