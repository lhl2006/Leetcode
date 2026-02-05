/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

#include<stdlib.h>
int* constructTransformedArray(int* nums, int numsSize, int* returnSize) {
    int *result = malloc(sizeof(int) * numsSize);
    for(int i = 0;i < numsSize;i++){
        result[i] = nums[((i + nums[i]) % numsSize + numsSize) % numsSize];
    }
    *returnSize = numsSize;
    return result;
}