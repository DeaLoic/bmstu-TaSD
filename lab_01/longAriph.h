#ifndef __LONG_ARIFH_H__
#define __LONG_ARIFH_H__

#include "longNumber.h"

void sumNumber(longNumber* numberFirst, longNumber* numberSecond, longNumber* result, int* errorCode);
void longMultiply(longNumber* numberFirst, longNumber* numberSecond, longNumber* result, int* errorCode);
void rounding(int* temp, int oldLen);

#endif