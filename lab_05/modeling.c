#include "modeling.h"
#include "queue_list.h"
#include "logic.h"
#include "info.h"
#include "universal.h"
#include "error_codes.h"
#include "request.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int next_cycle(queue_list_t *queue, free_zone_t *free_zone, info_t *info, request_t *next_request)
{
    int error_code = INCORRECT_INPUT;
    //printf("\n %d\n", queue->size);
    if (queue && free_zone && info)
    {
        error_code = SUCCES;
        if (is_queue_list_non_empty(queue))
        {
            //print_queue_list_req(queue);

            request_t *temp_last_request = (request_t*)(queue->head_node->data);
            temp_last_request->count_of_cycle += 1;
            del_with_free_zone_control_queue_list(queue, free_zone);

            info->worked_count += 1;
            double oper_time = ((double)rand() / (double)RAND_MAX) * MAX_PROC_TIME;
            printf("%lf\n", oper_time);
            info->middle_proc_time += oper_time;
            //info->middle_proc_time /= 2;

            if ((info->full_time - temp_last_request->data) < 0)
            {
                info->free_time += temp_last_request->data - info->full_time;
                info->full_time += (temp_last_request->data - info->full_time);
            }
            info->full_time += oper_time;
            //printf("%x, %lf, %d    %lf     %lf\n", temp_last_request, temp_last_request->data, temp_last_request->count_of_cycle, info->full_time, next_request->data);
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
                    next_cycle(queue, free_zone, info, next_request);
                }
            }
            else
            {
                temp_last_request->data = info->full_time;
                if (compare_double(&(next_request->data), &(info->full_time)) > 0)
                {
                    add_with_free_zone_control_queue_list(temp_last_request, queue, free_zone);
                    next_cycle(queue, free_zone, info, next_request);
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

int model(queue_list_t *queue, free_zone_t *free_zone, info_t *info)
{
    int error_code = INCORRECT_INPUT;
    if (queue && free_zone && info)
    {
        srand(time(NULL));
        error_code = SUCCES;
        double wait_time;
        int i = 1;
        while (info->out_requests < TARGET_OUTPUT_REQUEST && !error_code)
        {

            request_t *next_request = (request_t*)malloc(sizeof(request_t));
            if (next_request)
            {
                wait_time = (((double)rand() / (double)RAND_MAX) * MAX_INCOME_TIME);
                info->middle_income_time += wait_time;
                create_request(next_request, info->full_time + wait_time);
                next_cycle(queue, free_zone, info, next_request);
                //print_full_info(info);
            }
            // TODO FIX
            //printf("%d\n", info->out_requests);
            if ((info->out_requests / 100) == i)
            {
                printf("\n%d requests was output\n\n", i * 100);
                print_medium_info(info);
                i++;
                info->middle_income_time /= 100;
            }
        }
        info->middle_income_time /= info->worked_count;
        print_full_info(info);
    }

    return error_code;
}