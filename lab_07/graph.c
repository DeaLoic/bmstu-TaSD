#include "graph.h"
#include "array.h"
#include "universal.h"
#include "error_codes.h"
#include "linked_list.h"
#include <stdio.h>

int parse_graph(graph_t *graph, FILE *source)
{
    set_null_graph(graph);
    fscanf(source, "%d", &(graph->node_count));

    edge_t *new_edge = (edge_t*)malloc(sizeof(edge_t));
    int temp = 0;
    while (fscanf(source, "%d %d %d %d", &(new_edge->first), &(new_edge->second), &(new_edge->lenght), &(temp)) == 4)
    {
        if (temp == 1)
        {
            new_edge->road_type = highway;
        }
        change_size_array(&(graph->edges), graph->edge_count + 1, sizeof(new_edge));
        graph->edges[graph->edge_count] = new_edge;
        graph->edge_count += 1;
        new_edge = (edge_t*)malloc(sizeof(edge_t));
    }
    free(new_edge);

    return SUCCES;
}

int set_null_graph(graph_t *graph)
{
    if (graph)
    {
        graph->edges = NULL;
        graph->edge_count = 0;
        graph->node_count = 0;
    }

    return SUCCES;
}

int delete_graph(graph_t *graph)
{
    if (graph)
    {
        if (graph->edges)
        {
            for (int i = 0; i < graph->edge_count; i++)
            {
                free((graph->edges)[i]);
            }
            free(graph->edges);
        }
    }

    set_null_graph(graph);

    return SUCCES;
}

/*
int delete_node(graph_t *graph, int node_number)
{
    int error_code = SUCCES;
    if (graph && graph->node_count && is_node_exist(graph, node_number))
    {
        graph_node_t node;
        set_node(&node, node_number, 0, 0);
        int pos = find_in_array(graph->nodes, graph->node_count, sizeof(graph_node_t*), &node, node_compare);

        move_to_end(graph->nodes, graph->node_count, sizeof(graph_node_t*), pos);

        free(graph->nodes[graph->node_count - 1]);
        change_size_array(&(graph->nodes), graph->node_count - 1, sizeof(graph_node_t*));
        graph->node_count -= 1;
    }
    return error_code;
}
*/

int add_edge(graph_t *graph, edge_t *edge)
{
    int error_code = INCORRECT_INPUT;
    if (graph)
    {
        error_code = SUCCES;
        if (!is_edge_exist(graph->edges, graph->edge_count, edge))
        {
            change_size_array(&(graph->edges), graph->edge_count + 1, sizeof(edge_t*));
            graph->edges[graph->edge_count] = edge;
            graph->edge_count += 1;
        }
    }

    return error_code;
}


int set_edge(edge_t *edge, int first, int second, int lenght, enum road_type_t road_type)
{
    if (edge)
    {
        edge->first = first;
        edge->second = second;
        edge->lenght = lenght;
        edge->road_type = road_type;
    }

    return SUCCES;
}


int deikstra(graph_t *graph, int start_node, int end_node, linked_list_t *path)
{
    int ways_len[graph->node_count];
    int is_setted[graph->node_count];

    linked_list_t *all_path = NULL;
    create_array(&all_path, graph->node_count, sizeof(linked_list_t));
    //all_path[end_node - 1] = *path;
    for (int i = 0; i < graph->node_count; i++)
    {
        set_null_list(&(all_path[i]));
        ways_len[i] = INT32_MAX;
        is_setted[i] = 0;
    }
    ways_len[start_node - 1] = 0;


    int res = 0;
    int pos = 0;
    sum_elements(&is_setted, graph->node_count, sizeof(int), &res, int_sum);
    while (res != graph->node_count - 1)
    {
        res = -1;
        for (int i = 0; i < graph->node_count; i++)
        {
            if (is_setted[i] == 0)
            {
                if (ways_len[i] < res || res == -1)
                {
                    res = (ways_len[i]);
                    pos = i;
                }
            }
        }
        if (pos != -1)
        {
            is_setted[pos] = 1;
        }

        for (int i = 0; i < graph->edge_count; i++)
        {
            if ((graph->edges)[i]->first == pos + 1 && is_setted[(graph->edges)[i]->second - 1] == 0)
            {
                if (ways_len[pos] != INT32_MAX && ways_len[(graph->edges)[i]->second - 1] > ways_len[pos] + (graph->edges)[i]->lenght)
                {
                    ways_len[(graph->edges)[i]->second - 1] = ways_len[pos] + (graph->edges)[i]->lenght;

                    copy_linked_list(all_path + (graph->edges)[i]->second - 1,  all_path + pos);
                    add_element(all_path + (graph->edges)[i]->second - 1, (graph->edges)[i]);
                }
            }
            else if ((graph->edges)[i]->second == pos + 1 && is_setted[(graph->edges)[i]->first - 1] == 0)
            {
                if (ways_len[pos] != INT32_MAX && ways_len[(graph->edges)[i]->first - 1] > ways_len[pos] + (graph->edges)[i]->lenght)
                {
                    ways_len[(graph->edges)[i]->first - 1] = ways_len[pos] + (graph->edges)[i]->lenght;

                    copy_linked_list(all_path + (graph->edges)[i]->first - 1,  all_path + pos);
                    add_element(all_path + (graph->edges)[i]->first - 1, (graph->edges)[i]);
                }
            }
            
        }
        sum_elements(&is_setted, graph->node_count, sizeof(int), &res, int_sum);
    }

    copy_linked_list(path, all_path + end_node - 1);

    return ways_len[end_node - 1];
}

int edge_compare(void *first, void *second)
{
    edge_t *fir = first;
    edge_t *sec = second;

    if (fir && sec)
    {
        if (fir->first == sec->first && fir->second == sec->second && fir->lenght == sec->lenght && fir->road_type == sec->road_type)
        {
            return 0;
        }
        else
        {
            return 1;
        }
        
    }

    return 1;
}

int is_edge_exist(edge_t **edges, int edge_count,  edge_t *edge)
{
    return find_in_array(edges, edge_count, sizeof(edge_t*), &edge, edge_compare) != -1;
}

int is_edge_in_path(edge_t *edge, linked_list_t *path)
{
    int res = 0;
    for (int i = 0; i < path->size; i++)
    {

        edge_t *ed = get_element(path, i);
        if (!(edge_compare(edge, ed)))
        {
            res = 1;
            break;
        }
    }

    return res;
}

int is_node_trans(int node, linked_list_t *path)
{
    int res = 0;
    if (path && path->size)
    {
        edge_t *prev = NULL;
        int prev_node_1;
        int prev_node_2;
        enum road_type_t prev_type;
        prev = get_element(path, 0);
        prev_node_1 = prev->first;
        prev_node_2 = prev->second;
        prev_type = prev->road_type; 

        for (int i = 1; i < path->size; i++)
        {
            prev = get_element(path, i);
            if (prev_type != prev->road_type)
            {
                if (prev_node_1 == node)
                {
                    if (prev->first == prev_node_1 || prev->second == prev_node_1)
                    {
                        return 1;
                    }
                }
                else if (prev_node_2 == node)
                {
                    if (prev->first == prev_node_2 || prev->second == prev_node_2)
                    {
                        return 1;
                    }
                }
            }

            prev_node_1 = prev->first;
            prev_node_2 = prev->second;
            prev_type = prev->road_type; 
        }
    }
    return res;
}

int print_graph_file(FILE *out, graph_t *graph, linked_list_t *path)
{
    fprintf(out, "graph { \n\trankdir=LR; \n");

    for (int i = 1; i <= graph->node_count; i++)
    {
        if (!is_node_trans(i, path))
        {
            fprintf(out, "%d;\n", i);
        }
        else
        {
            fprintf(out, "%d [shape=box];\n", i);
        }
        
    }
    for (int i = 0; i < graph->edge_count; i++)
    {
        if (!is_edge_in_path(graph->edges[i], path))
        {
            fprintf(out, "\t%d -- %d [label=%d\n", graph->edges[i]->first, graph->edges[i]->second, graph->edges[i]->lenght);
            if (graph->edges[i]->road_type == railway)
            {
                fprintf(out, ", style=dotted");
            }
            fprintf(out, "];\n");
        }
    }
    for (int i = 0; i < path->size; i++)
    {
        fprintf(out, "\t%d -- %d [label=%d, color=blue", ((edge_t *)get_element(path, i))->first, ((edge_t *)get_element(path, i))->second, \
        ((edge_t *)get_element(path, i))->lenght);
        if (((edge_t *)get_element(path, i))->road_type == railway)
        {
            fprintf(out, ", style=dotted");
        }
        fprintf(out, "];\n");
    }

    fprintf(out, "}\n");

    return SUCCES;
}