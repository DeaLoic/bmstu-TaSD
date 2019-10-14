#ifndef __SPARSE_MATRIX_H__
#define __SPARSE_MATRIX_H__

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "array.h"

typedef struct
{
	int_arr_t values; 
	int_arr_t column_for_values;
	int_arr_t rows_start;
	int cnt_non_zero;
	int n;
	int m;
} sparse_matrix;

//CDIO
int set_null_matrix(sparse_matrix *smatrix);
int delete_smatrix_content(sparse_matrix *smatrix);
int input_smatrix(sparse_matrix *smatrix);
int input_smatrix_row(sparse_matrix *matrix_row);
int print_smatrix_pretty(sparse_matrix *smatrix);
int print_smatrix_source(sparse_matrix *smatrix);


int change_size_smatrix(sparse_matrix *smatrix, int n, int m, int non_zero);

int multiply_matrix_row(sparse_matrix *matrix_row, sparse_matrix *smatrix, sparse_matrix *sres);
int multiply_row_col(sparse_matrix *matrix_row, sparse_matrix *smatrix, int row, int col);

int find_col_index(int_arr_t arr, int n, int col);
int cnt_nonzero_in_row(sparse_matrix *smatrix, int row);
int is_smatrix_correct(sparse_matrix *smatrix);

#endif