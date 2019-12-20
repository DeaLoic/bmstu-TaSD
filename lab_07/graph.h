#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "linked_list.h"

#include <stdio.h>

typedef struct graph_t
{
    linked_list_t *edges;
} graph_t;


typedef struct graph_node_t
{
    int number;
    char label;
} graph_node_t;

typedef struct edge_t
{
    graph_node_t *first;
    graph_node_t *second;
    int cost;
} edge_t;

int parse_graph(graph_t *graph, FILE *source);
int add_node(graph_t *graph);
int add_edge(graph_t *graph);

linked_list_t *belman_ford(graph_t *graph, int start_node, int end_node);

#endif