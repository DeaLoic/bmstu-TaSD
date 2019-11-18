#ifndef __LOGIC_H__
#define __LOGIC_H__

#include "queue_array.h"
#include "queue_list.h"
#include "info.h"

typedef struct free_zone_t
{
    void **addresses;
    int max_size;
    int cur_size;
} free_zone_t;

int set_null_free_zone(free_zone_t *free_zone);

int del_with_free_zone_control_queue_list(queue_list_t *queue, free_zone_t *free_zone);
int add_with_free_zone_control_queue_list(void *data, queue_list_t *queue, free_zone_t *free_zone);

int print_queue_list_req(queue_list_t *queue);

#endif
