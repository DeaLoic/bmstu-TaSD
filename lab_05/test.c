#include "modeling.h"
#include "queue_list.h"
#include "logic.h"
#include "info.h"
#include "universal.h"
#include "error_codes.h"
#include "request.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    queue_list_t queue;
    set_null_queue_list(&queue);
    int c = 0;
    while (scanf("%d", &c))
    {
        if (c <= 100)
        {
            //request_t req;
            //create_request(&req, c);
            printf("%x %d\n", &c, c);
            add_elem_queue_list(&queue, &c);
        }
        else
        {
            delete_elem_queue_list(&queue);
        }
        print_queue_list(&queue);
        printf("\n");
    }
}