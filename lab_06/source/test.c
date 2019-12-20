#include "test.h"
#include "avl.h"
#include "bst.h"
#include "universal.h"
#include "hash_table.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FILE_TEMP "temp_file.txt"
unsigned long int tick(void)
{
    unsigned long int d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d) );
    return d;
}

void efficiency(int len)
{
    srand(time(NULL));
    FILE *f = fopen(FILE_TEMP, "w");
    for (int i = 0; i < len; i++)
    {
        fprintf(f, "%d ", abs((int) (rand() * len * 1000)));
    }
    fclose(f);

    bst_t avl_tree;
    bst_t bs_tree;
    hash_table_t hash;

    set_null_bst(&bs_tree);
    set_null_bst(&avl_tree);
    create_hash_table(&hash, len, 13);

    int temp_int = 0;

    clock_t start = clock();
    clock_t end = 0;

    int64_t cmp_full = 0;
    int cmp = 0;
    int iter = 0;
    f = fopen(FILE_TEMP, "r");
    clock_t start_malloc;
    clock_t end_malloc;

    int collis_pred = 0;
    printf("Input max count of compare: ");
    scanf("%d", &collis_pred);
    printf("\n");

    double correction = 0;
    int *temp_intp = (int*)malloc(sizeof(int));
    while (fscanf(f, "%d", temp_intp) == 1)
    {
        iter++;
        cmp = 0;
        add_to_hash_table(&hash, temp_intp, &cmp, collis_pred);
        cmp_full += cmp;
        start_malloc = clock();
        temp_intp = (int*)malloc(sizeof(int));
        end_malloc = clock();
        correction += (end_malloc - start_malloc);
    }
    end = clock();
    double diff = end - start - correction;
    printf("Hash table:\nElements: %d\nMiddle compare: %lf\nMiddle time: %lf\nFull time: %lf\n", iter, \
                        cmp_full / (double)iter, diff / (double)iter, diff);
    
    //print_hash_table(&hash);
    //delete_hash_table(&hash);

    fclose(f);
    f = fopen(FILE_TEMP, "r");
    int uniq_elem = len;
    cmp_full = 0;

    start = clock();
    iter = 0;
    while (fscanf(f, "%d", &temp_int) == 1)
    {
        iter++;
        cmp = 0;
        add_element(&bs_tree, temp_int, &cmp);
        cmp_full += cmp;
    }
    end = clock();
    printf("\nBST:\nElements: %d\nMiddle compare: %lf\nMiddle time: %lf\nFull time: %ld\n", iter, \
                        (double)cmp_full / (double)iter, (double)(end - start) / (double)iter, end - start);
    //del_bst(bs_tree.root);

    fclose(f);
    f = fopen(FILE_TEMP, "r");
    start = clock();
    cmp_full = 0;
    iter = 0;
    while (fscanf(f, "%d", &temp_int) == 1)
    {
        iter++;
        cmp = 0;
        avl_tree.root = insert(avl_tree.root, temp_int, &cmp);
        cmp_full += cmp;
    }

    //print_tree_graph(avl_tree.root, 0, 0);
    end = clock();
    printf("\nAVL:\nElements: %d\nMiddle compare: %lf\nMiddle time: %lf\nFull time: %ld\n", iter, \
                        cmp_full / (double)iter, (double)(end - start) / iter, end - start);
    //del_bst(avl_tree.root);
    fclose(f);
    f = fopen(FILE_TEMP, "r");



//*** find find
    start = clock();
    cmp_full = 0;
    iter = 0;
    while (fscanf(f, "%d", temp_intp) == 1)
    {
        iter++;
        cmp = 0;
        find_element_in_hash_table(&hash, temp_intp, &cmp);
        cmp_full += cmp;
    }
    end = clock();
    diff = end - start;
    printf("\n\n\nFind test\nHash table find:\nElements: %d\nMiddle compare: %lf\nMiddle time: %lf\nFull time: %lf\n", iter, \
                        cmp_full / (double)iter, diff / (double)iter, diff);
    
    //print_hash_table(&hash);
    delete_hash_table(&hash);

    fclose(f);



    f = fopen(FILE_TEMP, "r");
    cmp_full = 0;

    start = clock();
    iter = 0;
    while (fscanf(f, "%d", &temp_int) == 1)
    {
        iter++;
        cmp = 0;
        find_element(bs_tree.root, temp_int, &cmp);
        cmp_full += cmp;
    }
    end = clock();
    printf("\nBST find:\nElements: %d\nMiddle compare: %lf\nMiddle time: %lf\nFull time: %ld\n", iter, \
                        (double)cmp_full / (double)iter, (double)(end - start) / (double)iter, end - start);
    del_bst(bs_tree.root);

    fclose(f);
    f = fopen(FILE_TEMP, "r");
    start = clock();
    cmp_full = 0;
    iter = 0;
    while (fscanf(f, "%d", &temp_int) == 1)
    {
        iter++;
        cmp = 0;
        find_element(avl_tree.root, temp_int, &cmp);
        cmp_full += cmp;
    }

    //print_tree_graph(avl_tree.root, 0, 0);
    end = clock();
    printf("\nAVL find:\nElements: %d\nMiddle compare: %lf\nMiddle time: %lf\nFull time: %ld\n", iter, \
                        cmp_full / (double)iter, (double)(end - start) / iter, end - start);
    del_bst(avl_tree.root);
    fclose(f);
}