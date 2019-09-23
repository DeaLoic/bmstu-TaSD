#include "longAriph.h"
#include "longNumber.h"
#include "universal.h"
#include <stdlib.h>
#include <stdio.h>

#define DEBUG_ARIPH 1

void longMultiply(longNumber* numberFirst, longNumber* numberSecond, longNumber* result, int* errorCode)
{
    int* temp = (int*)calloc((MAX_MANTISA * 2), sizeof(int));

    setEmpty(result);

    if (DEBUG_ARIPH)
    {
        printf("First mantisa: ");
        printIntArray(numberFirst->mantisa, MAX_MANTISA);
        printf("\nSecond mantisa: ");
        printIntArray(numberSecond->mantisa, MAX_MANTISA);
    }

    // Multiply to len * 2 array
    for (int i = MAX_MANTISA - 1; i >= MAX_MANTISA - numberFirst->mantisaLen; i--)
    {
        for (int j = MAX_MANTISA - 1; j >= MAX_MANTISA - numberSecond->mantisaLen; j--)
        {
            temp[i + j + 1] += numberSecond->mantisa[j] * numberFirst->mantisa[i];
        }
    }

    // Normalize result to base 10 system
    normalizeBase10(temp, MAX_MANTISA * 2);

    if (DEBUG_ARIPH)
    {
        printf("\nres after normalize: ");
        printIntArray(temp, MAX_MANTISA * 2);
    }

    int delSymbs = countLeadingZero(temp, MAX_MANTISA * 2);

    // rounding
    if (delSymbs < MAX_MANTISA)
    {
        rounding(temp, MAX_MANTISA * 2);
        delSymbs = countLeadingZero(temp, MAX_MANTISA * 2);

        result->mantisaLen = MAX_MANTISA;
        result->exp = MAX_MANTISA - delSymbs;
    }
    else
    {   
        delSymbs = MAX_MANTISA;
        result->mantisaLen = (MAX_MANTISA * 2 - delSymbs);
    }
    
    if (DEBUG_ARIPH)
    {
        printf("\ndel symb: %d", delSymbs);
        printf("\nround: ");
        printIntArray(temp, MAX_MANTISA * 2);
    }

    // Copy meaning part of number from temp to struct
    for (int i = 0; i < MAX_MANTISA; i++)
    {
        result->mantisa[i] = temp[delSymbs + i];
    }

    // Free memory
    free(temp);

    if (DEBUG_ARIPH)
    {
        printf("\nresult: ");
        printIntArray(result->mantisa, MAX_MANTISA);
        printf("\n exp in res: %d", result->exp);
    }

    delRightZero(result);
    
    if (DEBUG_ARIPH)
    {
        printf("\ndel: ");
        printIntArray(result->mantisa, MAX_MANTISA);
    }

    // Set result sign
    result->mantisaSign = 1;
    if (numberFirst->mantisaSign != numberSecond->mantisaSign)
    {
        result->mantisaSign = 0;
    }
    
    // Normalize
    result->dotPos = 0;
    result->exp += numberFirst->exp + numberSecond->exp + result->mantisaLen;
    countMantisLen(result);

    // Set exponent to 0 if mantisa == 0
    if (result->mantisaLen == 1 && result->mantisa[MAX_MANTISA - 1] == 0)
    {
        result->exp = 0;
    }
    // If was overflow in rounding - fix
    else if (result->mantisaLen == 1 && result->mantisa[MAX_MANTISA - 1] >= 10)
    {
        result->exp++;
        result->mantisa[MAX_MANTISA - 1] /= 10;
    }
}

void rounding(int* temp, int oldLen)
{
    for (int i = oldLen - 1; i > 0; i--)
    {
        if (temp[i] >= 5)
        {
            temp[i - 1] += (temp[i] + 5) / 10;
            temp[i] = 0;
        }
    }
}