#ifndef __AL_COMMON_H__
#define __AL_COMMON_H__

#pragma once

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

typedef int bool;
#define true 1
#define false 0

#define PIVOT_FLAG 0xdeadbeef

#ifdef __cplusplus
extern "C"
{
#endif

	void swap(int *x, int *y);
	void printNums(int* pNumArray, int len);

#ifdef __cplusplus
}
#endif

#endif

