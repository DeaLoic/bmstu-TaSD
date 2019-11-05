#include <inttypes.h>
#include "test.h"
#include "universal.h"
#include "stack.h"

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

void testing(int size)
{
    test(size);
    printf("\n");
    test(size * 2);
    printf("\n");
    test(size * 5);
}