#ifndef __AVL_H__
#define __AVL_H__

#include "bst.h"

int height(bst_node_t *p);
int b_factor(bst_node_t *p);
void fix_height(bst_node_t *p);

bst_node_t *rotate_right(bst_node_t *p); // правый поворот вокруг p
bst_node_t *rotate_left(bst_node_t *q); // левый поворот вокруг q
bst_node_t *balance(bst_node_t *p); // балансировка узла p
bst_node_t *insert(bst_t *p, void *data_p, int compare(void*, void*)); // вставка ключа k в дерево с корнем p
bst_node_t *find_min(bst_node_t *p); // поиск узла с минимальным ключом в дереве p
bst_node_t *remove_min(bst_node_t *p); // удаление узла с минимальным ключом из дерева p
bst_node_t *remove_avl(bst_node_t *p, void *data_p, int compare(void*, void*)); // удаление ключа k из дерева p

void balance_bst_to_avl(bst_node_t *root, bst_node_t *avl);

void fill_tree_avl(bst_t *tree, FILE *source);

#endif