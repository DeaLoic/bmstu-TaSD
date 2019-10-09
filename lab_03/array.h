#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <inttypes.h>
#include <stdio.h>

typedef double *dbl_arr_t;
typedef int *int_arr_t;
typedef long int *lint_arr_t;
typedef int64_t *llint_arr_t;

// CDIO
int create_array(void *array_p, int size, size_t size_elem);
void delete_array(void *array_p);
int input_array(void *array, int size, size_t elem_size, FILE* source, int (*fscanf_elem)(FILE*, void*));
int print_array(void *array, int size, size_t size_elem, FILE* dest, void (*fprintf_elem)(FILE*, void*));

// Base handler
int move_to_end(void *array, int size, size_t size_elem, int index);
int change_size_array(void *array_p, int new_size, size_t size_elem);
int insert_to_position(void *array, int size, size_t size_elem, void *value, int pos);

// Complex handler
// return position of max elem
int max_in_array(void *array, int size, size_t elem_size, int (*compare)(void*, void*));

// Inline check
int is_array_correct(void *array, int size);
int is_position_correct_arr(int size, int pos);


#endif