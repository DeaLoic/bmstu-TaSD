#include "queue_array.h"
#include "error_codes.h"

int create_queue_array(queue_array_t *queue, size_t queue_size)
{
    int error_code = INCORRECT_INPUT;
    if (queue)
    {
        error_code = SUCCES;
        queue->cur_size = 0;
        queue->size = queue_size;
        queue->cur_tail_position = 0;
    }

    return error_code;
}

int set_null_queue_array(queue_array_t *queue)
{
    int error_code = INCORRECT_INPUT;
    if (queue)
    {
        error_code = SUCCES;
        queue->cur_size = 0;
        queue->size = 0;
        queue->cur_tail_position = 0;
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
int add_element_queue_array(queue_array_t *queue, double data);
int delete_element_queue_array(queue_array_t *queue);