#include "bst.h"
#include "avl.h"
#include "hash_table.h"
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
    hash_table_t hash;
    create_hash_table(&hash, 0, 13);
    FILE *source = NULL;
    int choose = 1;
    while (choose != 0)
    {
        menu();
        printf("Your choice: ");
        if (scanf("%d", &choose) == 1)
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
                    break;
                case 3:
                    printf("Binary Search tree (AVL)\n");
                    print_tree_graph(tree.root, 0, 0);
                    printf("\n");
                    break;
                case 4:
                    printf("Balancing tree (AVL)\n");
                    print_tree_graph(avl.root, 0, 0);
                    printf("\n");
                case 122:
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
                        printf("Element found in tree\n");
                    }
                    else
                    {
                        printf("Element doesnt found\n");
                    }
                }
                    break;
                case 8:
                    /* code */
                    break;
                case 9:
                    /* code */
                    break;
                case 10:
                    source = fopen(TREE_FILE, "r");
                    delete_hash_table(&hash);
                    parse_file_hash_table(&hash, source);
                    fclose(source);
                    break;
                case 11:
                    print_hash_table(&hash);
                    break;
                case 12:
                    printf("Input new basis to function (basis > 0): ");
                    if (scanf("%d", &choose) == 1)
                    {
                        change_basis(&hash, choose);
                    }
                    else
                    {
                        printf("Invalid basis\n");
                    }
                    
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
            "7  - find integer in structs\n"
            "8  - add integer to structs\n"
            "9  - delete integer from structs\n\n"
            "10  - make hash table from file\n"
            "11  - print hash table\n"
            "12  - restructurasing hash table\n\n"
            "13 - modeling\n");
}