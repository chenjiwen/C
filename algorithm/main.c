#include <stdio.h>
#include "sort.h"

extern void dsa_chap2_test();
extern void math_test();
extern void sort_algo_perf_analysis();

int main()
{
	int array[] = {1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15, 8, 16};
	int countarray[] = { 2, 5, 3, 0, 2, 3, 0, 3 };
	int dstarray[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	//bubbleSort(array, sizeof(array) / sizeof(array[0]));
	//selectionSort(array, sizeof(array) / sizeof(array[0]));
	//mergeSort(array, sizeof(array) / sizeof(array[0]));
	int val = 0;
	//val = selectionKthR(array, sizeof(array) / sizeof(array[0]), 12);
	val = quickSelectKth(array, sizeof(array) / sizeof(array[0]), 10);
	quickSort(array, sizeof(array) / sizeof(array[0]));
	insertionSort(array, sizeof(array) / sizeof(array[0]));
	shellsort(array, sizeof(array)/sizeof(array[0]), INC_SHELL);
	countingSort(countarray, dstarray, 8, 5);
	dsa_chap2_test();
	math_test();
	sort_algo_perf_analysis();
	return 0;
}