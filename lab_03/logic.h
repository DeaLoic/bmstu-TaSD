#ifndef __LOGIC_H__

#include "matrix.h"
#include "sparse_matrix.h"

int sparse_to_classic_matrix(sparse_matrix *smatrix, matrix_t *matrix);
int create_random_smatrix(sparse_matrix *smatrix, int n, int m, int percent_of_sparsed);
int cnt_time(int side, int percent);
int compare_time(int side, int percent);

#endif