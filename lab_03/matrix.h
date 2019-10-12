#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdint.h>
#include <inttypes.h>
#include "array.h"

typedef int_arr_t *matrix_body;

typedef struct
{
    matrix_body body;
    int n;
    int m;
} matrix_t;

// I/O
int create_matrix(matrix_t *matrix, int n, int m);
void delete_matrix(matrix_t *matrix);
int input_matrix(matrix_t *matrix);
int input_non_zero(matrix_t *matrix, int *non_zero_elems);

void output_matrix(matrix_t *matrix);
int is_input_size_matrix(int *n, int *m);
int create_input_matrix(matrix_t *matrix);

int matrix_cpy(matrix_t *source, matrix_t *dest);

int set_zero_matrix(matrix_t *matrix);
int set_unit_matrix(matrix_t *matrix);
int init_null_matrix(matrix_t *matrix);
int initialize_matrix(matrix_t *matrix);

// Row Handler
int delete_row(matrix_t *matrix, int index_to_delete);
int add_row(matrix_t *matrix);
int swap_row(matrix_t *matrix, int first_row_index, int second_row_index);
int move_row_to_end(matrix_t *matrix, int row_index);
int insert_row(matrix_t *matrix, int_arr_t row_to_insert, int pos);

// Column handler
// base
int delete_col(matrix_t *matrix, int index_to_delete);
int add_col(matrix_t *matrix);
int swap_col(matrix_t *matrix, int first_row_index, int second_row_index);
int move_col_to_end(matrix_t *matrix, int col_index);
int insert_col(matrix_t *matrix, int_arr_t col_to_insert, int pos);

// Full matrix handler
int find_min_by_col(matrix_t *matrix, int *rowres, int *colres);
int scalar_multiply_row_col(matrix_t *first_matrix, matrix_t *second_matrix, int row, int col);

int multiply_matrix(matrix_t *first_matrix, matrix_t *second_matrix, matrix_t *res);
int pow_matrix(matrix_t *matrix, matrix_t *res, int power);

int is_matrix_correct(matrix_t *matrix);
int is_matrix_square(matrix_t *matrix);
int is_position_correct(int size, int pos);
#endif