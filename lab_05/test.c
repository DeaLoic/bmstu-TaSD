#include "modeling.h"
#include "queue_list.h"
#include "logic.h"
#include "info.h"
#include "universal.h"
#include "error_codes.h"
#include "request.h"
#include "array.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    queue_list_t queue;
    free_zone_t free_zone;
    set_null_free_zone(&free_zone);
    set_null_queue_list(&queue);
    int c = 0;
    while (c < 300)
    {
        if (c < 100)
        {
            //request_t req;
            //create_request(&req, c);
            add_with_free_zone_control_queue_list(&c, &queue, &free_zone);
        }
        else if (c < 200)
        {
            //printf("%x %x\n", queue.head_node, queue.head_node->prev_node);
            del_with_free_zone_control_queue_list(&queue, &free_zone);
        }
        else
        {
            add_with_free_zone_control_queue_list(&c, &queue, &free_zone);
        }
        //print_queue_list(&queue);
        c++;
    }
    print_queue_list(&queue);
    printf("%d\n", free_zone.cur_size);
    print_array(free_zone.addresses, free_zone.cur_size, sizeof(void*), stdout, printf_pointer);
    getchar();
    return 0;
}