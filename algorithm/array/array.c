#include <stdio.h>
#include <stdlib.h>

int removeDuplicates(int* nums, int numsSize) {
    int i = 0, j = 0, count = 0;

    count = 1;
    for (j = 1; j < numsSize; j++)
    {
        if (nums[i] == nums[j])
        {
            count++;
            if (count <= 2)
            {
                nums[++i] = nums[j];
            }
        }
        else
        {
            nums[++i] = nums[j];
            count = 1;
        }
    }

    return numsSize ? i + 1 : 0;
}

int removeDupGivenVal(int* nums, int numsSize, int val) {
    int i = 0, j = 0;
    for (j = 1; j < numsSize; j++)
    {
        if (nums[j] != val)
            nums[++i] = nums[j];
    }

    return numsSize ? i + 1 : 0;
}

int thirdMax(int* nums, int numsSize) {
    int max = LONG_MIN, second = LONG_MIN, third = LONG_MIN;
    int i = 0;

    for (i = 0; i < numsSize; i++)
    {
        if (nums[i] > max)
        {
            second = max;
            max = nums[i];
        }
        else if (nums[i] > second && nums[i] < max)
        {
            third = second;
            second = nums[i];
        }
        else if (nums[i] < second && nums[i] > third)
            third = nums[i];
    }

    return (third == LONG_MIN) ? max : third;
}



void arrayTest()
{
    int nums[] = { 0,0,1,1,1,1,2,3,3 };

    int len = sizeof(nums)/sizeof(nums[0]);

    len = removeDuplicates(nums, len);

    int nums1[] = { 1,2 };

    thirdMax(nums1, 2);
}