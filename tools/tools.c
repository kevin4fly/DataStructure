#include  "tools.h"

#include  <stdlib.h> // for random();


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
