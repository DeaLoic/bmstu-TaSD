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
        menu();
        printf("Your choice: ");
        if (scanf("%d", &choose) == 1);
        {
            system("clear");
            switch (choose)
            {
                case 1:
                    source = fopen(TREE_FILE, "r");
                    set_null_bst(&tree);
                    fill_tree(&tree, source);
                    fclose(source);
                    break;
                case 2:
                    balance_bst_to_avl(tree.root, &avl);
                    tree.root = avl.root;
                    set_null_bst(&avl);
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
                if (scanf("%d", &choose) == 1)
                {
                    if (find_element(tree.root, &choose, int_compare))
                    {
                        printf("Element found");
                    }
                    else
                    {
                        printf("Element doesnt found");
                    }
                }
                    break;
                case 8:
                    /* code */
                    break;
                case 9:
                    /* code */
                    break;
                case 0:
                    break;
                default:
                    printf("Pls, choose one of menu points");
                    break;
            }
        }

    }
    return error_code;
}

void menu()
{
    printf("0  - exit\n\n"
            "1  - make tree from file\n"
            "2  - balance tree to avl\n\n"
            "3  - print tree pseudographiacal\n"
            "4  - print tree prefix\n"
            "5  - print tree infix\n"
            "6  - print tree postfix\n\n"
            "7  - find integer in tree\n"
            "8  - add integer to tree\n"
            "9  - delete integer from tree\nn"
            "10  - make hash table from file\n"
            "11  - restructurasing hash table\n\n"
            "12 - modeling\n");
}