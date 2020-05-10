/*
 *
 */
#include "sort.h"
#include <stdio.h>
#include <time.h>
#include <memory.h>
#include <malloc.h>

extern int* randomPermutationBySwap(int n);
void sort_algo_perf_analysis() 
{
    int nums = 12800000;
    clock_t begin, end;
    int* pNumArra = NULL;
	int value = 0;

    pNumArra = randomPermutationBySwap(nums);

    begin = clock();
    quickSort(pNumArra, nums);
    end = clock();
    free(pNumArra);
    printf("quickSort:%.4f s\n", (double)(end - begin) / CLOCKS_PER_SEC);


    pNumArra = randomPermutationBySwap(nums);
	begin = clock();
	shellsort(pNumArra, nums, INC_BEST);
	end = clock();
	free(pNumArra);
    printf("shellsort:%.4f s\n", (double)(end - begin) / CLOCKS_PER_SEC);

	pNumArra = randomPermutationBySwap(nums);
	begin = clock();
    value = quickSelectKth(pNumArra, nums, nums >> 1);
	end = clock();
	free(pNumArra);
	printf("quickSelectKth:%.4f s\n", (double)(end - begin) / CLOCKS_PER_SEC);

	pNumArra = randomPermutationBySwap(nums);
	begin = clock();
	value = selectionKthR(pNumArra, nums, nums >> 1);
	end = clock();
	free(pNumArra);
	printf("selectionKthR:%.4f s\n", (double)(end - begin) / CLOCKS_PER_SEC);

}