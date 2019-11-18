#include "queue_array.h"
#include "error_codes.h"
#include "request.h"

int create_queue_array(queue_array_t *queue, size_t queue_size)
{
    int error_code = INCORRECT_INPUT;
    if (queue && queue_size <= MAX_QUEUE)
    {
        error_code = SUCCES;
        set_null_queue_array(queue);
        queue->max_size = queue_size;
    }

    return error_code;
}

int set_null_queue_array(queue_array_t *queue)
{
    int error_code = INCORRECT_INPUT;
    if (queue)
    {
        error_code = SUCCES;
        queue->max_size = 0;
        queue->size = 0;
        queue->tail_position = 0;
        queue->head_position = 0;
    }

    return error_code;
}

/*
int print_queue_array(queue_array_t *queue)
{
    int error_code = INCORRECT_INPUT;
    if (is_queue_array_correct(queue))
    {
        error_code = SUCCES;
        for (int i = 0; i < queue->cur_size; i++)
        {
            printf("%lf \n", queue->body[i + queue->cur_tail_position]);
        }
    }
}
*/
int add_element_queue_array(queue_array_t *queue, void *data)
{
    int error_code = INCORRECT_INPUT;
    if (is_queue_array_correct(queue) && !is_queue_array_fill(queue))
    {
        error_code = SUCCES;
        queue->body[queue->tail_position] = data;
        queue->size += 1;
        queue->tail_position = (queue->tail_position + 1) % queue->max_size;
    }

    return error_code;
}

int delete_element_queue_array(queue_array_t *queue)
{
    int error_code = INCORRECT_INPUT;
    if (is_queue_array_correct(queue) && is_queue_array_non_empty(queue))
    {
        error_code = SUCCES;
        queue->size -= 1;
        queue->head_position = (queue->head_position + 1) % queue->max_size;
    }

    return error_code;
}



int is_queue_array_empty(queue_array_t *queue)
{
    return queue && queue->tail_position == queue->head_position && queue->size == 0;
}

int is_queue_array_non_empty(queue_array_t *queue)
{
    return queue && queue->size != 0;
}

int is_queue_array_fill(queue_array_t *queue)
{
    return queue && queue->size == queue->max_size;
}
int is_queue_array_correct(queue_array_t *queue)
{
    return (is_queue_array_empty(queue) || is_queue_array_non_empty(queue)) && queue->size <= queue->max_size;
}