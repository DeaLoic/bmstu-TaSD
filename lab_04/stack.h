#ifndef __STACK_H__
#define __STACK_H__

#include <stdio.h>
#include <inttypes.h>
#include "error_codes.h"

#define MAX_STACK 30
#define MAX_MAX_STACK 300

struct node_t
{
    struct node_t *data;
    struct node_t *next_node;
};

typedef struct node_t node_t;

typedef struct stack_t
{
    node_t *head;
    int size;
} stack_t;

typedef struct
{
    node_t **addresses;
    int max_size;
    int cur_size;
} free_zone_t;

typedef struct
{
    int n;
    int64_t data[MAX_MAX_STACK];

} stack_array_t;

int set_null_stack(stack_t *stack);
int clean_stack(stack_t *stack);
//int input_stack(stack_t *stack, int n);
int print_stack(stack_t *stack);

int pop_stack(stack_t *stack);
int pop_with_free_zone_control(stack_t *stack, free_zone_t *free_zone);

int push_stack(stack_t *stack, node_t *new_elem);
int push_with_free_zone_control(stack_t *stack, node_t *new_elem, free_zone_t *free_zone);

int peek_stack(stack_t *stack, node_t **elem);

// array
int set_null_array_stack(stack_array_t *stack);
int clean_array_stack(stack_array_t *stack);
int input_array_stack(stack_array_t *stack, int n);
int print_array_stack(stack_array_t *stack);

int pop_array_stack(stack_array_t *stack);
int push_array_stack(stack_array_t *stack, int64_t *data);
int peek_array_stack(stack_array_t *stack, int64_t *data);

#endif