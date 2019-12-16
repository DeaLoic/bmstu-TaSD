#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include "array.h"

typedef struct hash_table_t
{
    int **body;
    int basis;
    int size;
    int fill;
} hash_table_t;

void create_hash_table(hash_table_t *hash, int size, int base);
void delete_hash_table(hash_table_t *hash);

int add_to_hash_table(hash_table_t *hash, int *element);
int find_element_in_hash_table(hash_table_t *hash, int *element);
void change_basis(hash_table_t *hash, int basic);

int parse_file_hash_table(hash_table_t *hash, FILE *source);

#endif