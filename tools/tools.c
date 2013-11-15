#include  "tools.h"

/* random_int_between: return the random integer between @m and @n
 *
 * description:
 * random() -> 0-huge
 * random()%(n-m+1) -> [0,n-m+1)
 * random()%(n-m+1)+n -> [m,n+1) -> [m,n]
 *
 * */
int random_int_between(const int m, const int n)
{
    return random()%(n-m+1)+m;
}

int abs_int(const int a, const int b)
{
    return a>b?a-b:b-a;
}

// average = (x + y)/2 may cause overflow
// x&y: 1/1 equals to 1, which means divide 2 already.
// (x^y)>>1: 1/0 or 0/1 equals to 1, which should divide 2.
// 0/0 equals 0, divide 2 or not is the same..
int average_int(const int x, const int y)
{
    return (x&y)+((x|y)>>1);
}

void print_array(int *array, int array_size)
{
    int i;
    for( i=0 ; i<array_size ; i++ )
    {
        printf("%-3d",array[i]);
        if( i%10==9 )
        {
            printf("\n");
        }
    }
}
