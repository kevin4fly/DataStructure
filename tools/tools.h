#ifndef  TOOLS_H
#define  TOOLS_H

#include  <stdio.h>

#define   MAX(a,b) ((a)>(b)?(a):(b))
int random_int_between(const int m, const int n);

int abs_int(int a, int b);

void print_array(int *array, int array_size);

#endif  /*TOOLS_H*/
