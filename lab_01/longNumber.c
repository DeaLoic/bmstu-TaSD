#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include "longNumber.h"
#include "errorCodes.h"

void printNumber(longNumber* number, int* errorCode)
{
    if (0 < number->mantisaLen && number->mantisaLen <= (MAX_MANTISA) &&
        0 <= abs(number->exp) && abs(number->exp) <= MAX_EXP)
    {
        if (number->mantisaSign)
        {
            printf("+");
        }
        else
        {
            printf("-");
        }
        
        for (int i = MAX_MANTISA - number->mantisaLen; i < MAX_MANTISA; i++)
        {
            if (i == (MAX_MANTISA - number->mantisaLen + number->dotPos))
            {
                if(i == MAX_MANTISA - number->mantisaLen)
                {
                    printf("0");
                }
                printf(".");
            }
            printf("%d", *(number->mantisa + i));
        }

        printf("E%+d\n", number->exp);
    }
    else
    {
        *errorCode = INCORRECT_INPUT;
    }
}

void setEmpty(longNumber* number)
{
    number->mantisaSign = 1;
    number->dotPos = -1;
    number->mantisaLen = 0;
    number->exp = 0;
    zeroMantis(number);
}

void inputMantisa(longNumber* number, int* errorCode)
{
    char temp;
    
    if (!feof(stdin) && fscanf(stdin, "%c", &temp))
    {
        if (temp == '-')
        {
            number->mantisaSign = 0;
        }
        else if (temp == '.')
        {
            number->mantisaSign = 1;
            number->dotPos = 0;
        }
        else if (isdigit(temp))
        {
            number->mantisaSign = 1;
            *(number->mantisa) = temp - '0';
            number->mantisaLen = 1;
        }
        else if (temp != '+')
        {
            *errorCode = INPUT_ERROR;
        }
        
        int isContinue = 1;

        while (!*errorCode && isContinue && !feof(stdin) && number->mantisaLen < (MAX_MANTISA) && fscanf(stdin, "%c", &temp))
        {
            if (isdigit(temp))
            {
                *(number->mantisa + number->mantisaLen) = temp - '0';
                number->mantisaLen += 1;
            }
            else if (temp == '.' && number->dotPos == -1)
            {
                number->dotPos = number->mantisaLen;
            }
            else if (temp == '.' || !number->mantisaLen)
            {
                *errorCode = INPUT_ERROR;
            }
            else
            {
                ungetc(temp, stdin);
                isContinue = 0;
            }
        }

        if (!*errorCode && MAX_MANTISA != number->mantisaLen)
        {
            for (int i = 0; i < number->mantisaLen; i++)
            {
                *(number->mantisa + (MAX_MANTISA - 1 - i)) = *(number->mantisa + number->mantisaLen - 1 - i);
                *(number->mantisa + number->mantisaLen - 1 - i) = 0;
            }
        }
    }
    else
    {
        *errorCode = INPUT_ERROR;
    }
}

void inputExp(longNumber* number, int* errorCode)
{
    char temp;

    if (!feof(stdin) && fscanf(stdin, "%c", &temp))
    {
        if ((temp != 'E' && temp != 'e') || feof(stdin) || !fscanf(stdin, "%d", &number->exp) ||\
         (fscanf(stdin, "%c", &temp) && !isspace(temp)))
        {
            *errorCode = INPUT_ERROR;
        }
    }
    else
    {
        *errorCode = INPUT_ERROR;
    }
}
void inputNumber(longNumber* number, int* errorCode)
{
    setEmpty(number);
    inputMantisa(number, errorCode);
    if (!*errorCode)
    {
        inputExp(number, errorCode);
    }
}

void setZero(longNumber* number)
{
    number->mantisaSign = 1;
    number->dotPos = -1;
    number->mantisaLen = 1;
    number->exp = 0;
    zeroMantis(number);
}

void delRightZero(longNumber* number)
{
    int i = MAX_MANTISA - 1;
    int countRightZero = 0;
    
    while (i > 0 && *(number->mantisa + i) == 0 && (number->mantisaLen > 1))
    {
        number->mantisaLen--;
        number->exp++;
        countRightZero++;
        i--;
    }
    
    if (countRightZero)
    {
        for (int k = MAX_MANTISA - 1; k > MAX_MANTISA - number->mantisaLen - 1; k--)
        {
            number->mantisa[k] = number->mantisa[k - countRightZero];
            number->mantisa[k - countRightZero] = 0;
        }
    }
}
void normalizeNumber(longNumber* number)
{
    if (number->dotPos != -1)
    {
        number->exp -= number->mantisaLen - number->dotPos;
    }
    number->dotPos = -1;

    delRightZero(number);
}

void countMantisLen(longNumber* number)
{
    int i = 0;
    while(*(number->mantisa + i) == 0 && i < MAX_MANTISA)
    {
        i++;
    }
    number->mantisaLen = MAX_MANTISA - i;
    if (number->mantisaLen == 0)
    {
        number->mantisaLen = 1;
    }
}

void deleteLeadingSymb(int* temp, int len, int cntSymb)
{
    for (int i = 0; i + cntSymb < len; i++)
    {
        temp[i] = temp[i + cntSymb];
    }
}

void zeroMantis(longNumber* number)
{
    for (int i = 0; i < MAX_MANTISA; i++)
    {
        *(number->mantisa + i) = 0;
    }
}

void inputNumberInt(longNumber* number, int* errorCode)
{
    setEmpty(number);
    char temp;

    if (!feof(stdin) && fscanf(stdin, "%c", &temp))
    {
        if (temp == '-')
        {
            number->mantisaSign = 0;
        }
        else if (isdigit(temp))
        {
            number->mantisaSign = 1;
            *(number->mantisa) = temp - '0';
            number->mantisaLen = 1;
        }
        else if (temp != '+')
        {
            *errorCode = INPUT_ERROR;
        }
        
        int isContinue = 1;
        while (!*errorCode  && isContinue && !feof(stdin) && number->mantisaLen < (MAX_MANTISA) && fscanf(stdin, "%c", &temp) )
        {
            if (isdigit(temp))
            {
                *(number->mantisa + number->mantisaLen) = temp - '0';
                number->mantisaLen += 1;
            }
            else if (number->mantisaLen && isspace(temp))
            {
                isContinue = 0;
            }
            else
            {
                *errorCode = INPUT_ERROR;
            }

        }
        
        if (number->mantisaLen == (MAX_MANTISA) && !feof(stdin) && fscanf(stdin, "%c", &temp) && (temp != '\n'))
        {
            *errorCode = INPUT_ERROR;
        }
        
        if (!*errorCode && MAX_MANTISA != number->mantisaLen)
        {
            for (int i = 0; i < number->mantisaLen; i++)
            {
                *(number->mantisa + (MAX_MANTISA - 1 - i)) = *(number->mantisa + number->mantisaLen - 1 - i);
                *(number->mantisa + number->mantisaLen - 1 - i) = 0;
            }
        }
    }
}

int countLeadingZero(int* temp, int len)
{
    int leadingZero = 0;
    while (temp[leadingZero] == 0 && leadingZero < len)
    {
        leadingZero++;
    }

    return leadingZero;
}

void normalizeBase10(int* temp, int len)
{
    for (int i = len - 1; i > 0; i--)
    {
        if (temp[i] >= 10)
        {
            temp[i - 1] += temp[i] / 10;
            temp[i] %= 10;
        }
    }
}