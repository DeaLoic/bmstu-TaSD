#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "errorCodes.h"
#include "universal.h"

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

int inputString(FILE* f, char* string, int size)
{
    int errorCode = SUCCES;
    if (fgets(string, size, f) == NULL)
    {
        errorCode = INPUT_ERROR;
    }
    else
    {
        if (strlen(string) == size - 1 && (string[size - 2] != '\n') && !feof(f))
        {
            int tempChar = fgetc(f);
            if (tempChar != '\n')
            {
                ungetc(tempChar, f);
                errorCode = INPUT_ERROR;
            }
        }
        string[strcspn(string, "\n")] = '\0';
    }

    return errorCode;
}

int createRandomString(char* str, int len)
{
    if (len > 1)
    {
        char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?!";
        int key = 0;
        
        for (int n = 0; n < len; n++)
        {            
            key = rand() % (int)(sizeof(charset) - 1);
            str[n] = charset[key];
        }

            str[len] = '\0';
    }

    return SUCCES;
}