#ifndef  TOOLS_H
#define  TOOLS_H

#include  <stdio.h>
#include  <time.h>
#include  <stdlib.h>

#define   MAX(a,b) ((a)>(b)?(a):(b))

// single line style
#define   SWAP_INT(a,b) int t=(a); (a)=(b); (b)=t

// advantage: no overflow
// shortage: only for integer
#define   SWAP1(a,b) \
          do{ \
              (a) = (a)^(b); \
              (b) = (a)^(b); \
              (a) = (b)^(a); \
          }while(0)

// advantage: no overflow and for all kinds of types
// shortage: need support typeof operator
#define   SWAP2(a,b) \
          do{ \
              typeof(a) tmp = (a); \
              (a) = (b); \
              (b) = tmp; \
          }while(0)

// advantage: all kinds of types
// shortage: overflow risk since a+b
#define   SWAP3(a,b) \
          do{ \
              (a) = (a)+(b); \
              (b) = (a)-(b); \
              (a) = (a)-(b); \
          }while(0)


// add this function srandom((unsigned int)time(NULL)) so that the random
// numbers all not the same when running the code each time
int random_int_between(const int m, const int n);

int abs_int(const int a, const int b);

int average_int(const int x, const int y);

void print_array(const int *array, int array_size);

#endif  /*TOOLS_H*/
