#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "array.h"
#include "linked_list.h"

#include <stdio.h>

enum road_type_t
{
    railway,
    highway
};

typedef struct edge_t
{
    int first;
    int second;

    int lenght;

    enum road_type_t road_type;
} edge_t;

typedef struct graph_t
{
    edge_t **edges;

    int edge_count;
    int node_count;

} graph_t;


int parse_graph(graph_t *graph, FILE *source);

int set_null_graph(graph_t *graph);
int delete_graph(graph_t *graph);

int add_edge(graph_t *graph, edge_t *edge);
int delete_edge(graph_t *graph, edge_t *edge);

int set_edge(edge_t *edge, int first, int second, int lenght, enum road_type_t road_type);

int print_graph_file(FILE *out, graph_t *graph, linked_list_t *path)

int deikstra(graph_t *graph, int start_node, int end_node, linked_list_t *path);

int is_edge_exist(graph_t *graph, edge_t *edge);

#endif