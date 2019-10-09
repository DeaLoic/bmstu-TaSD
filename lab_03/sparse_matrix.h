#ifndef __SPARSE_MATRIX_H__
#define __SPARSE_MATRIX_H__

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <array.h>

typedef struct
{
	int64_t *values; 
	int *column_for_values;
	int *rows_start;
	int n;
	int m;
} sparse_matrix;

//CDIO
int create_smatrix(sparse_matrix *smatrix);
int delete_matrix(sparse_matrix *smatrix);
int input_matrix(sparse_matrix *smatrix, FILE *source);
int print_matrix(sparse_matrix *smatrix);