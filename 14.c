int check(int *nums,int numsSize){
    for(int i = 1;i < numsSize;i++){
        if(nums[i] < nums[i - 1]) return 1;
    }
    return 0;
}

int minimumPairRemoval(int* nums, int numsSize) {
    int result = 0;
    while(check(nums,numsSize)){
        int index = 0;
        int min = nums[0] + nums[1];
        for(int i = 1;i < numsSize;i++){
            if(nums[i] + nums[i-1] < min){
                index = i - 1;
                min = nums[i] + nums[i-1];
            }
        }
        nums[index] = nums[index] + nums[index + 1];
        for(int i = index + 2;i < numsSize;i++){
            nums[i - 1] = nums[i];
        }
        result++;
        numsSize--;
    }
    return result;
}