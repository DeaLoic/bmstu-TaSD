#include "logic.h"
#include "queue_array.h"
#include "queue_list.h"
#include "array.h"
#include "request.h"
#include "error_codes.h"
#include "universal.h"
#include <stdio.h>

int set_null_free_zone(free_zone_t *free_zone)
{
    int error_code = INCORRECT_INPUT;
    if (free_zone)
    {
        error_code = SUCCES;
        free_zone->addresses = NULL;
        free_zone->cur_size = 0;
        free_zone->max_size = 0;
    }

    return error_code;
}

int del_with_free_zone_control_queue_list(queue_list_t *queue, free_zone_t *free_zone)
{
    int error_code = INCORRECT_INPUT;

    if (queue && free_zone)
    {
        if (is_queue_list_non_empty(queue))
        {
            error_code = SUCCES;
            if (free_zone->cur_size == free_zone->max_size)
            {
                error_code = change_size_array(&(free_zone->addresses), free_zone->max_size * 2 + 1, sizeof(void *));
                if (!error_code)
                {
                    free_zone->max_size = free_zone->max_size * 2 + 1;
                }
            }

            if (!error_code)
            {
                (free_zone->addresses)[free_zone->cur_size] = queue->head_node;
                free_zone->cur_size += 1;
            }
            delete_elem_queue_list(queue);
        }
    }

    return error_code;
}

int add_with_free_zone_control_queue_list(void *data, queue_list_t *queue, free_zone_t *free_zone)
{
    int error_code = INCORRECT_INPUT;
    if (queue && free_zone)
    {
        error_code = add_elem_queue_list(queue, data);
        int pos = pos_in_array(free_zone->addresses, free_zone->cur_size, sizeof(void *), &(queue->tail_node), compare_void_p);
        if (pos != -1)
        {
            move_to_end(free_zone->addresses, free_zone->cur_size, sizeof(void *), pos);
            free_zone->cur_size -= 1;
        }
    }

    return error_code;
}

int print_queue_list_req(queue_list_t *queue)
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
                delete_elem_queue_list(queue);
                printf("%lf %d\n", ((request_t *)temp_data)->data, ((request_t *)temp_data)->count_of_cycle);
                add_elem_queue_list(queue, temp_data);
            }
        }
    }

    return error_code;
}