#include  "sort.h"

void bubble_sort(int *array, int n)
{
    int i, j;
    for( i=0 ; i<n-1 ; i++ )
    {
        for( j=1 ; j<n-i ; j++ )
        {
            if( array[j-1]>array[j] )
            {
                int temp = array[j];
                array[j] = array[j-1];
                array[j-1] = temp;
            }
        }
    }
}

void selection_sort(int *array, int n)
{
    int i, j;
    for( i=0 ; i<n-1 ; i++ )
    {
        int k = 0;
        for( j=1 ; j<n-i ; j++ )
        {
            if( array[k]<array[j] )
            {
                k=j;
            }
        }
        int temp = array[j-1];
        array[j-1] = array[k];
        array[k] = temp;
    }
}

void insertion_sort(int *array, int n)
{
    int i, j;
    for( i=0 ; i<n-1 ; i++ )
    {
        int temp = array[i+1];
        // should compare array[j-1] with temp NOT with array[j],
        // please DO remember.
        for( j=i+1 ; j-1>=0 && array[j-1]>temp ; j-- )
        {
            array[j] = array[j-1];
        }
        array[j] = temp;
    }
}

void shell_sort(int *array, int n)
{
    int i, j, gap;
    for( gap = n/2 ; gap>0 ; gap /= 2 )
    {
        for( i=0 ; i+gap<n ; i++ )
        {
            int temp = array[i+gap];
            // should be j=j-gap NOT j--, please DO remember
            for( j=i+gap ; j-gap>=0 && array[j-gap]>temp; j-=gap )
            {
                array[j] = array[j-gap];
            }
            array[j] = temp;
        }
    }
}

void bin_insertion_sort(int *array, int n)
{
    int i, j;
    for( i=0 ; i<n-1 ; i++ )
    {
        j = i + 1;
        int temp=array[j], low=0, high=i;
        while( low<=high )
        {
            int mid=(low+high)/2;
            if( temp<array[mid] )
            {
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }
        while( low<j )
        {
            array[j] = array[j-1];
            j--;
        }
        array[j] = temp;
    }
}

static void merge(int *array, int low, int mid, int high)
{
    int i=low, j=mid+1, k=0, len=high-low+1;
    int *temp = malloc(sizeof(int) * len);
    while( i<=mid && j<=high )
    {
        temp[k++] = array[i]<=array[j] ? array[i++] : array[j++];
    }
    while( i<=mid )
    {
        temp[k++]=array[i++];
    }
    while( j<=high )
    {
        temp[k++]=array[j++];
    }
    //should be len*sizeof(int) NOT len
    //memcpy(array+low,temp,len*sizeof(int));
    for( k=0 ; k<len ; k++ )
    {
        array[low+k] = temp[k];
    }
    free(temp);
}

void merge_sort(int *array, int low, int high)
{
    if( low<high )
    {
        int mid = (low+high)/2;
        merge_sort(array,low,mid);
        merge_sort(array,mid+1,high);
        merge(array,low,mid,high);
    }
}

static int partition(int *array, int low, int high)
{
    int i = low, j = high-1;
    while( i<=j )
    {
        while( i<=j && array[i]<=array[high] )
        {
            i++;
        }
        while( i<=j && array[j]>=array[high] )
        {
            j--;
        }
        if( i<j )
        {
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i++;
            j--;
        }
    }
    int temp = array[i];
    array[i] = array[high];
    array[high] = temp;
    return i;
}

static int random_partition(int *array, int low, int high)
{
    int pivot = random_int_between(low,high);
    int temp = array[pivot];
    array[pivot] = array[high];
    array[high] = temp;
    return partition(array,low,high);
}

void quick_sort(int *array, int low, int high)
{
    if( low<high )
    {
        int mid = random_partition(array, low, high);
        quick_sort(array,low,mid-1);
        quick_sort(array,mid+1,high);
    }
}

static void max_heapify_recursive(int *array, int n, int index)
{
    int largest = index;
    if( 2*index <=n && array[2*index]>array[largest] )
    {
        largest = 2*index;
    }
    if( 2*index+1 <= n && array[2*index+1]>array[largest] )
    {
        largest = 2*index+1;
    }
    if( largest != index )
    {
        int temp = array[largest];
        array[largest] = array[index];
        array[index] = temp;
        max_heapify_recursive(array,n,largest);
    }
}

static void max_heapify_nonrecursive(int *array, int n, int index)
{
    int flag = 1, largest = index;
    while( flag )
    {
        if( 2*index<=n && array[2*index]>array[largest] )
        {
            largest = 2*index;
        }
        if( 2*index+1<=n && array[2*index+1]>array[largest] )
        {
            largest = 2*index+1;
        }
        if( largest != index )
        {
            int temp = array[index];
            array[index] = array[largest];
            array[largest] = temp;
            index = largest;
        }
        else
        {
            flag = 0;
        }
    }
}

static void build_heap(int  *array, int n)
{
    int i;
    for( i=n/2 ; i>=1 ; i-- )
    {
        //max_heapify_recursive(array,n,i);
        max_heapify_nonrecursive(array,n,i);
    }
}

void heap_sort(int *array, int n)
{
    build_heap(array, n);
    int i;
    for( i=n ; i>1 ; i-- )
    {
        int temp = array[i];
        array[i] = array[1];
        array[1] = temp;
        //max_heapify_recursive(array,i-1,1);
        max_heapify_nonrecursive(array,i-1,1);
    }
}

void counting_sort(int *a, int n, int k)
{
    int i, c[k], b[n];
    memset(c,0,k*sizeof(int));
    for( i=0 ; i<n ; i++ )
    {
        c[a[i]]++;
    }
    for( i=1 ; i<k ; i++ )
    {
        c[i] = c[i] + c[i-1];
    }
    //from high to low to guarantee the stable sort
    for( i=n-1; i>=0 ; i-- )
    {
        b[c[a[i]]-1] = a[i];
        c[a[i]]--;
    }
    //memcpy(a,b,n*sizeof(int));
    for( i=0 ; i<n ; i++ )
    {
        a[i]=b[i];
    }
}
