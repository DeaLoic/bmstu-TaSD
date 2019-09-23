#include <stdio.h>
#include <stdlib.h>
#include "longNumber.h"
#include "longAriph.h"
#include "errorCodes.h"

#define RELEASE 1    // For information messages
#define DEBUG 0      // For debug messages

void printIntRule(void);
void printDoubleRule(void);
void printMainRule(void);
void printSymbolTip(void);
void printInputError(void);
void printMultiplyError(void);

int main(void)
{
    int errorCode = SUCCES;

    longNumber int_number;
    longNumber dbl_number;
    
    // Set zero in numbers
    setZero(&int_number);
    setZero(&dbl_number);

    // Print information
    if (RELEASE)
    {
        printMainRule();
        printf("\n");
        printIntRule();
        printSymbolTip();
    }

    // Input integer number
    inputNumberInt(&int_number, &errorCode);

    if (!errorCode)
    {
        // Delete possibly trash before input
        fflush(stdin);

        // Print information
        if (RELEASE)
        {
            printf("\n");
            printDoubleRule();
            printSymbolTip();
        }
        
        // Input real number
        inputNumberDbl(&dbl_number, &errorCode);
        
        // If numbers are correct
        if (!errorCode && (abs(dbl_number.exp) <= MAX_EXP))
        {
            if (DEBUG)
            {
                printf("\ni got:\n");
                printNumber(&int_number, &errorCode);
                printNumber(&dbl_number, &errorCode);
            }

            // Normalize numbers (remove dot from mantissa)
            normalizeNumber(&int_number);
            normalizeNumber(&dbl_number);

            if (DEBUG)
            {
                printf("\ni normalized that like this:\n");
                printNumber(&int_number, &errorCode);
                printNumber(&dbl_number, &errorCode);
            }

            // If normalize was correct
            if (!errorCode)
            {
                longNumber result;

                // Multiply numbers
                longMultiply(&int_number, &dbl_number, &result, &errorCode);

                // If multiply was correct
                if (!errorCode)
                {
                    if (DEBUG)
                    {
                        printf("\nResult dotpos: %d, len: %d, exp: %d\n",
                                result.dotPos, result.mantisaLen, result.exp);
                    }

                    if (RELEASE)
                    {
                        printf("\nResult of multiply:\n");
                    }

                    // Print number in requirment format
                    printNumber(&result, &errorCode);

                    if (errorCode)
                    {
                        // If overflow exponent
                        if (abs(result.exp) > MAX_EXP)
                        {
                            printf("Exponent too large\n");
                        }
                        
                        // Print error message
                        printMultiplyError();
                    }
                }
                else
                {
                    printMultiplyError();
                }
            }
            else
            {
                printf("ERROR");
            }
        }
        else
        {
            printInputError();
        }
    }
    else
    {
        printInputError();
    }

    fflush(stdin);
    getchar();
    
    return errorCode;
}

void printIntRule(void)
{
    printf("input integer\nFormat (reduce spaces): +/- m1, where len(m1) <= 30\n");
}
void printDoubleRule(void)
{
    printf("input real\nFormat (reduce spaces): +/- m.n e/E r1, where len(m + n) <= 30 and len(r1) <= 5: \n");
}
void printMainRule(void)
{
    printf("pls, input integer and real number:\n");
}
void printSymbolTip(void)
{
    printf("|------------------------------|30\n");
}
void printInputError(void)
{
    printf("Wrong input!\n");
}
void printMultiplyError(void)
{
    printf("I cant multiply it\n");
}