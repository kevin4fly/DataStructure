#ifndef  SORT_H
#define  SORT_H

#include  "../tools/tools.h"
#include  <stdlib.h>
#include  <assert.h>
#include  <string.h>

/**< the sort algorithms
 *
 * */

void bubble_sort(int *array, int n);
void selection_sort(int *array, int n);
void insertion_sort(int *array, int n);
void shell_sort(int *array, int n);
void bin_insertion_sort(int *array, int n);

void merge_sort(int *array, int low, int high);
void quick_sort(int *array, int low, int high);
void heap_sort(int *array, int n);
void counting_sort(int *a, int n, int k);

#endif  /*SORT_H*/
