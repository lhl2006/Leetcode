//
// Created by lhl on 2026/2/10.
//
#include <stdlib.h>
#include <string.h>

#define MAX 100005
#define max(a, b) (((a) > (b)) ? (a) : (b))

int longestBalanced(int* nums, int numsSize) {
    int maxSize = 0;
    for (int i = 0; i < numsSize; i++){
        int oddCnt = 0;
        int evenCnt = 0;
        int visited[MAX] = {0};
        for (int j = i; j < numsSize; j++){
            if (visited[nums[j]] == 0){
                visited[nums[j]] = 1;
                if ((nums[j] & 1) == 1){
                    oddCnt++;
                }
                else{
                    evenCnt++;
                }
            }

            if (oddCnt == evenCnt){
                maxSize = max(maxSize, j - i + 1);
            }
        }
    }
    return maxSize;
}
