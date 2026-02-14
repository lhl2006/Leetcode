#define MAX 105
#include <stdbool.h>

double dp[MAX][MAX] = {0};

double champagneTower(int poured, int query_row, int query_glass) {
    memset(dp, 0, sizeof(dp));
    dp[0][0] = poured;
    for(int i = 0;i <= query_row;i++){
        bool overflow = false;
        for(int j = 0;j < i + 1;j++){
            if(dp[i][j] > 1){
                overflow = true;
                dp[i + 1][j] += (double)(dp[i][j] - 1) / 2;
                dp[i + 1][j + 1] += (double)(dp[i][j] - 1) / 2;
                dp[i][j] = 1.0;
            }
        }
        if(!overflow) break;
    }
    return dp[query_row][query_glass];
}