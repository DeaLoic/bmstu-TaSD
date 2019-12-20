#include <stdlib.h>
#include "hash_table.h"
#include "error_codes.h"
#include "array.h"
#include "universal.h"

int hash_func(hash_table_t *hash, int element)
{
    int res = -1;
    if (hash && hash->basis > 0)
    {
        res = element % hash->basis;
    }

    return res;
}
void create_hash_table(hash_table_t *hash, int size, int base)
{
    if (hash)
    {
        hash->basis = base;
        hash->fill = 0;
        hash->size = size;
        hash->body = NULL;
        create_array(&(hash->body), hash->size, sizeof(int *));
    }
}

void delete_hash_table(hash_table_t *hash)
{
    if (hash)
    {
        delete_array(&(hash->body));
        hash->fill = 0;
        hash->size = 0;
        hash->basis = 1;
    }
}

int add_to_hash_table(hash_table_t *hash, int *element, int *comp_times, int max_conflict)
{
    int insert_index = -1;
    if (hash)
    {
        *comp_times = 1;
        if (hash->fill == hash->size)
        {
            change_basis(hash, get_next_prime(hash->basis * 2));
        }

        insert_index = hash_func(hash, *element);
        int start_ins = insert_index;
        int is_in = 0;
        int k = 0;
        while (hash->body[insert_index] != NULL)
        {
            if (*(hash->body[insert_index]) == *element)
            {
                is_in = 1;
                break;
            }
            if ((k && insert_index == start_ins) || ((max_conflict > 0) && (k + 1) == max_conflict))
            {
                change_basis(hash, get_next_prime(hash->basis * 2));
                add_to_hash_table(hash, element, comp_times, max_conflict);
            }
            *comp_times += 2;

            insert_index = ((insert_index + HASH_STEP) % hash->size);
            k++;
        }

        if (is_in)
        {
            return -1;
        }

        (hash->body)[insert_index] = element;

        hash->fill += 1;
        
    }

    return insert_index;
}

int find_element_in_hash_table(hash_table_t *hash, int *element, int *cmp)
{
    *cmp = 1;
    int insert_index = -1;
    if (hash)
    {
        insert_index = *element % hash->basis;
        int start_index = insert_index;
        int k = 0;
        while (hash->body[insert_index] != NULL && *(hash->body[insert_index]) != *element && insert_index > 0)
        {
            *cmp += 2;
            k++;
            insert_index = ((insert_index + HASH_STEP) % hash->size);
            if (insert_index == start_index)
            {
                insert_index = -1;
            }
        }

        if (hash->body[insert_index] == NULL)
        {
            insert_index = -1;
        }
    }

    return insert_index;
}

void change_basis(hash_table_t *hash, int basis)
{
    hash_table_t new_hash;
    int cmp = 0;
    create_hash_table(&new_hash, basis, basis);
    for (int i = 0; i < hash->size; i++)
    {
        if (hash->body[i])
        {
            add_to_hash_table(&new_hash, hash->body[i], &cmp, -1);
        }
    }

    delete_hash_table(hash);
    hash->basis = basis;
    hash->body = new_hash.body;
    hash->fill = new_hash.fill;
    hash->size = new_hash.size;
}

int parse_file_hash_table(hash_table_t *hash, FILE *source)
{
    int error_code = INCORRECT_INPUT;
    int cmp = 0;
    int *cur_digit = (int*)malloc(sizeof(int));
    while (fscanf(source, "%d", cur_digit) == 1)
    {
        error_code = SUCCES;
        add_to_hash_table(hash, cur_digit, &cmp, -1);
        cur_digit = (int*)malloc(sizeof(int));
    }
    free(cur_digit);
    return error_code;
}

int print_hash_table(hash_table_t *hash)
{
    int error_code = INCORRECT_INPUT;
    if (hash)
    {
        error_code = SUCCES;
        printf("INDEX         VALUE         KEY\n");
        error_code = SUCCES;
        for (int i = 0; i < hash->size; i++)
        {
            if (hash->body[i] != NULL)
            {
                printf("%8d | %8d | %8d\n", i, *(hash->body[i]), *(hash->body[i]) % hash->basis);
            }
            else
            {
                printf("%8d | %8p | %8p\n", i, hash->body[i], hash->body[i]);
            }
            
        }
    }

    return error_code;
}