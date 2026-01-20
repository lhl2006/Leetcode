/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdlib.h>

int* minBitwiseArray(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;
    int *ans = malloc(sizeof(int) * numsSize);
    for(int i = 0;i < numsSize;i++){
        ans[i] = -1;
    }
    for(int i = 0;i < numsSize;i++){
        int temp = 1;
        if((nums[i] & temp) == 0) continue;
        while((nums[i] & temp) != 0){
            temp <<= 1;
        }
        ans[i] = nums[i] - (temp >> 1);
    }
    return ans;
}

// for(int i = 0;i < numsSize;i++){
//         for(int j = 1;j < nums[i];j++){
//             if((j | (j + 1)) == nums[i]){
//                 ans[i] = j;
//                 break;
//             }
//         }
//     }