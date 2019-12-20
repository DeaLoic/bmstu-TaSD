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
        delete_bst_node(root);
    }
}
int add_element(bst_t *tree, int data, int *comp_times)
{
    int error_code = INCORRECT_INPUT;
    if (1)
    {
        error_code = SUCCES;
        *comp_times = 1;
        if (tree->root)
        {
            add_element_at_parent(tree->root, data, comp_times);
        }
        else
        {
            tree->root = create_bst_node(data);
            if (!(tree))
            {
                error_code = MEMORY_ERROR;
            }
        }
    }

    return error_code;
}

bst_node_t *create_bst_node(int data)
{
    bst_node_t* new_node = (bst_node_t*)malloc(sizeof(bst_node_t));
    if (new_node)
    {
        set_null_bst_node(new_node);
        new_node->data = data;
    }
    return new_node;
}

void delete_bst_node(bst_node_t *node)
{
    free(node);
}

void set_null_bst_node(bst_node_t *node)
{
    if (node)
    {
        node->data = 0;
        node->height = 1;

        node->father = NULL;
        node->l_son = NULL;
        node->r_son = NULL;
    }
}

int add_element_at_parent(bst_node_t *parent, int data, int *cmp)
{
    int error_code = INCORRECT_INPUT;
    if (parent)
    {
        error_code = SUCCES;
        if (data < parent->data)
        {
            *cmp += 1;
            if (parent->l_son)
            {
                add_element_at_parent(parent->l_son, data, cmp);
            }
            else
            {
                parent->l_son = create_bst_node(data);
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
        else if (data > parent->data)
        {
            *cmp += 2;
            if (parent->r_son)
            {
                add_element_at_parent(parent->r_son, data, cmp);
            }
            else
            {
                parent->r_son = create_bst_node(data);
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

void del_bst(bst_node_t *tree)
{
    if (tree)
    {
        del_bst(tree->l_son);
        del_bst(tree->r_son);
        free(tree);
    }
}

bst_node_t *find_element(bst_node_t *root, int data, int *cmp)
{
    bst_node_t *result = NULL;
    if (root)
    {
        result = root;
        *cmp += 1;
        if (data < root->data)
        {
            if (root->l_son)
            {
                result = find_element(root->l_son, data, cmp);
            }
            else
            {
                result = NULL;
            }
        }
        else if (data > root->data)
        {
            *cmp += 1;
            if (root->r_son)
            {
                result = find_element(root->r_son, data, cmp);
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
            delete_bst_node(target_node);
        }
        else
        {
            delete_bst_node(target_node);
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
            
            delete_bst_node(target_node);
        }

    }
    return temp_node;
}

void print_tree_prefix(bst_node_t *root)
{
    if (root)
    {
        printf("%d", root->data);
        printf(" ");
        print_tree_prefix(root->l_son);
        print_tree_prefix(root->r_son);
    }
}

void print_tree_postfix(bst_node_t *root)
{
    if (root)
    {
        print_tree_postfix(root->l_son);
        print_tree_postfix(root->r_son);
        printf("%d", root->data);
        printf(" ");
    }
}

void print_tree_infix(bst_node_t *root)
{
    if (root)
    {
        print_tree_infix(root->l_son);
        printf("%d", root->data);
        printf(" ");
        print_tree_infix(root->r_son);
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
        
        printf("%3d\n", tree->data);
        print_tree_graph(tree->l_son, level + 1, 0);
    }
}

void fill_tree(bst_t *tree, FILE *source)
{
    int cur_digit = 0;
    int cmp = 0;
    while (fscanf(source, "%d", &cur_digit) == 1)
    {
        add_element(tree, cur_digit, &cmp);
    }
}