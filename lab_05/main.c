#include <stdio.h>
#include "error_codes.h"
#include "modeling.h"
#include "queue_list.h"
#include "logic.h"
#include "info.h"
#include "universal.h"
#include "error_codes.h"
#include "request.h"
#include <time.h>
#include <stdlib.h>

int main()
{
    int error_code = SUCCES;

    queue_list_t queue;
    free_zone_t free_zone;
    set_null_free_zone(&free_zone);
    info_t info;
    set_null_info(&info);

    set_null_queue_list(&queue);
    model(&queue, &free_zone, &info);
    print_full_info(&info);
    //print_queue_list(&queue);
    
    
    getchar();
    return error_code;
}