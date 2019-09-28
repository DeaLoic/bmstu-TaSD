#ifndef __LONG_NUMBER_H__
#define __LONG_NUMBER_H__

#define MAX_MANTISA 30
#define MAX_EXP 99999

typedef struct
{
    int mantisaSign;
    int dotPos;
    int mantisaLen;
    int mantisa[MAX_MANTISA];
    int exp;

} longNumber;

// Set value to longNumber
void setZero(longNumber* number);
void setEmpty(longNumber* number);

// I/O
void inputNumberDbl(longNumber* number, int* errorCode);
void inputNumberInt(longNumber* number, int* errorCode);
void printNumber(longNumber* number, int* errorCode);

// Handlers

// Set number->mantisaLen by calculated mantisa lenght
// Mantisa calculate as MAX_MANTISA - leading zeros
void countMantisLen(longNumber* number);

// Normalize like integer mantisa without dat and right zeros with de/increment number->exp
void normalizeNumber(longNumber* number);

// Shift to left at cntSymbToDelete. Frees fill by zero
void deleteLeadingSymb(int* sourceArray, int len, int cntSymbToDelete);

// Set mantissa to zeros
void zeroMantis(longNumber* number);

// Delete right zeros and increese number->exp
void delRightZero(longNumber* number);

// Shift mantissa to right by first non-zero right digit
void shiftMantisToRight(longNumber* number);

// Support
// Max digit = 9, else increese ledt digit and set cur digit ti curDigit mod 10
void normalizeBase10(int* sourceArray, int len);

// Return number of left zeros
int countLeadingZero(int* sourceArray, int len);

#endif