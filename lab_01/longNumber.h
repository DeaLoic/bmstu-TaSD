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

void setZero(longNumber* number);
void setEmpty(longNumber* number);
void inputNumber(longNumber* number, int* errorCode);
void inputNumberInt(longNumber* number, int* errorCode);
void printNumber(longNumber* number, int* errorCode);
void normalizeNumber(longNumber* number);
void countMantisLen(longNumber* number);
void deleteLeadingSymb(int* temp, int len, int cntSymb);
void zeroMantis(longNumber* number);
void delRightZero(longNumber* number);
void normalizeBase10(int* temp, int len);
int countLeadingZero(int* temp, int len);

#endif