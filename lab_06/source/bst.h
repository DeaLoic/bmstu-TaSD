#ifndef __BST_H__
#define __BST_H__

#include <stdio.h>

struct bst_node_t
{
    void *data_p;
    int height;
    struct bst_node_t *father;
    struct bst_node_t *l_son;
    struct bst_node_t *r_son;
};

typedef struct bst_node_t bst_node_t;

typedef struct bst_t
{
    bst_node_t *root;
} bst_t;

int add_element(bst_t *tree, void *data_p, int compare(void*, void*));
bst_node_t *find_element(bst_node_t *root, void *data_p, int compare(void*, void*));
bst_node_t *delete_element(bst_node_t *target_node);

void print_tree_prefix(bst_node_t *root, void print(void*));
void print_tree_postfix(bst_node_t *root, void print(void*));
void print_tree_infix(bst_node_t *root, void print(void*));

int print_tree_graph(bst_t *tree);

int fill_tree(bst_t *tree, FILE *source);
int copy_tree(bst_t *dest, bst_t *source);
#endif