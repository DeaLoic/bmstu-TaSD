#ifndef __HANDLER_OPERATOR_H__
#define __HANDLER_OPERATOR_H__

typedef struct info_t
{
    int worked_count;

    double free_time;
    double full_time;

    double middle_len_queue;
    int cur_queue_len;

    double middle_proc_time;
    double middle_income_time;

    int in_requests;
    int out_requests;

} info_t;

int set_null_info(info_t *info);

int print_medium_info(info_t *info);
int print_full_info(info_t *info);

#endif