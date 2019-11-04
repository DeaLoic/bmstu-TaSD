#include "stack.h"
#include "array.h"
#include <stdio.h>
#include <stdlib.h>
#include "test.h"

#define TESTING_BASE 50

int print_menu();
int print_address_hex(node_t *node);
int fprintf_hex_node_p_address(FILE *dest, node_t **elem);

int main()
{
    int error_code = SUCCES;

    stack_t stack;
    set_null_stack(&stack);

    stack_array_t stack_arr;
    set_null_array_stack(&stack_arr);

    node_t *node = NULL;
    int64_t temp_int64 = 0;

    free_zone_t free_zone;
    free_zone.max_size = 10;
    free_zone.cur_size = 0;

    create_array(&(free_zone.addresses), free_zone.max_size, sizeof(node_t*));

    int choose = 1;
    while (choose)
    {
        print_menu();

        scanf("%d", &choose);
        system("clear");
        fflush(stdin);
        
        switch (choose)
        {
            case 0:
                break;
            
            case 1:
                if (stack_arr.n)
                {
                    pop_array_stack(&stack_arr);
                }
                else
                {
                    printf("Array stack is empty\n");
                }
                break;

            case 2:
                if (stack_arr.n < MAX_STACK)
                {
                    printf("Input address in hexagen format\n");
                    if (scanf("%x", &temp_int64) == 1 && getchar() == '\n')
                    {
                        push_array_stack(&stack_arr, &temp_int64);
                    }
                    else
                    {
                        printf("INCORRECT_INPUT\n");
                        fflush(stdin);
                    }
                }
                else
                {
                    printf("Array stack is overflow\n");
                }
                
                
                break;

            case 3:
                if (stack_arr.n)
                {
                    peek_array_stack(&stack_arr, &temp_int64);
                    printf("%x\n", temp_int64);
                }
                else
                {
                    printf("Array stack is empty\n");
                }
                break;
            
            case 4:
                print_array_stack(&stack_arr);
                break;

            case 5:
                if (stack.size)
                {
                    pop_with_free_zone_control(&stack, &free_zone);
                }
                else
                {
                    printf("List stack is empty\n");
                }
                break;

            case 6:
                if (stack.size < MAX_STACK)
                {
                    push_with_free_zone_control(&stack, NULL, &free_zone);
                    stack.head->data = stack.head;
                }
                else
                {
                    printf("List stack is overflow\n");
                }
                break;
            
            case 7:
                if (stack.size)
                {
                    peek_stack(&stack, &node);
                    printf("%x\n", node);
                }
                else
                {
                    printf("List stack is empty\n");
                }
                break;
            
            case 8:
                if (free_zone.cur_size)
                {
                    printf("Free addreses:\n");
                    print_array(free_zone.addresses, free_zone.cur_size, sizeof(node_t*), stdout, (int (*)(FILE*, void*))fprintf_hex_node_p_address);
                }
                else
                {
                    printf("All addresses busy\n");
                }
                
                print_stack(&stack);
                break;

            case 9:
                testing(TESTING_BASE);
                break;
            
            default:
                printf("Choose point from menu\n");
                break;
        }
    }

    clean_stack(&stack);
    delete_array(&(free_zone.addresses));

    return error_code;
}

int print_menu()
{
    printf("------------MENU------------\n\n");
    printf("0 - exit\n\n1 - pop from array stack\n2 - push to array stack\n");
    printf("3 - peek from array stack\n4 - print array stack\n\n5 - pop from list stack\n");
    printf("6 - push to list stack\n7 - peek from list stack\n8 - print list stack\n\n9 - testing\n\n");
}

int print_address_hex(node_t *node)
{
    printf("%x", node->data);

    return SUCCES;
}

int fprintf_hex_node_p_address(FILE *dest, node_t **elem)
{
    return fprintf(dest, "%x", *elem);
}