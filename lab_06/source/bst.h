#ifndef __BST_H__
#define __BST_H__

#include <stdio.h>

struct bst_node_t
{
    int data;
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

void set_null_bst(bst_t *tree);
int add_element(bst_t *tree, int data, int *comp_times);
bst_node_t *find_element(bst_node_t *root, int data, int *cmp);
bst_node_t *delete_element(bst_node_t *target_node);

void print_tree_prefix(bst_node_t *root);
void print_tree_postfix(bst_node_t *root);
void print_tree_infix(bst_node_t *root);

void print_tree_graph(bst_node_t *tree, int level, int is_left);

void fill_tree(bst_t *tree, FILE *source);
int copy_tree(bst_t *dest, bst_t *source);

bst_node_t *create_bst_node(int data);
void delete_bst_node(bst_node_t *node);

void del_bst(bst_node_t *tree);
void set_null_bst_node(bst_node_t *node);
int update_height_up(bst_node_t *son);
int add_element_at_parent(bst_node_t *parent, int data, int *cmp);
#endif