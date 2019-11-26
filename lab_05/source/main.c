#include <stdio.h>
#include "error_codes.h"
#include "array.h"
#include "modeling.h"
#include "queue_list.h"
#include "logic.h"
#include "info.h"
#include "universal.h"
#include "error_codes.h"
#include "request.h"
#include <time.h>
#include <stdlib.h>

void print_menu();

int main()
{
    char buff_input[20];
    int error_code = SUCCES;

    queue_list_t queue_list;
    set_null_queue_list(&queue_list);

    free_zone_t free_zone;
    set_null_free_zone(&free_zone);

    info_t info;
    set_null_info(&info);

    queue_array_t queue_array;
    set_null_queue_array(&queue_array);

    queue_array_t queue_array_check;
    create_queue_array(&queue_array_check, MAX_QUEUE);

    request_t temp_req;
    create_queue_array(&queue_array, MAX_HANDLE_QUEUE);

    int choose = 1;
    while (choose)
    {
        print_menu();

        printf("Your point: ");
        if (scanf("%d", &choose))
        {
            system("clear");
            switch (choose)
            {
                case 0:
                {
                    break;
                }
                case 1:
                if (queue_array.size < queue_array.max_size && queue_array.size < MAX_HANDLE_QUEUE)
                {
                    double new_elem = 0;
                    printf("Input real number: ");
                    if (scanf("%lf", &new_elem) == 1)
                    {
                        create_request(&temp_req, new_elem);
                        add_element_queue_array(&queue_array, &temp_req);
                    }
                    else
                    {
                        printf("\nWrong input\n");
                    }
                }
                else
                {
                    printf("Queue-array is full (%d of %d)\n", queue_array.size, queue_array.max_size);
                }
                    break;

                case 2:
                if (is_queue_array_empty(&queue_array))
                {
                    printf("Queue array is empty\n");
                }
                else
                {
                    delete_element_queue_array(&queue_array);
                    printf("Deleting succes\n");
                }
                break;
                
                case 3:
                if (is_queue_array_empty(&queue_array))
                {
                    printf("Queue array is empty\n");
                }
                else
                {
                    print_queue_array(&queue_array);
                }
                break;

                case 4:
                if (queue_list.size < MAX_HANDLE_QUEUE)
                {
                    double *new_elem = (double*)malloc(sizeof(double));
                    printf("Input real number: ");
                    if (scanf("%lf", new_elem) == 1)
                    {
                        add_with_free_zone_control_queue_list(new_elem, &queue_list, &free_zone);
                    }
                    else
                    {
                        printf("\nWrong input\n");
                        free(new_elem);
                    }
                }
                else
                {
                    printf("Queue-list is full (%d of %d)\n", queue_list.size, MAX_HANDLE_QUEUE);
                }
                break;

                case 5:
                {
                    if (is_queue_list_empty(&queue_list))
                    {
                        printf("Queue list is empty\n");
                    }
                    else
                    {
                        free(queue_list.head_node->data);
                        del_with_free_zone_control_queue_list(&queue_list, &free_zone);
                        printf("Deleting succes\n");
                    }
                    break;
                }

                case 6:
                if (is_queue_list_empty(&queue_list))
                {
                    printf("Queue list is empty\n");
                }
                else
                {
                    print_queue_list(&queue_list);
                }
                break;

                case 7:
                {
                    printf("Free zone:\n");
                    print_array(free_zone.addresses, free_zone.cur_size, sizeof(void*), stdout, printf_pointer);
                    break;
                }
                case 8:
                {
                    queue_list_t que;
                    free_zone_t fre_z;
                    set_null_info(&info);
                    set_null_queue_list(&que);
                    set_null_free_zone(&fre_z);
                    modeling_list(&que, &fre_z, &info);
                }
                break;
                case 9:
                {
                    create_queue_array(&queue_array_check, MAX_QUEUE);
                    set_null_info(&info);
                    modeling_array(&queue_array_check, &info);
                }
                default:
                    printf("Pls, choose point from menu");
                    gets(buff_input);
                    break;
            }
        }
    
        else
        {
        
            gets(buff_input);
            system("clear");

        }
    }
        
    getchar();
    return error_code;
}

void print_menu()
{
    printf("0 - Exit\n\n1 - Add element to array queue\n2 - Delete element from queue array\n3 - Print queue array\n\n"
           "4 - Add element to queue list\n5 - Delete element from queue list\n6 - Print queue list\n7 - Print free zone\n\n"
           "8 - Modeling list\n9 - Modeling array\n");
}