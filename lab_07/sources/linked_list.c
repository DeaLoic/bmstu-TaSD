#include <stdlib.h>
#include "linked_list.h"
#include "error_codes.h"

int is_index_correct(linked_list_t *list, int index);

linked_list_node_t *create_node(void *data)
{
    linked_list_node_t *new_node = (linked_list_node_t *)malloc(sizeof(linked_list_node_t));

    if (new_node)
    {
        set_null_node(new_node);
        new_node->data = data;
    }

    return new_node;
}

void set_null_node(linked_list_node_t *node)
{
    if (node)
    {
        node->data = NULL;
        node->next_node = NULL;
    }
}

void delete_node(linked_list_node_t *node, void destructor(void*))
{
    if (node)
    {
        destructor(node->data);
    }
    free(node);
}

/*  List  */

void set_null_list(linked_list_t *list)
{
    if (list)
    {
        list->head = NULL;
        list->tail = NULL;
        list->size = 0;
    }
}

int copy_linked_list(linked_list_t *dest, linked_list_t *source)
{
    set_null_list(dest);
    void *res;
    for (int i = 0; i < source->size; i++)
    {
        res = get_element(source, i);
        add_element(dest, res);
    }

    return SUCCES;
}

int add_element(linked_list_t *list, void *data)
{
    int error_code = INCORRECT_INPUT;
    if (is_list_correct(list))
    {
        error_code = MEMORY_ERROR;
        if (is_list_not_empty(list))
        {
            list->tail->next_node = create_node(data);
            if (list->tail->next_node)
            {
                error_code = SUCCES;
                list->tail = list->tail->next_node;
                list->size += 1;
            }
        }
        else
        {
            list->head = create_node(data);
            if (list->head)
            {
                error_code = SUCCES;
                list->tail = list->head;
                list->size += 1;
            }
        }
    }

    return error_code;
}

/*
   if index_to_delete out of range - situation is correct and list doesnt change;
   negative indexes interpretation - out of range
*/
int del_element(linked_list_t *list, int index_to_delete, void destructor(void*))
{
    int error_code = INCORRECT_INPUT;
    if (is_list_correct(list))
    {
        linked_list_node_t *temp_node = list->head;
        linked_list_node_t *deleting_node = NULL;
        error_code = SUCCES;
        if (index_to_delete == 0 && list->size == 1)
        {
            delete_node(list->head, destructor);
            set_null_list(list);
        }
        else if (index_to_delete == 0 && list->size > 1)
        {
            temp_node = list->head;
            list->head = list->head->next_node;
            list->size -= 1;
            delete_node(temp_node, destructor);
        }
        else if (index_to_delete > 0 && index_to_delete < list->size)
        {
            for (int i = 1; i < index_to_delete; i++)
            {
                temp_node = temp_node->next_node;
            }            
            deleting_node = temp_node->next_node;

            temp_node->next_node = deleting_node->next_node;
            delete_node(deleting_node, destructor);
            list->size -= 1;
            
            if (temp_node->next_node == NULL)
            {
                list->tail = temp_node;
            }
        }
    }

    return error_code;
}


void *get_element(linked_list_t *list, int index)
{
    void *result = NULL;
    if (is_list_correct(list) && index < list->size)
    {
        linked_list_node_t *temp_node = list->head;
        for (int i = 0; i < index; i++)
        {
            temp_node = temp_node->next_node;
        }

        if (temp_node)
        {
            result = temp_node->data;
        }
    }

    return result;
}

int delete_linked_list(linked_list_t *list, void destructor(void*))
{
    int error_code = INCORRECT_INPUT;
    if (is_list_correct(list))
    {
        error_code = SUCCES;
        int source_size = list->size;
        for (int i = 0; i < source_size; i++)
        {
            del_element(list, 0, destructor);
        }
        set_null_list(list);
    }

    return error_code;
}

int cut_linked_list(linked_list_t *list, int new_size, void destructor(void*))
{
    int error_code = INCORRECT_INPUT;

    if (is_list_correct(list) && is_index_correct(list, new_size))
    {
        error_code = SUCCES;
        if (new_size == 0)
        {
            delete_linked_list(list, destructor);
        }
        else
        {
            linked_list_node_t *temp_node = list->head;
            linked_list_node_t *deleting_node = list->head;
            for (int i = 1; i < new_size; i++)
            {
                temp_node = temp_node->next_node;
            }
            list->tail = temp_node;
            deleting_node = temp_node->next_node;

            for (int i = 0; i < list->size - new_size; i++)
            {
                temp_node = deleting_node->next_node;
                delete_node(deleting_node, destructor);
                deleting_node = temp_node;
            }
            list->tail->next_node = NULL;
        }

        list->size = new_size;
    }

    return error_code;
}

// set second list null
int cat_linked_list(linked_list_t *first, linked_list_t *second)
{
    int error_code = INCORRECT_INPUT;
    if (is_list_correct(first) && is_list_correct(second))
    {
        error_code = SUCCES;
        if (is_list_not_empty(second))
        {
            if (is_list_empty(first))
            {
                first->head = second->head;
                first->tail = second->tail;
                first->size = second->size;
            }
            else
            {
                first->tail->next_node = second->head;
                first->tail = second->tail;
                first->size += second->size;
            }

            set_null_list(second);
        }
    }

    return error_code;
}

int is_list_correct(linked_list_t *list)
{
    return is_list_not_empty(list) || is_list_empty(list);
}

int is_list_not_empty(linked_list_t *list)
{
    return list && list->size > 0 && list->head && list->tail;
}
int is_list_empty(linked_list_t *list)
{
    return list && !(list->size) && !(list->head) && !(list->tail);
}

int is_index_correct(linked_list_t *list, int index)
{
    return list && list->size > 0 && index < list->size && index >= 0;
}