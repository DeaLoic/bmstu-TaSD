#include "graph.h"
#include "linked_list.h"
#include "error_codes.h"

int parse_graph(graph_t *graph, FILE *source);
int add_node(graph_t *graph);
int add_edge(graph_t *graph);

linked_list_t *belman_ford(graph_t *graph, int start_node, int end_node);