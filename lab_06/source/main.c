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
    int *temp_int_p = NULL;
    int *temp_int_p2 = NULL;
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
                    set_null_bst(&avl);
                    balance_bst_to_avl(tree.root, &avl);
                    fseek(source, SEEK_SET, 0);
                    set_null_bst(&tree);
                    fill_tree(&tree, source);
                    fclose(source);
                    break;
                case 2:
                avl.root = balance(avl.root);
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
                    break;
                case 5:
                    print_tree_prefix(tree.root, print_int);
                    printf("\n");
                    break;
                case 6:
                    print_tree_infix(tree.root, print_int);
                    printf("\n");
                    break;
                case 7:
                    print_tree_postfix(tree.root, print_int);
                    printf("\n");
                    break;
                case 8:
                printf("Input integer to find, pls: ");
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
                else
                {
                    printf("Incorrect input\n");
                }
                
                    break;
                case 9:
                    printf("Input integer to add, pls: ");
                    temp_int_p = (int*)malloc(sizeof(int));
                    if (scanf("%d", temp_int_p) == 1)
                    {
                        insert(avl.root, temp_int_p, int_compare);
                        temp_int_p2 = (int *)malloc(sizeof(int));

                        *temp_int_p2 = *temp_int_p;
                        add_to_hash_table(&hash, temp_int_p2);

                        temp_int_p = (int *)malloc(sizeof(int));
                        *temp_int_p = *temp_int_p2;
                        if (add_element(&tree, temp_int_p, int_compare))
                        {
                            printf("Element added\n");
                        }
                    }
                else
                {
                    free(temp_int_p);
                    printf("Incorrect input\n");
                }
                    temp_int_p = NULL;
                    break;
                case 10:
                printf("Input integer to delete, pls: ");
                    temp_int_p = (int*)malloc(sizeof(int));
                    if (scanf("%d", temp_int_p) == 1)
                    {
                        avl.root = remove_avl(avl.root, temp_int_p, int_compare);
                        del_element_in_hash_table(&hash, temp_int_p);
                        if (delete_element(find_element(tree.root, temp_int_p, int_compare)))
                        {
                            printf("Element deleted\n");
                        }
                        else
                        {
                            printf("Element doesnt found\n");
                        }
                    }
                else
                {
                    free(temp_int_p);
                    printf("Incorrect input\n");
                }
                    temp_int_p = NULL;
                    break;
                case 11:
                    source = fopen(TREE_FILE, "r");
                    delete_hash_table(&hash);
                    create_hash_table(&hash, 0, 13);
                    parse_file_hash_table(&hash, source);
                    fclose(source);
                    break;
                case 12:
                    print_hash_table(&hash);
                    break;
                case 13:
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
            "4  - print AVL tree pseudographiacal\n"
            "5  - print tree prefix\n"
            "6  - print tree infix\n"
            "7  - print tree postfix\n\n"
            "8  - find integer in structs\n"
            "9  - add integer to structs\n"
            "10  - delete integer from structs\n\n"
            "11  - make hash table from file\n"
            "12  - print hash table\n"
            "13  - restructurasing hash table\n\n"
            "14 - modeling\n");
}