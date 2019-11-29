#include "modeling.h"
#include "queue_defines.h"
#include "queue_list.h"
#include "logic.h"
#include "info.h"
#include "universal.h"
#include "error_codes.h"
#include "request.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int next_cycle_list(queue_list_t *queue, free_zone_t *free_zone, info_t *info, request_t *next_request)
{
    int error_code = INCORRECT_INPUT;
    if (queue && free_zone && info)
    {
        error_code = SUCCES;
        if (is_queue_list_non_empty(queue))
        {

            request_t *temp_last_request = (request_t*)(queue->head_node->data);
            temp_last_request->count_of_cycle += 1;
            del_with_free_zone_control_queue_list(queue, free_zone);

            info->worked_count += 1;
            double oper_time = ((double)rand() / (double)RAND_MAX) * MAX_PROC_TIME;
            
            info->middle_proc_time += oper_time;
            
            if ((info->full_time - temp_last_request->data) < 0)
            {
                info->free_time += temp_last_request->data - info->full_time;
                info->full_time += (temp_last_request->data - info->full_time);
            }
            info->full_time += oper_time;
            if (is_request_full_handled(temp_last_request))
            {
                info->out_requests += 1;
                free(temp_last_request);
                if (is_queue_list_empty(queue) || (compare_double(&(next_request->data), &(info->full_time)) < 0))
                {
                    add_with_free_zone_control_queue_list(next_request, queue, free_zone);
                    info->in_requests += 1;
                }
                else
                {
                    info->cur_queue_len = queue->size;
                    info->middle_len_queue = (info->middle_len_queue + queue->size) / 2.0;
                    next_cycle_list(queue, free_zone, info, next_request);
                }
            }
            else
            {
                temp_last_request->data = info->full_time;
                if (compare_double(&(next_request->data), &(info->full_time)) > 0)
                {
                    add_with_free_zone_control_queue_list(temp_last_request, queue, free_zone);
                    next_cycle_list(queue, free_zone, info, next_request);
                }
                else
                {
                    add_with_free_zone_control_queue_list(next_request, queue, free_zone);
                    add_with_free_zone_control_queue_list(temp_last_request, queue, free_zone);
                    info->cur_queue_len = queue->size;

                    info->middle_len_queue = (info->middle_len_queue + queue->size) / 2.0;
                    info->in_requests += 1;
                }
            }
        }
        else
        {
            add_with_free_zone_control_queue_list(next_request, queue, free_zone);
            info->cur_queue_len = queue->size;
            info->middle_len_queue = (info->middle_len_queue + queue->size) / 2.0;
            info->in_requests += 1;
        }
        
    }

    return error_code;
}

int modeling_list(queue_list_t *queue, free_zone_t *free_zone, info_t *info)
{
    int error_code = INCORRECT_INPUT;
    if (queue && free_zone && info)
    {
        srand(time(NULL));
        error_code = SUCCES;
        double wait_time = 0;
        double last_wait_time = 0;
        int i = 1;

        clock_t start_time = clock();

        while (info->out_requests < TARGET_OUTPUT_REQUEST && !error_code)
        {
            start_time = clock();
            request_t *next_request = (request_t*)malloc(sizeof(request_t));
            if (next_request)
            {
                wait_time = (((double)rand() / (double)RAND_MAX) * MAX_INCOME_TIME);
                info->middle_income_time += wait_time;
                last_wait_time += wait_time;
                create_request(next_request, last_wait_time);
                next_cycle_list(queue, free_zone, info, next_request);
                if (info->cur_queue_len > info->max_queue_len)
                {
                    info->max_queue_len = info->cur_queue_len;
                }
            }
            info->real_time += (clock() - start_time);
            if ((info->out_requests / 100) == i)
            {
                printf("\n%d requests was output\n", i * 100);
                print_medium_info(info);
                printf("\n");   
                i++;
            }
        }
        info->real_time /= CLOCKS_PER_SEC;
        info->middle_income_time /= info->in_requests;
        info->middle_proc_time /= info->worked_count;
        print_full_info(info);
        printf("\nUniqle memory blocks was used (ideal - %d (max queue size)): %d\n", info->max_queue_len, free_zone->cur_size);
    }

    return error_code;
}

int modeling_array(queue_array_t *queue, info_t *info)
{
    int error_code = INCORRECT_INPUT;
    if (queue && info)
    {
        srand(time(NULL));
        error_code = SUCCES;
        double wait_time = 0;
        double last_wait_time = 0;
        int i = 1;
        clock_t start_time = clock();
        while (info->out_requests < TARGET_OUTPUT_REQUEST && !error_code)
        {
            start_time = clock();
            request_t next_request;
            wait_time = (((double)rand() / (double)RAND_MAX) * MAX_INCOME_TIME);
            info->middle_income_time += wait_time;
            last_wait_time += wait_time;

            create_request(&next_request, last_wait_time);
            error_code = next_cycle_array(queue, info, &next_request);

            info->real_time += (clock() - start_time);
            if ((info->out_requests / 100) == i)
            {
                printf("\n%d requests was output\n\n", i * 100);
                print_medium_info(info);
                i++;
            }
        }
        if (error_code)
        {
            printf("During runtime queue-array was overflowed\nInfo at overflow moment:\n");
        }

        info->real_time /= CLOCKS_PER_SEC;
        info->middle_income_time /= info->in_requests;
        info->middle_proc_time /= info->worked_count;
        print_full_info(info);
    }
}

int next_cycle_array(queue_array_t *queue, info_t *info, request_t *next_request)
{
    int error_code = INCORRECT_INPUT;
    //printf("\n %d\n", queue->size);
    if (queue && info)
    {
        error_code = SUCCES;
        if (is_queue_array_non_empty(queue))
        {
            request_t temp_last_request;
            copy_request(&temp_last_request, queue->body + queue->head_position);
            temp_last_request.count_of_cycle += 1;
            delete_element_queue_array(queue);
            
            //printf("%d\n", temp_last_request.count_of_cycle);
            info->worked_count += 1;
            double oper_time = ((double)rand() / (double)RAND_MAX) * MAX_PROC_TIME;
            info->middle_proc_time += oper_time;
            

            if ((info->full_time - temp_last_request.data) < 0)
            {
                info->free_time += temp_last_request.data - info->full_time;
                info->full_time += (temp_last_request.data - info->full_time);
            }
            info->full_time += oper_time;
            if (is_request_full_handled(&temp_last_request))
            {
                info->out_requests += 1;
                if (is_queue_array_empty(queue) || (compare_double(&(next_request->data), &(info->full_time)) < 0))
                {
                    add_element_queue_array(queue, next_request);
                    info->in_requests += 1;
                }
                else
                {
                    info->cur_queue_len = queue->size;
                    info->middle_len_queue = (info->middle_len_queue + queue->size) / 2.0;
                    error_code = next_cycle_array(queue, info, next_request);
                }
            }
            else
            {
                temp_last_request.data = info->full_time;
                if (compare_double(&(next_request->data), &(info->full_time)) > 0)
                {
                    add_element_queue_array(queue, &temp_last_request);
                    error_code = next_cycle_array(queue, info, next_request);
                }
                else
                {
                    add_element_queue_array(queue, next_request);
                    add_element_queue_array(queue, &temp_last_request);
                    info->in_requests += 1;
                    
                    info->cur_queue_len = queue->size;
                    info->middle_len_queue = (info->middle_len_queue + queue->size) / 2.0;
                }
            }
        }
        else
        {
            add_element_queue_array(queue, next_request);
            info->cur_queue_len = queue->size;
            info->middle_len_queue = (info->middle_len_queue + queue->size) / 2.0;
            info->in_requests += 1;
        }
    }

    return error_code;
}