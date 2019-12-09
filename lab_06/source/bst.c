#include <stdio.h>
#include "bst.h"
#include "error_codes.h"

bst_node_t *create_bst_node(void *data_p);
void set_null_bst_node(bst_node_t *node);
int increase_height_up(bst_node_t *son);
int add_element_at_parent(bst_node_t *parent, void *data_p, int compare(void*, void*));

int add_element_at_tree(bst_t *tree, void *data_p, int compare(void*, void*))
{
    int error_code = INCORRECT_INPUT;
    if (tree && data_p)
    {
        error_code = SUCCES;
        if (tree->root)
        {
            add_element_at_parent(tree->root, data_p, compare);
        }
        else
        {
            tree->root = create_bst_node(data_p);
            if (!(tree->root))
            {
                error_code = MEMORY_ERROR;
            }
        }
    }

    return error_code;
}

bst_node_t *create_bst_node(void *data_p)
{
    bst_node_t* new_node = (bst_node_t*)malloc(sizeof(bst_node_t));
    if (new_node)
    {
        set_null_bst_node(new_node);
        new_node->data_p = data_p;
    }
    return new_node;
}

void set_null_bst_node(bst_node_t *node)
{
    if (node)
    {
        node->data_p = NULL;
        node->height = 0;

        node->father = NULL;
        node->l_son = NULL;
        node->r_son = NULL;
    }
}

int 
int add_element_at_parent(bst_node_t *parent, void *data_p, int compare(void*, void*))
{
    int error_code = INCORRECT_INPUT;
    if (parent && data_p)
    {
        if (compare(data_p, parent->data_p) < 0)
        {
            if (parent->l_son)
            {
                add_element_at_parent(parent->l_son, data_p, compare);
            }
            else
            {
                parent->l_son = create_bst_node(data_p);
                if (parent->l_son)
                {
                    increase_height_up(parent->l_son);
                }
                else
                {
                    error_code = MEMORY_ERROR;
                }
            }
            
        }
    }
}
int increase_height_up(bst_node_t *son);

bst_node_t *find_element(bst_t *tree, void *data_p, int compare(void*, void*));
int delete_element(bst_t *tree, void *data_p, int compare(void*, void*));

int print_tree_prefix(bst_t *tree);
int print_tree_postfix(bst_t *tree);
int print_tree_infix(bst_t *tree);

int print_tree_graph(bst_t *tree);

int fill_tree(bst_t *tree, FILE *source);