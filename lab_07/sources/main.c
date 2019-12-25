#include "error_codes.h"
#include "graph.h"
#include "linked_list.h"

#include <stdlib.h>
#include <stdio.h>

#define FILE_S "graph.txt"
#define FILE_DOT "graph_1.dot"

int main()
{
    graph_t graph;

    FILE *f = fopen(FILE_S, "r");
    parse_graph(&graph, f);
    fclose(f);

    linked_list_t way;

    int choose = 1;
    int first_node = 0;
    int second_node = 0;
    while (choose != 0)
    {
        printf("Input start and finish node: ");
        if (scanf("%d %d", &first_node, &second_node) == 2 && first_node > 0 && second_node > 0 &&\
             first_node < graph.node_count + 1 && second_node < graph.node_count + 1 )
        {
            set_null_list(&way);

            int way_l = deikstra(&graph, first_node, second_node, &way);
            printf("\nLenght of way: %d\n", way_l);
            if (way.size != INT32_MAX)
            {
                printf("Way in unor edges: ");
                for (int i = 0; i < way.size; i++)
                {
                    printf("%d %d ", ((edge_t *)get_element(&way, i))->first, ((edge_t *)get_element(&way, i))->second);
                }
                f = fopen(FILE_DOT, "w");
                print_graph_file(f, &graph, &way);

                fclose(f);
                system("dot.exe -Tpng " FILE_DOT" -o OutputFile.png");
                system("OutputFile.png");
            }
            else
            {
                printf("\nSolution doesnt exist");
            }
            
        }
        else
        {
            printf("\nIncorrect nodes number\n");
        }
        printf("\nContinue? (1/0)\n");
        if (scanf("%d", &choose) != 1)
        {
            break;
        };
    }
    
    getchar();

    return SUCCES;
}