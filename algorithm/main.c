#ifdef __cplusplus
extern "C" {
	int main();
	int farh2ceils(int);
	void char_input_out();
	int word_count();
	void ctest();
}
#endif

#include <stdio.h>
#include "sort.h"

//符号常量
//字符串常量
double farh2ceils(int fahr)
{
	return 5.0 * (fahr - 32.0) / 9.0;
}

char p[10] = "abcdefgh";

void my_test_ptr(char *s)
{
	printf("val of s:0x%x\n", (unsigned)s);
	printf("address of s:0x%x\n", (unsigned)&s);
	printf("sizeof(s):%d\n", sizeof(s));
}

void my_test_arr(char s[10]) {
	printf("val of s:0x%x\n", (unsigned)s);
	printf("address of s:0x%x\n", (unsigned)&s);
	printf("sizeof(s):%d\n", sizeof(s));
}

void my_test(char* p)
{
	printf("val of s:0x%x\n", (unsigned)p);
	printf("address of s:0x%x\n", (unsigned)&p);
	printf("sizeof(s):%d\n", sizeof(p));
}
//extern char* p;

int apricot[2][3][5];
int carrot[10][20];
int(*papr)[3][5];

void ctest()
{
	int low = 0, high = 300;
	int i = 0;
	int step = 20;
	int eof = EOF;
	char* pc;
	char(*ppc)[10] = NULL;

	int(*r)[5] = apricot[0];
	int* t = apricot[0][0];

	//papr = apricot[0];
	papr = apricot;

	printf("r = 0x%x, t = 0x%x\n", (unsigned)r, (unsigned)t);
	r++;
	t++;
	printf("r = 0x%x, t = 0x%x\n", (unsigned)r, (unsigned)t);

	printf("val of p, address of p: 0x%x, 0x%x\n", (unsigned)p, (unsigned)&p);
	pc = p;

	my_test_arr(p);
	my_test_ptr(p);
	my_test(p);

	printf_s("please enter two integer nums:\n");
	//scanf_s("%d %d", &low, &high);
	//char_input_out();

	printf_s("table of fahr to celsius: \n");
	for (i = low; i <= high; i += step)
	{
		printf("%3.0f:\t%6.1f\n", (double)i, farh2ceils(i));
	}

	for (i = low; i <= high; i += step)
	{
		printf_s("%3d: \t0x%08x\n", i, i);
	}

	//printf("word count:%d\n", word_count());
}

int main()
{
	int array[] = {1, 9, 2, 10, 3, 11, 4, 12, 5, 13, 6, 14, 7, 15, 8, 16};
	int countarray[] = { 2, 5, 3, 0, 2, 3, 0, 3 };
	int dstarray[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	//bubbleSort(array, sizeof(array) / sizeof(array[0]));
	//selectionSort(array, sizeof(array) / sizeof(array[0]));
	mergeSort(array, sizeof(array) / sizeof(array[0]));
	quickSort(array, sizeof(array) / sizeof(array[0]));
	insertionSort(array, sizeof(array) / sizeof(array[0]));
	shellsort(array, sizeof(array)/sizeof(array[0]), INC_SHELL);
	countingSort(countarray, dstarray, 8, 5);
	return 0;
}