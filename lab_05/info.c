#include "info.h"
#include "error_codes.h"
#include <stdio.h>

int set_null_info(info_t *info)
{
    int error_code = INCORRECT_INPUT;

    if (info)
    {
        error_code = SUCCES;
        info->cur_queue_len = 0;
        info->middle_len_queue = 0;
        info->free_time = 0;
        info->full_time = 0;
        info->in_requests = 0;
        info->out_requests = 0;
        info->worked_count = 0;
        info->middle_income_time = 0;
        info->middle_proc_time = 0;
    }

    return error_code;
}

int print_medium_info(info_t *info)
{
    int error_code = INCORRECT_INPUT;
    if (info)
    {
        error_code = SUCCES;
        printf("Middle lenght of queue: %lf\n"
               "Current lenght of queue: %d\n",
                info->middle_len_queue, info->cur_queue_len);
    }

    return error_code;
}

int print_full_info(info_t *info)
{
    int error_code = INCORRECT_INPUT;
    if (info)
    {
        error_code = SUCCES;
        printf("Full time: %lf\n"
               "Free time: %lf\n\n"
               "Requests was input: %d\n"
               "Requests was output: %d\n\n"
               "Worked times: %d\n\n"
               "Middle lenght of queue: %lf\n"
               "Current lenght of queue: %d\n\n"
               "Middle income time: %lf\n"
               "Middle processing time: %lf\n",
                info->full_time, info->free_time,
                info->in_requests, info->out_requests,
                info->worked_count,
                info->middle_len_queue, info->cur_queue_len,
                info->middle_income_time, info->middle_proc_time);
    }

    return error_code;
}