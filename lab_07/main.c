#include "error_codes.h"
#include "graph.h"
#include "linked_list.h"

#include <stdio.h>

#define FILE_S "graph.txt"

int main()
{
    graph_t graph;

    FILE *f = fopen(FILE_S, "r");
    parse_graph(&graph, f);
    fclose(f);

    linked_list_t way;
    set_null_list(&way);

    printf("Lenght of way: %d\nWay in nodes: ", deikstra(&graph, 1, 3, &way));
    if (way.size)
    {
        printf("%d ", ((edge_t *)get_element(&way, 0))->first);
    }
    for (int i = 0; i < way.size; i++)
    {
        printf("%d", ((edge_t *)get_element(&way, i))->second);
    }
    getchar();getchar();

    return SUCCES;
}