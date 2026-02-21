int count_bit(int num){
    int cnt = 0;
    while(num != 0){
        if((num & 1) == 1) cnt++;
        num >>= 1;
    }
    int tar[8] = {2, 3, 5, 7 ,11, 13, 17, 19};
    for(int i = 0;i < 8;i++){
        if(cnt == tar[i]) return 1;
    }
    return 0;
}

int countPrimeSetBits(int left, int right) {
    int result = 0;
    for(int i = left;i <= right;i++){
        if(count_bit(i)){
            result++;
        }
    }
    return result;
}


// GPT
/*
int countPrimeSetBits(int left, int right) {
    const int prime_mask = 665772; // bits: 2,3,5,7,11,13,17,19
    int ans = 0;
    for (int x = left; x <= right; ++x) {
        ans += (prime_mask >> __builtin_popcount((unsigned)x)) & 1;
    }
    return ans;
}
*/