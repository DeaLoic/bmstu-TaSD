#include <inttypes.h>
#include "array.h"
#include "test.h"
#include "universal.h"
#include "stack.h"
#include <stdlib.h>

void test_list_stack(int size)
{
    stack_t stack;
    set_null_stack(&stack);

    uint64_t start_tick = tick();
    node_t *data_temp = NULL;
    for (int iter = 0; iter < 3; iter++)
    {
        for (int i = 0; i < size; i++)
        {
            data_temp = rand();
            push_stack(&stack, &data_temp);
        }

        for (int i = 0; i < size; i++)
        {
            pop_stack(&stack);
        }
    }

    uint64_t end_tick = tick();
    printf("List-based stack: %" PRIu64 "\n", end_tick - start_tick);
}

void test_array_stack(int size)
{
    stack_array_t stack;
    set_null_array_stack(&stack);

    uint64_t start_tick = tick();
    int64_t data_temp = 0;
    for (int iter = 0; iter < 3; iter++)
    {
        for (int i = 0; i < size; i++)
        {
            data_temp = rand();
            push_array_stack(&stack, &data_temp);
        }

        for (int i = 0; i < size; i++)
        {
            pop_array_stack(&stack);
        }
    }

    uint64_t end_tick = tick();
    printf("Array-based stack: %" PRIu64 "\n", end_tick - start_tick);
}

void test(int size)
{
    printf("3 cycles      %d elements", size);
    test_list_stack(size);
    test_array_stack(size);
}

void test_list_stack_defrag(int size)
{
    free_zone_t free_zone;
    free_zone.addresses = NULL;
    free_zone.max_size = 0;
    free_zone.cur_size = 0;
    stack_t stack;
    set_null_stack(&stack);

    node_t *data_temp = NULL;
    for (int iter = 0; iter < 3; iter++)
    {
        for (int i = 0; i < size; i++)
        {
            data_temp = rand();
            push_with_free_zone_control(&stack, &data_temp, &free_zone, 0);
            stack.head->data = stack.head;
        }

        for (int i = 0; i < size; i++)
        {
            pop_with_free_zone_control(&stack, &free_zone);
        }
    }

    printf("\nList-based stack free zone count (should be %d): %d    %d\n", size, free_zone.cur_size, free_zone.max_size);
    free(free_zone.addresses);
}

void test_defrag(int size)
{
    printf("DEFRUGMENTATION\n3 cycles      %d elements", size);
    test_list_stack_defrag(size);
}

void testing(int size)
{
    test(size);
    printf("\n");
    test(size * 2);
    printf("\n");
    test(size * 5);
    printf("\n");
    test_defrag(size * 5);
}