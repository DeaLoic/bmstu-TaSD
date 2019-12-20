#include "test.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

unsigned long int tick(void)
{
    unsigned long int d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d) );
    return d;
}

void efficiency(char data_file[], int len_table)
{
    for int i
}