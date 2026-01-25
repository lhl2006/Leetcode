#include<stdlib.h>

int comp(const void* a,const void* b){
    return *(int *)a - *(int *)b;
}

int minimumDifference(int* nums, int numsSize, int k) {
    qsort(nums, numsSize, sizeof(int), comp);
    int min = nums[k - 1] - nums[0];
    for(int i = 0;i + k - 1 < numsSize;i++){
        int diff = nums[i + k - 1] - nums[i];
        if(diff < min){
            min = diff;
        }
    }
    return min;
}