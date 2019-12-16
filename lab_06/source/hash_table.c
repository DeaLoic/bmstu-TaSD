#include "hash_table.h"
#include "error_codes.h"
#include "array.h"

void create_hash_table(hash_table_t *hash, int size, int base)
{
    if (hash)
    {
        hash->basis = base;
        hash->fill = 0;
        hash->size = size;
        hash->body = NULL;
        create_array(&(hash->body), size, sizeof(int *));
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

int add_to_hash_table(hash_table_t *hash, int *element)
{
    int insert_index = -1;
    if (hash && hash->basis > 0)
    {
        if (hash->fill == hash->size)
        {
            change_size_array(&(hash->body), hash->size * 2 + 1, sizeof(int*));
            for (int i = hash->size; i < hash->size * 2 + 1; i++)
            {
                (hash->body)[i] = NULL;
            }
            hash->size = hash->size * 2 + 1;
        }

        insert_index = *element % hash->basis;
        while (hash->body[insert_index] != NULL)
        {
            insert_index++;
            insert_index %= hash->basis;
        }

        (hash->body)[insert_index] = element;

        hash->fill += 1;
        
    }

    return insert_index;
}

int find_element_in_hash_table(hash_table_t *hash, int *element)
{
    int insert_index = -1;
    if (hash)
    {
        insert_index = *element % hash->basis;
        while (hash->body[insert_index] != NULL && *(hash->body[insert_index]) != *element && insert_index > 0)
        {
            insert_index++;
            insert_index %= hash->basis;
            if (insert_index == *element % hash->basis)
            {
                insert_index = -1;
            }
        }
    }

    return insert_index;
}

void change_basis(hash_table_t *hash, int basis)
{
    hash_table_t *new_hash;
    create_hash_table(new_hash, hash->fill > basis ? hash->fill * 2 + 1 : basis, basis);
    for (int i = 0; i < hash->size; i++)
    {
        if (hash->body[i])
        {
            add_to_hash_table(new_hash, hash->body[i]);
        }
    }

    delete_hash_table(hash);
    hash->basis = basis;
    hash->body = new_hash->body;
    hash->fill = new_hash->fill;
    hash->size = new_hash->size;
}

int parse_file_hash_table(hash_table_t *hash, FILE *source)
{
    int *cur_digit = (int*)malloc(sizeof(int));
    while (fscanf(source, "%d", cur_digit) == 1)
    {
        add_to_hash_table(hash, cur_digit);
        cur_digit = (int*)malloc(sizeof(int));
    }
    free(cur_digit);
}