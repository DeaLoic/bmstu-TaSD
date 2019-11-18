#include <stdio.h>
#include <stdlib.h>
#include "queue_list.h"
#include "error_codes.h"

int create_queue_node(queue_node_t **node)
{
    int error_code = INCORRECT_INPUT;
    if (node)
    {
        error_code = MEMORY_ERROR;
        *node = (queue_node_t*)malloc(sizeof(queue_node_t));
        if (*node)
        {
            error_code = SUCCES;
            set_null_queue_node(*node);
        }
    }

    return error_code;
}

int delete_queue_node(queue_node_t **node)
{
    int error_code = INCORRECT_INPUT;
    if (node)
    {
        error_code = SUCCES;
        free(*node);
        *node = NULL;
    }

    return error_code;
}

int set_null_queue_node(queue_node_t *node)
{
    int error_code = INCORRECT_INPUT;
    if (node)
    {
        node->data = NULL;
        node->prev_node = NULL;
    }

    return error_code;
}

int set_null_queue_list(queue_list_t *queue)
{
    int error_code = INCORRECT_INPUT;
    if (queue)
    {
        error_code = SUCCES;
        queue->size = 0;
        queue->head_node = NULL;
        queue->tail_node = NULL;
    }

    return error_code;
}

//CDIO
int delete_queue_list(queue_list_t *queue)
{
    int error_code = INCORRECT_INPUT;
    if (queue)
    {
        error_code = SUCCES;
        int source_size = queue->size;
        for (int i = 0; i < source_size; i++)
        {
            delete_elem_queue_list(queue);
        }

        set_null_queue_list(queue);
    }

    return error_code;
}

int add_elem_queue_list(queue_list_t *queue, void *data)
{
    int error_code = INCORRECT_INPUT;
    if (is_queue_list_correct(queue))
    {
        queue_node_t *new_node;
        error_code = create_queue_node(&new_node);
        if (!error_code)
        {
            new_node->data = data;

            if (is_queue_list_empty(queue))
            {
                queue->tail_node = new_node;
                queue->head_node = new_node;
                queue->tail_node->prev_node = new_node;
                queue->size = 1;
            }
            else
            {
                queue->tail_node->prev_node = new_node;
                queue->tail_node = new_node;
                queue->size += 1;
            }
        }
    }

    return error_code;
}

int delete_elem_queue_list(queue_list_t *queue)
{
    int error_code = INCORRECT_INPUT;
    if (is_queue_list_correct(queue))
    {
        error_code = SUCCES;
        if (queue->size > 1)
        {
            queue_node_t *node_to_delete = queue->head_node;
            queue->head_node = queue->head_node->prev_node;
            delete_queue_node(&node_to_delete);
            queue->size -= 1;
        }
        else if (queue->size == 1)
        {
            delete_queue_node(&(queue->head_node));
            set_null_queue_list(queue);
        }
    }

    return error_code;
}

int print_queue_list(queue_list_t *queue)
{
    int error_code = INCORRECT_INPUT;
    if (queue)
    {
        error_code = SUCCES;
        if (is_queue_list_non_empty(queue))
        {
            void *temp_data = NULL;
            int size = queue->size;
            for (int i = 0; i < size; i++)
            {
                temp_data = queue->head_node->data;
                printf("%x %x\n", queue->head_node, temp_data);
                delete_elem_queue_list(queue);
                add_elem_queue_list(queue, temp_data);
            }
        }
    }

    return error_code;
}

int is_queue_list_empty(queue_list_t *queue)
{
    return queue && !(queue->size) && !(queue->head_node) && !(queue->tail_node);
}

int is_queue_list_non_empty(queue_list_t *queue)
{
    return queue && queue->size > 0 && queue->head_node && queue->tail_node; 
}

int is_queue_list_correct(queue_list_t *queue)
{
    return is_queue_list_empty(queue) || is_queue_list_non_empty(queue);
}