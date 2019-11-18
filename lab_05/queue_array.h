#ifndef __QUEUE_ARRAY_H__
#define __QUEUE_ARRAY_H__

#include <stddef.h>
#include "queue_defines.h"

typedef struct queue_array_t
{
    void *body[MAX_QUEUE];
    int max_size;
    int size;
    int tail_position;
    int head_position;

} queue_array_t;

int create_queue_array(queue_array_t *queue, size_t queue_size);
int set_null_queue_array(queue_array_t *queue);
int print_queue_array(queue_array_t *queue);

int add_element_queue_array(queue_array_t *queue, void *data);
int delete_element_queue_array(queue_array_t *queue);

int is_queue_array_empty(queue_array_t *queue);
int is_queue_array_non_empty(queue_array_t *queue);
int is_queue_array_fill(queue_array_t *queue);
int is_queue_array_correct(queue_array_t *queue);

#endif