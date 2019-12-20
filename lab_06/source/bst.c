#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "error_codes.h"
#include "universal.h"

void set_null_bst(bst_t *tree)
{
    if (tree)
    {
        tree->root = NULL;
    }
}

void delete_bst_by_root(bst_node_t* root)
{
    if (root)
    {
        delete_bst_by_root(root->l_son);
        delete_bst_by_root(root->r_son);
        if (root->father)
        {
            if (root->father->l_son == root)
            {
                root->father->l_son = NULL;
            }
            else
            {
                root->father->r_son = NULL;
            }
            
        }
        delete_bst_node(root, free);
    }
}
int add_element(bst_t *tree, void *data_p, int compare(void*, void*), int *comp_times)
{
    int error_code = INCORRECT_INPUT;
    if (data_p)
    {
        error_code = SUCCES;
        *comp_times = 1;
        if (tree->root)
        {
            add_element_at_parent(tree->root, data_p, compare, comp_times);
        }
        else
        {
            tree->root = create_bst_node(data_p);
            if (!(tree))
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

void delete_bst_node(bst_node_t *node, void destructor(void*))
{
    if (node)
    {
        destructor(node->data_p);
    }
    free(node);
}

void set_null_bst_node(bst_node_t *node)
{
    if (node)
    {
        node->data_p = NULL;
        node->height = 1;

        node->father = NULL;
        node->l_son = NULL;
        node->r_son = NULL;
    }
}

int add_element_at_parent(bst_node_t *parent, void *data_p, int compare(void*, void*), int *cmp)
{
    int error_code = INCORRECT_INPUT;
    if (parent && data_p)
    {
        error_code = SUCCES;
        if (compare(data_p, parent->data_p) < 0)
        {
            *cmp += 1;
            if (parent->l_son)
            {
                add_element_at_parent(parent->l_son, data_p, compare, cmp);
            }
            else
            {
                parent->l_son = create_bst_node(data_p);
                if (parent->l_son)
                {
                    parent->l_son->father = parent;
                    //update_height_up(parent->l_son);
                }
                else
                {
                    error_code = MEMORY_ERROR;
                }
            }
        }
        else if (compare(data_p, parent->data_p) > 0)
        {
            *cmp += 2;
            if (parent->r_son)
            {
                add_element_at_parent(parent->r_son, data_p, compare, cmp);
            }
            else
            {
                parent->r_son = create_bst_node(data_p);
                if (parent->r_son)
                {
                    parent->r_son->father = parent;
                    //update_height_up(parent->r_son);
                }
                else
                {
                    error_code = MEMORY_ERROR;
                }
            }
        }
    }

    return error_code;
}

int update_height_up(bst_node_t *son)
{
    int error_code = INCORRECT_INPUT;
    if (son)
    {
        error_code = SUCCES;
        if (son->father)
        {
            int l_height = -1;
            int r_height = -1;
            if (son->father->l_son)
            {
                l_height = son->father->l_son->height;
            }
            if (son->father->r_son)
            {
                r_height = son->father->r_son->height;
            }

            if (l_height > r_height)
            {
                son->father->height = l_height + 1;
            }
            else
            {
                son->father->height = r_height + 1;
            }
            
        }
    }

    return error_code;
}

bst_node_t *find_element(bst_node_t *root, void *data_p, int compare(void*, void*), int *cmp)
{
    bst_node_t *result = NULL;
    if (root && data_p)
    {
        result = root;
        *cmp += 1;
        if (compare(data_p, root->data_p) < 0)
        {
            if (root->l_son)
            {
                result = find_element(root->l_son, data_p, compare, cmp);
            }
            else
            {
                result = NULL;
            }
        }
        else if (compare(data_p, root->data_p) > 0)
        {
            *cmp += 1;
            if (root->r_son)
            {
                result = find_element(root->r_son, data_p, compare, cmp);
            }
            else
            {
                result = NULL;
            }
        }
    }

    return result;
}

bst_node_t *delete_element(bst_node_t *target_node)
{
    bst_node_t *temp_node = NULL;
    if (target_node && (target_node->l_son || target_node->r_son || target_node->father))
    {
        temp_node = NULL;
        if (target_node->l_son)
        {
            temp_node = target_node->l_son;
            while (temp_node->r_son)
            {
                temp_node = temp_node->r_son;
            }
            temp_node->father->r_son = NULL;
        }
        else if (target_node->r_son)
        {
            temp_node = target_node->r_son;
            while (temp_node->l_son)
            {
                temp_node = temp_node->l_son;
            }
            temp_node->father->l_son = NULL;

        }
        else if (target_node->father)
        {
            if (target_node->father->l_son == target_node)
            {
                target_node->father->l_son = NULL;
            }
            else
            {
                target_node->father->r_son = NULL;
            }
            delete_bst_node(target_node, free);
        }
        else
        {
            delete_bst_node(target_node, free);
        }
        
        //temp_node->height = -1;
        //update_height_up(temp_node);

        if (temp_node)
        {
            temp_node->father = target_node->father;
            if (target_node->father && target_node->father->l_son == target_node)
            {
                target_node->father->l_son = temp_node;
            }
            else if (target_node->father)
            {
                target_node->father->r_son = temp_node;
            }
            temp_node->height = target_node->height;
            if (temp_node != target_node->l_son)
            {
                temp_node->l_son = target_node->l_son;
            }

            if (temp_node != target_node->r_son)
            {
                temp_node->r_son = target_node->r_son;
            }
            
            if (temp_node->r_son)
            {
                temp_node->r_son->father = temp_node;
            }
            if (temp_node->l_son)
            {
                temp_node->l_son->father = temp_node;
            }
            
            delete_bst_node(target_node, free);
        }
        
    }
    return temp_node;
}

void print_tree_prefix(bst_node_t *root, void print(void*))
{
    if (root)
    {
        print(root->data_p);
        printf(" ");
        print_tree_prefix(root->l_son, print);
        print_tree_prefix(root->r_son, print);
    }
}

void print_tree_postfix(bst_node_t *root, void print(void*))
{
    if (root)
    {
        print_tree_postfix(root->l_son, print);
        print_tree_postfix(root->r_son, print);
        print(root->data_p);
        printf(" ");
    }
}

void print_tree_infix(bst_node_t *root, void print(void*))
{
    if (root)
    {
        print_tree_infix(root->l_son, print);
        print(root->data_p);
        printf(" ");
        print_tree_infix(root->r_son, print);
    }
}

void print_tree_graph(bst_node_t *tree, int level, int is_left)
{
    if (tree)
    {
        print_tree_graph(tree->r_son, level + 1, 1);
        for(int i = 0; i < level; i++)
        {
            printf("   ");
        }
        /* 
        if (is_left)
        {
            printf("/");
        }
        else
        {
            printf("\\");
        }
        */
        
        printf("%3d\n", *((int*)tree->data_p));
        print_tree_graph(tree->l_son, level + 1, 0);
    }
}

void fill_tree(bst_t *tree, FILE *source)
{
    int *cur_digit = (int*)malloc(sizeof(int));
    int cmp = 0;
    while (fscanf(source, "%d", cur_digit) == 1)
    {
        add_element(tree, cur_digit, int_compare, &cmp);
        cur_digit = (int*)malloc(sizeof(int));
    }
    free(cur_digit);
}