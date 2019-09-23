#include <stdio.h>

void swapDbl(double* first, double* second)
{
    double temp = *first;
    *first = *second;
    *second = temp;
}

void swapInt(int* first, int* second)
{
    int temp = *first;
    *first = *second;
    *second = temp;
}

void printIntArray(int* array, int len)
{
    printf("%d", array[0]);
    for (int i = 1; i < len; i++)
    {
        printf(" %d", array[i]);
    }
    printf("\n");
}