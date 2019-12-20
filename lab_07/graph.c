#include "graph.h"
#include "linked_list.h"
#include "error_codes.h"

int parse_graph(graph_t *graph, FILE *source)
{
    while ()
}
int add_node(graph_t *graph, graph_node_t *node);
int add_edge(graph_t *graph, edge_t *edge);

linked_list_t *belman_ford(graph_t *graph, int start_node, int end_node);