#ifndef __QUEUE_ARRAY_H__
#define __QUEUE_ARRAY_H__

#include <stddef.h>
#include "queue_defines.h"

typedef struct queue_array_t
{
    double body[MAX_QUEUE];
    int size;
    int cur_size;
    int cur_tail_position;
} queue_array_t;

int create_queue_array(queue_array_t *queue, size_t queue_size);
int set_null_queue_array(queue_array_t *queue);
int print_queue_array(queue_array_t *queue);

int add_element_queue_array(queue_array_t *queue, double data);
int delete_element_queue_array(queue_array_t *queue);

#endif