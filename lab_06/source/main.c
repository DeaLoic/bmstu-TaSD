#include "bst.h"
#include "avl.h"
#include <stdio.h>
#include "error_codes.h"
#include "universal.h"

#define TREE_FILE "tree.txt"

void menu();

int main()
{
    int error_code = SUCCES;
    bst_t tree;
    bst_t avl;
    set_null_bst(&tree);
    set_null_bst(&avl);
    bst_node_t *temp;
    FILE *source = NULL;
    int choose = 1;
    while (choose != 0)
    {
        //menu();
        scanf("%d", &choose);
        switch (choose)
        {
        case 1:
            source = fopen(TREE_FILE, "r");
            fill_tree_avl(&tree, source);
            fclose(source);
            break;
        case 2:
            balance_bst_to_avl(tree.root, avl.root);
            tree.root = avl.root;
            break;
        case 3:
            print_tree_graph(tree.root, 0, 0);
            printf("\n");
            break;
        case 4:
            print_tree_prefix(tree.root, print_int);
            printf("\n");
            break;
        case 5:
            print_tree_infix(tree.root, print_int);
            printf("\n");
            break;
        case 6:
            print_tree_postfix(tree.root, print_int);
            printf("\n");
            break;
        case 7:
            temp = tree.root;
            while (temp)
            {
                printf("%p\n", temp);
                temp = temp->r_son;
            }
            break;
        case 8:
            /* code */
            break;
        case 9:
            /* code */
            break;
        
        default:
            break;
        }

    }
    return error_code;
}

void menu()
{
    printf("0 - exit\n\n"
            "1 - make tree from file\n"
            "2 - balance tree to avl\n\n"
            "3 - print tree pseudographiacal\n"
            "4 - print tree prefix\n"
            "5 - print tree infix\n"
            "6 - print tree postfix\n\n"
            "7 - make hash table from file\n"
            "8 - restructurasing hash table\n\n"
            "9 - modeling\n");
}