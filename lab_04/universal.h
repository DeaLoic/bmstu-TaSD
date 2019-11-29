#ifndef __UNIVERSAL_H__
#define __UNIVERSAL_H__

#include <inttypes.h>

#define COMPARE_EPS 1E-7
#define DATE_LEN_DOTS 11 // DD.MM.YYYY format  

// universal
void universal_swap(void *first, void *second, size_t size);

// char
int input_string(FILE* f, char* string, int size);
int is_alpha_string(char *string);
int is_date_format(char *date_str);

// int64
int compare_int64(int64_t *first, int64_t *second);
int fscanf_int64(FILE* source, int64_t *elem);
int fprintf_int64(FILE* source, int64_t *elem);

// int
int compare_int(int *first, int *second);
int fscanf_int(FILE* source, int *elem);
int fprintf_int(FILE* source, int *elem);

// double
int compare_double(double *first, double *second);
int summator_double(double *increased, double *added);
int fscanf_double(FILE* source, double *elem);
int fprintf_double(FILE* source, double *elem);

uint64_t tick(void);

#endif