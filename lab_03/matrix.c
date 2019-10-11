#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>
#include "error_codes.h"
#include "matrix.h"
#include "array.h"
#include "universal.h"

int is_input_size_matrix(int *n, int *m)
{
    return (fscanf(stdin, "%d", n) == 1) && (fscanf(stdin, "%d", m) == 1) && *n > 0 && *m > 0;
}

int create_matrix(matrix_t *matrix, int n, int m)
{
    int error_code = INCORRECT_INPUT;

    if (n > 0 && m > 0)
    {
        error_code = SUCCES;
        matrix->body = (matrix_body)calloc(n, sizeof(int_arr_t));
        if (matrix->body)
        {
            matrix->n = n;
            matrix->m = m;

            int i = 0;
            while (i < n && !error_code)
            {   
                error_code = create_array(matrix->body + i, m, sizeof(int));
                i++;
            }

            if (error_code)
            {
                error_code = CREATE_ERROR;
                delete_matrix(matrix);
            }
        }
        else
        {
            error_code = CREATE_ERROR;
        }
    }

    return error_code;
}

void delete_matrix(matrix_t *matrix)
{
    if (is_matrix_correct(matrix))
    {
        for (int i = 0; i < matrix->n; i++)
        {
            delete_array(matrix->body + i);
        }
        free(matrix->body);
        matrix->body = NULL;
        matrix->n = 0;
        matrix->m = 0;
    }
}

int init_null_matrix(matrix_t *matrix)
{
    matrix->body = NULL;
    matrix->n = 0;
    matrix->m = 0;

    return SUCCES;
}

int initialize_matrix(matrix_t *matrix)
{
    int error_code = SUCCES;

    for (int i = 0; i < matrix->n; i++)
    {
        for (int j = 0; j < matrix->m; j++)
        {
            (matrix->body)[i][j] = i + j;
            (matrix->body)[i][j] = (matrix->body)[i][j];
        }
    }

    return error_code;
}

int set_zero_matrix(matrix_t *matrix)
{
    int error_code = INCORRECT_INPUT;

    if (is_matrix_correct(matrix))
    {
        error_code = SUCCES;

        for (int i = 0; i < matrix->n; i++)
        {
            for (int j = 0; j < matrix->m; j++)
            {
                (matrix->body)[i][j] = 0;
            }
        }
    }
    return error_code;
}

int set_unit_matrix(matrix_t *matrix)
{
    int error_code = INCORRECT_INPUT;

    if (is_matrix_correct(matrix))
    {
        error_code = SUCCES;

        set_zero_matrix(matrix);
        for (int i = 0; i < matrix->n; i++)
        {
            (matrix->body)[i][i] = 1;
        }
    }

    return error_code;
}

int matrix_cpy(matrix_t *source, matrix_t *dest)
{
    int error_code = INCORRECT_INPUT;

    if (is_matrix_correct(source) && is_matrix_correct(dest))
    {
        error_code = SUCCES;

        for (int i = 0; i < source->n; i++)
        {
            for (int j = 0; j < source->m; j++)
            {
                (dest->body)[i][j] = (source->body)[i][j];
            }
        }
    }

    return error_code;
}

int input_matrix(matrix_t *matrix)
{
    int error_code = SUCCES;
    int i = 0;

    while (i < matrix->n && !error_code)
    {
        error_code = input_array((matrix->body)[i], matrix->m, sizeof(int), stdin, (int (*)(FILE*, void*))fscanf_int64);
        i++;
    }

    return error_code;
}

int create_input_matrix(matrix_t *matrix)
{
    int error_code = INPUT_ERROR;

    int n, m;

    if (is_input_size_matrix(&n, &m))
    {
        error_code = SUCCES;
        error_code = create_matrix(matrix, n, m);
        if (!error_code)
        {
            error_code = input_matrix(matrix);
        }
    }

    return error_code;
}

void output_matrix(matrix_t *matrix)
{
    for (int i = 0; i < matrix->n; i++)
    {
        print_array((matrix->body)[i], matrix->m, sizeof(int), stdout, (void (*)(FILE*, void*))fprintf_int64);
    }
}


int delete_row(matrix_t *matrix, int index_to_delete)
{
    int error_code = INCORRECT_INPUT;

    if (is_position_correct(matrix->n, index_to_delete) && matrix->n > 1)
    {
        error_code = SUCCES;

        int_arr_t temp_arr = (matrix->body)[index_to_delete];
        move_row_to_end(matrix, index_to_delete);

        matrix_body new_body = (matrix_body)realloc(matrix->body, sizeof(int_arr_t) * (matrix->n - 1));

        if (new_body)
        {
            matrix->body = new_body;
            free(temp_arr);
            (matrix->n)--;
        }
        else
        {
            error_code = MEMORY_ERROR;
            insert_row(matrix, temp_arr, index_to_delete);
        }
    }
    
    return error_code;
}

int add_row(matrix_t *matrix)
{
    int error_code = INCORRECT_INPUT;

    if (is_matrix_correct(matrix))
    {
        error_code = SUCCES;

        matrix_body new_body = (matrix_body)realloc(matrix->body, sizeof(int_arr_t) * (matrix->n + 1));
        int_arr_t temp_array = NULL;
        create_array(&temp_array, matrix->m, sizeof(int));
        
        if (new_body && temp_array)
        {
            matrix->body = new_body;
            (matrix->body)[matrix->n] = temp_array;
            (matrix->n)++;
        }
        else
        {
            delete_array(&temp_array);
            delete_array(&new_body);
            error_code = MEMORY_ERROR;
        }
    }

    return error_code;
}

int swap_row(matrix_t *matrix, int first_row_index, int second_row_index)
{
    int error_code = INCORRECT_INPUT;
    if (is_position_correct(matrix->n, first_row_index) && is_position_correct(matrix->n, second_row_index)\
        && is_matrix_correct(matrix))
    {
        error_code = SUCCES;
        universal_swap(matrix->body + first_row_index, matrix->body + second_row_index, sizeof((matrix->body)[first_row_index]));
    }

    return error_code;
}

int move_row_to_end(matrix_t *matrix, int row_index)
{
    int error_code = INCORRECT_INPUT;

    if (is_matrix_correct(matrix) && is_position_correct(matrix->n, row_index))
    {
        error_code = SUCCES;
        int_arr_t temp_arr = (matrix->body)[row_index];

        for (int i = row_index; i + 1 < matrix->n; i++)
        {
            (matrix->body)[i] = (matrix->body)[i + 1];
        }
        (matrix->body)[matrix->n - 1] = temp_arr;
    }

    return error_code;
}

int insert_row(matrix_t *matrix, int_arr_t row_to_insert, int pos)
{
    int error_code = INCORRECT_INPUT;

    if (is_matrix_correct(matrix) && is_position_correct(matrix->n, pos))
    {
        error_code = SUCCES;

        for (int i = matrix->n - 1; i > pos; i--)
        {
            (matrix->body)[i] = (matrix->body)[i - 1];
        }
        (matrix->body)[pos] = row_to_insert;
    }

    return error_code;   
}


// collumn funcs
int delete_col(matrix_t *matrix, int index_to_delete)
{
    int error_code = INCORRECT_INPUT;

    if (is_position_correct(matrix->m, index_to_delete) && is_matrix_correct(matrix) && matrix->m > 1)
    {
        error_code = SUCCES;

        for (int i = 0; i < matrix->n && !error_code; i++)
        {
            move_to_end((matrix->body)[i], matrix->m, sizeof((matrix->body)[0][0]), index_to_delete);
            error_code = change_size_array(matrix->body + i, matrix->m - 1, sizeof((matrix->body)[0][0]));
        }
        if (!error_code)
        {
            (matrix->m)--;
        }
    }
    
    return error_code;
}

int add_col(matrix_t *matrix)
{
    int error_code = INCORRECT_INPUT;
    if (is_matrix_correct(matrix))
    {
        error_code = SUCCES;

        for (int i = 0; i < matrix->n && !error_code; i++)
        {
            error_code = change_size_array(matrix->body + i, matrix->m + 1, sizeof((matrix->body)[0][0]));
            if (!error_code)
            {
                (matrix->body)[i][matrix->m] = 0;
            }
        }
        if (!error_code)
        {
            (matrix->m)++;
        }
    }
    
    return error_code;
}

int swap_col(matrix_t *matrix, int first_col_index, int second_col_index)
{
    int error_code = INCORRECT_INPUT;

    if (is_matrix_correct(matrix) && is_position_correct(matrix->m, first_col_index)\
        && is_position_correct(matrix->m, second_col_index))
    {
        error_code = SUCCES;

        for (int i = 0; i < matrix->n; i++)
        {
            universal_swap((matrix->body)[i] + first_col_index, (matrix->body)[i] + second_col_index,
            sizeof((matrix->body)[i][first_col_index]));
        }
    }
    
    return error_code;
}

int move_col_to_end(matrix_t *matrix, int col_index)
{
    int error_code = INCORRECT_INPUT;
    if (is_matrix_correct(matrix) && is_position_correct(matrix->m, col_index))
    {
        error_code = SUCCES;

        for (int i = 0; i < matrix->n; i++)
        {
            move_to_end((matrix->body)[i], matrix->m, sizeof((matrix->body)[0][0]), col_index);
        }
    }
    
    return error_code;
}

int insert_col(matrix_t *matrix, int_arr_t col_to_insert, int pos)
{
    int error_code = INCORRECT_INPUT;
    if (is_matrix_correct(matrix) && is_position_correct(matrix->m, pos) && col_to_insert)
    {
        error_code = SUCCES;

        for (int i = 0; i < matrix->m; i++)
        {
            insert_to_position((matrix->body)[i], matrix->m, sizeof((matrix->body)[0][0]), col_to_insert + i, pos);
        }
    }
    
    return error_code;
}

int find_min_by_col(matrix_t *matrix, int *rowres, int *colres)
{
    int error_code = INCORRECT_INPUT;

    if (is_matrix_correct(matrix))
    {
        error_code = SUCCES;

        int min_el = (matrix->body)[0][0];
        *rowres = 0;
        *colres = 0;

        for (int j = 0; j < matrix->m; j++)
        {
            for (int i = 0; i < matrix->n; i++)
            {
                if ((matrix->body)[i][j] < min_el)
                {
                    min_el = (matrix->body)[i][j];
                    *rowres = i;
                    *colres = j;
                }
            }
        }
    }

    return error_code;
}

int scalar_multiply_row_col(matrix_t *first_matrix, matrix_t *second_matrix, int row, int col)
{
    int result = 0;

    for (int i = 0; i < first_matrix->n; i++)
    {
        result += ((first_matrix->body)[row][i] * (second_matrix->body)[i][col]);
    }

    return result;
}

int multiply_matrix(matrix_t *first_matrix, matrix_t *second_matrix, matrix_t *res)
{
    for (int i = 0; i < res->n; i++)
    {
        for (int j = 0; j < res->n; j++)
        {
            (res->body)[i][j] = scalar_multiply_row_col(first_matrix, second_matrix, i, j);
        }
    }

    return SUCCES;
}

int pow_matrix(matrix_t *matrix, matrix_t *res, int power)
{
    int error_code = SUCCES;

    matrix_cpy(matrix, res);

    if (!power)
    {
        set_unit_matrix(res);
        for (int i = 0; i < res->n; i++)
        {
            (res->body)[i][i] = 1;
        }
    }
    else if (power > 1)
    {
        matrix_t temp_res;
        create_matrix(&temp_res, matrix->n, matrix->n);

        for (int i = 1; i < power; i++)
        {   
            multiply_matrix(res, matrix, &temp_res);
            matrix_cpy(&temp_res, res);
        }

        delete_matrix(&temp_res);
    }
    
    return error_code;
}

int is_matrix_correct(matrix_t *matrix)
{
    return matrix->body && (matrix->n > 0) && (matrix->m > 0);
}

int is_position_correct(int size, int pos)
{
    return (pos >= 0) && (pos < size);
}