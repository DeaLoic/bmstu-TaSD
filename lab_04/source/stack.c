#include <inttypes.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#include "stack.h"
#include "error_codes.h"

int set_null_stack(stack_t *stack)
{
    int error_code = INCORRECT_INPUT;
    if (stack)
    {
        error_code = SUCCES;
        stack->head = NULL;
        stack->size = 0;
    }

    return error_code;
}

int clean_stack(stack_t *stack)
{
    int error_code = INCORRECT_INPUT;
    if (stack)
    {
        error_code = SUCCES;
        for (int i = 0; i < stack->size; i++)
        {
            pop_stack(stack);
        }
        set_null_stack(stack);
    }

    return error_code;
}

/*
int input_stack(stack_t *stack, int n)
{
    int error_code = INCORRECT_INPUT;
    if (stack && data_input)
    {
        error_code = MEMORY_ERROR;
        void *data_buff = malloc(data_size);
        if (data_buff)
        {
            error_code = SUCCES;
        }

        for (int i = 0; i < n && !error_code; i++)
        {
            error_code = data_input(data_buff);
            if (!error_code)
            {
                error_code = push_stack(stack, data_buff, data_size);
            }
        }
    }

    return error_code;
}
*/

int print_stack(stack_t *stack)
{
    int error_code = INCORRECT_INPUT;
    if (stack)
    {
        stack_t stack_buff;
        set_null_stack(&stack_buff);

        error_code = SUCCES;
        node_t *temp_elem;

        int elem_cnt = stack->size;
        for (int i = 0; i < elem_cnt && !error_code; i++)
        {
            error_code = peek_stack(stack, &temp_elem);
            if (!error_code)
            {
                printf("%x      %x\n", temp_elem, stack->head);

                temp_elem = stack->head;
                stack->head = stack->head->next_node;

                temp_elem->next_node = stack_buff.head;
                stack_buff.head = temp_elem;

                (stack_buff.size)++;
                (stack->size)--;
            }
        }

        elem_cnt = stack_buff.size;
        for (int i = 0; i < elem_cnt && !error_code; i++)
        {
            temp_elem = stack_buff.head;
            stack_buff.head = temp_elem->next_node;

            temp_elem->next_node = stack->head;
            stack->head = temp_elem;

            (stack_buff.size)--;
            (stack->size)++;
        }
    }

    return error_code;
}

int pop_stack(stack_t *stack)
{
    int error_code = INCORRECT_INPUT;
    if (stack && stack->head)
    {
        node_t *next_head = stack->head->next_node;
        free(stack->head);
        stack->head = next_head;
        stack->size--;

        error_code = SUCCES;
    }

    return error_code;
}

int pop_with_free_zone_control(stack_t *stack, free_zone_t *free_zone)
{
    int error_code = INCORRECT_INPUT;
    if (stack && stack->size)
    {
        error_code = SUCCES;
        if (free_zone->cur_size == free_zone->max_size)
        {
            error_code = change_size_array(&(free_zone->addresses), free_zone->max_size + 20, sizeof(node_t*));
            free_zone->max_size += 20;
        }
        if (!error_code)
        {
            free_zone->addresses[free_zone->cur_size] = stack->head->data;
            (free_zone->cur_size)++;
            pop_stack(stack);
        }
    }

    return error_code;
}

int push_stack(stack_t *stack, node_t *elem)
{
    int error_code = INCORRECT_INPUT;
    if (stack)
    {
        node_t *new_head = (node_t*)malloc(sizeof(node_t));
        if (new_head)
        {
            error_code = SUCCES;
            new_head->data = elem;
            new_head->next_node = stack->head;
            stack->head = new_head;
            stack->size++;
        }
        else
        {
            error_code = MEMORY_ERROR;
            free(new_head);
        }
    }

    return error_code;
}

int compare_node_p(node_t **first, node_t **second)
{
    int exit_code = -1;
    if (*first == *second)
    {
        exit_code = 0;
    }
    if (*first > *second)
    {
        exit_code = 1;
    }

    return exit_code;
}

int push_with_free_zone_control(stack_t *stack, node_t *elem, free_zone_t *free_zone, int is_print)
{
    int error_code = INCORRECT_INPUT;
    if (stack)
    {
        push_stack(stack, elem);
        int pos = pos_in_array(free_zone->addresses, free_zone->cur_size, sizeof(node_t*), &(stack->head), compare_node_p);
        if (pos != -1)
        {
            if (is_print)
            {
                printf("Take %x from free zone\n", free_zone->addresses[pos]);
            }
            move_to_end(free_zone->addresses, free_zone->cur_size, sizeof(node_t*), pos);
            (free_zone->cur_size)--;
        }
    }

    return error_code;
}

int peek_stack(stack_t *stack, node_t **elem)
{
    int error_code = INCORRECT_INPUT;
    if (stack && stack->head)
    {
        error_code = SUCCES;
        *elem = stack->head->data;
    }

    return error_code;
}

int set_null_array_stack(stack_array_t *stack)
{
    int error_code = INCORRECT_INPUT;
    if (stack)
    {
        error_code = SUCCES;
        stack->n = 0;
    }

    return error_code;
}

int clean_array_stack(stack_array_t *stack)
{
    int error_code = INCORRECT_INPUT;
    if (stack)
    {
        error_code = SUCCES;
        for (int i = 0; i < stack->n; i++)
        {
            pop_array_stack(stack);
        }
        set_null_array_stack(stack);
    }

    return error_code;
}

int input_array_stack(stack_array_t *stack, int n)
{
    int error_code = INCORRECT_INPUT;
    if (stack)
    {
        error_code = SUCCES;
        int64_t data = NULL;

        for (int i = 0; i < n && !error_code; i++)
        {
            if (scanf("%x", &data) == 1)
            {
                push_array_stack(stack, &data);
            }
            else
            {
                error_code = INPUT_ERROR;
            }
        }
    }

    return error_code;
}
int print_array_stack(stack_array_t *stack)
{
    int error_code = INCORRECT_INPUT;
    if (stack)
    {
        stack_array_t stack_buff;
        set_null_array_stack(&stack_buff);

        int64_t data_buff = 0;
        error_code = SUCCES;
        int elem_cnt = stack->n;
        for (int i = 0; i < elem_cnt && !error_code; i++)
        {
            error_code = peek_array_stack(stack, &data_buff);
            if (!error_code)
            {
                printf("%x     %x\n", data_buff, stack->data + stack->n);
                if (!error_code)
                {
                    pop_array_stack(stack);
                    error_code = push_array_stack(&stack_buff, &data_buff);
                }
            }
        }
        elem_cnt = stack_buff.n;
        for (int i = 0; i < elem_cnt && !error_code; i++)
        {
            error_code = peek_array_stack(&stack_buff, &data_buff);
            if (!error_code)
            {
                pop_array_stack(&stack_buff);
                error_code = push_array_stack(stack, &data_buff);
            }
        }
    }

    return error_code;
}

int pop_array_stack(stack_array_t *stack)
{
    int error_code = INCORRECT_INPUT;
    if (stack && stack->n > 0)
    {
        error_code = SUCCES;
        stack->n--;
    }

    return error_code;
}

int push_array_stack(stack_array_t *stack, int64_t *data)
{
    int error_code = INCORRECT_INPUT;
    if (stack && stack->n >= 0)
    {
        error_code = SUCCES;
        stack->data[stack->n] = *data;
        stack->n++;
    }

    return error_code;
}

int peek_array_stack(stack_array_t *stack, int64_t *data)
{
    int error_code = INCORRECT_INPUT;
    if (stack && stack->n > 0)
    {
        error_code = SUCCES;
        *data = stack->data[stack->n - 1];
    }

    return error_code;
}