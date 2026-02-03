#include<stdbool.h>
#define UP 1
#define DOWN -1

bool isTrionic(int* nums, int numsSize) {
    if(nums[0] >= nums[1]) return false;
    int change_cnt = 0;
    int cur_state = UP;
    for(int i = 1;i < numsSize;i++){
        if(nums[i - 1] == nums[i]) return false;
        if(nums[i - 1] < nums[i] && cur_state == DOWN){
            cur_state = UP;
            change_cnt++;
        }
        else if(nums[i - 1] > nums[i] && cur_state == UP){
            cur_state = DOWN;
            change_cnt++;
        }
    }
    if(change_cnt == 2) return true;
    return false;
}