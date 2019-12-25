#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include "error_codes.h"
#include "universal.h"


void add_to_file(FILE *file, int element)
{
    fseek(file, SEEK_END, 0);
    fprintf(file, "%d", element);
}

int get_next_prime(int number)
{
    while (1)
    {
        int count_del = 0;
        number++;
        for(int i = 2; i < number - 1; i++)
            if (!(number%i))
                count_del++;

        if (!count_del)
            return number;
    }
}


int int_compare(void* first, void *second)
{
    int result = 0;
    int first_i = *((int*)first);
    int second_i = *((int*)second);

    if (first_i < second_i)
    {
        result = -1;
    }
    else if (first_i > second_i)
    {
        result = 1;
    }

    return result;
}

void print_int(void *first)
{
    int first_i = *((int *)first);
    printf("%d", first_i);
}

// universal
void universal_swap(void *first, void *second, size_t size)
{
    void *buf = malloc(size);
    if (buf)
    {
        memcpy(buf, first, size);
        memcpy(first, second, size);
        memcpy(second, buf, size);
        free(buf);
    }
}

// size with zero-byte
int input_string(FILE *f, char *string, int size)
{
    int error_code = INCORRECT_INPUT;
    if (string && f && size >= 0)
    {
        error_code = SUCCES;

        if (fgets(string, size, f) == NULL)
        {
            error_code = INPUT_ERROR;
        }
        else
        {
            if (strlen(string) == size - 1 && (string[size - 2] != '\n') && !feof(f))
            {
                int temp_char = fgetc(f);
                if (temp_char != '\n')
                {
                    ungetc(temp_char, f);
                    error_code = EOL_UNREACHED;
                }
            }
            string[strcspn(string, "\n")] = '\0';
        }
    }

    return error_code;
}

int is_alpha_string(char *string)
{
    int exit_code = 0;
    if (string)
    {
        exit_code = 1;
        int i = 0;
        while (exit_code && string[i] != '\0')
        {
            if (!isalpha(string[i]))
            {
                exit_code = 0;
            }
            i++;
        }
    }

    return exit_code;
}

// int64
int compare_int64(int64_t *first, int64_t *second)
{
    int exit_code = -1;
    if (*first == *second)
    {
        exit_code = 0;
    }
    else if (*first > *second)
    {
        exit_code = 1;
    }

    return exit_code;
}

int fscanf_int64(FILE* source, int64_t *elem)
{
    return fscanf(source, "%" SCNd64, elem);
}

int fprintf_int64(FILE* source, int64_t *elem)
{
    return fprintf(source, "%" PRId64, *elem);
}

// int
int compare_int(int *first, int *second)
{
    int exit_code = -1;
    if (*first == *second)
    {
        exit_code = 0;
    }
    else if (*first > *second)
    {
        exit_code = 1;
    }

    return exit_code;
}

int fprintf_int(FILE* source, int *elem)
{
    return fprintf(source, "%d", *elem);
}

int fscanf_int(FILE* source, int *elem)
{
    return fscanf(source, "%d", elem);
}

// double
int compare_double(double *first, double *second)
{
    int exit_code = -1;
    if (fabs(*first - *second) < COMPARE_EPS)
    {
        exit_code = 0;
    }
    else if (*first - *second > COMPARE_EPS)
    {
        exit_code = 1;
    }

    return exit_code;
}

int summator_double(double *increased, double *added)
{
    int error_code = INCORRECT_INPUT;
    if (increased && added)
    {
        error_code = SUCCES;
        *increased += *added;
    }

    return error_code;
}

int fscanf_double(FILE* source, double *elem)
{
    return fscanf(source, "%lf", elem);
}

int fprintf_double(FILE* source, double *elem)
{
    return fprintf(source, "%lf", *elem);
}