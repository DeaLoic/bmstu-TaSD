#ifndef __LONG_ARIFH_H__
#define __LONG_ARIFH_H__

#include "longNumber.h"

// Multiply numberFirst and numberSecond. Write result of multiply to result and normalize by math rule (0.(digit) e EXP)
void longMultiply(longNumber* numberFirst, longNumber* numberSecond, longNumber* result, int* errorCode);

// If digit >= 10, then leftDigit = digit div 10, digit = digit mod 10
void rounding(int* temp, int oldLen);

#endif