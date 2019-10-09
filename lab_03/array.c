#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include "array.h"
#include "error_codes.h"
#include "universal.h"

// CDIO
// Create array
int create_array(void *array_p, int size, size_t size_elem)
{
    int error_code = INCORRECT_INPUT;
    if (size > 0)
    {
        error_code = SUCCES;

        void *new_double_array = calloc(size, size_elem);

        memmove(array_p, &new_double_array, sizeof(void*));
        if (!new_double_array)
        {
            error_code = CREATE_ERROR;
        }
    }

    return error_code;
}

// Delete array
void delete_array(void *array_p)
{
    void *null_pointer = NULL;
    free(*(char**)array_p);
    memmove(array_p, &null_pointer, sizeof(void*));
}

// Enter array
int input_array(void *array, int size, size_t elem_size, FILE* source, int (*fscanf_elem)(FILE*, void*))
{
    int error_code = INCORRECT_INPUT;

    if (is_array_correct(array, size))
    {
        error_code = SUCCES;
        int i = 0;
        while (!feof(source) && i < size && (fscanf_elem(source, (char*)array + i * elem_size) == 1))
        {
            i++;
        }

        if (i != size)
        {
            error_code = INPUT_ERROR;
        }
    }

    return error_code;
}

// Print array
int print_array(void *array, int size, size_t size_elem, FILE* dest, void (*fprintf_elem)(FILE*, void*))
{
    int error_code = INCORRECT_INPUT;

    if (is_array_correct(array, size))
    {
        error_code = SUCCES;

        fprintf_elem(dest, array);
        int i = 1;
        while (i < size)
        {
            fprintf(dest, " ");
            fprintf_elem(dest, (char*)array + i * size_elem);
            i++;
        }
        printf("\n");
    }

    return error_code;
}

// Move to end
int move_to_end(void *array, int size, size_t size_elem, int index)
{
    int error_code = INCORRECT_INPUT;

    if (is_array_correct(array, size) && is_position_correct_arr(size, index))
    {
        error_code = SUCCES;

        void *cur_element = malloc(size_elem);
        memmove(cur_element, (char*)array + index * size_elem, size_elem);

        while ((index + 1) < size)
        {
            memmove((char*)array + index * size_elem, (char*)array + (index + 1) * size_elem, size_elem);
            index++;
        }
        memmove((char*)array + index * size_elem, cur_element, size_elem);
        free(cur_element);
    }

    return error_code;
}

// Change size
int change_size_array(void *array_p, int new_size, size_t size_elem)
{
    int error_code = MEMORY_ERROR;

    void *new_array_head = realloc(*(char**)array_p, new_size * size_elem);

    if (new_array_head)
    {
        error_code = SUCCES;
        memmove(array_p, &new_array_head, sizeof(void*));
    }

    return error_code;
}

// Insert to position
int insert_to_position(void *array, int size, size_t size_elem, void *value, int pos)
{
    int error_code = INCORRECT_INPUT;
    if (is_array_correct(array, size) && is_position_correct_arr(size, pos))
    {
        error_code = SUCCES;

        size--;
        while (size != pos)
        {
            memmove((char*)array + (size - 1) * size_elem, (char*)array + size * size_elem, size_elem);
            size--;
        }
        memmove((char*)array + pos * size_elem, value, sizeof(size_elem));
    }

    return error_code;
}

int max_in_array(void *array, int size, size_t elem_size, int (*compare)(void*, void*))
{
    char **temp_max = malloc(sizeof(void*));
    *temp_max = array;
    int pos = 0;

    for (int i = 1; i < size; i++)
    {
        if (compare((char*)array + i * elem_size, *temp_max) > 0)
        {
            pos = i;
            *temp_max = (char*)array + i * elem_size;
        }
    }
    free(temp_max);

    return pos;
}

// Is array correct
int is_array_correct(void *array, int size)
{
    return (array && (size > 0));
}

// Is possition correct
int is_position_correct_arr(int size, int pos)
{
    return (pos >= 0 && (pos < size));
}
