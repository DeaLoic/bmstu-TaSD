#ifndef __QUEUE_LIST_H__
#define __QUEUE_LIST_H__

#include <stdio.h>

struct queue_node_t
{
    void *data;
    struct queue_node_t *prev_node;
};

typedef struct queue_node_t queue_node_t;

// Add to tail node
typedef struct queue_list_t
{
    queue_node_t *head_node;
    queue_node_t *tail_node;
    int size;
} queue_list_t;



int create_queue_node(queue_node_t **node);
int delete_queue_node(queue_node_t **node);
int set_null_queue_node(queue_node_t *node);

//CDIO
int set_null_queue_list(queue_list_t *queue);
int delete_queue_list(queue_list_t *queue);

int add_elem_queue_list(queue_list_t *queue, void *data);
int delete_elem_queue_list(queue_list_t *queue);
int print_queue_list(queue_list_t *queue);

int is_queue_list_non_empty(queue_list_t *queue);
int is_queue_list_empty(queue_list_t *queue);
int is_queue_list_correct(queue_list_t *queue);

#endif