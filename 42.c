//
// Created by GPT on 2026/2/19.
//
/*#include <string.h>

static inline int min_int(int a, int b) { return a < b ? a : b; }

int countBinarySubstrings(char* s) {
    if (s == NULL) return 0;
    int n = (int)strlen(s);
    if (n <= 1) return 0;

    int prev = 0;   // 上一段连续字符长度
    int cur = 1;    // 当前段连续字符长度（至少包含 s[0]）
    int ans = 0;

    for (int i = 1; i < n; ++i) {
        if (s[i] == s[i - 1]) {
            cur++;
        } else {
            ans += min_int(prev, cur);
            prev = cur;
            cur = 1;
        }
    }
    ans += min_int(prev, cur); // 处理最后一段与上一段的贡献

    return ans;
}*/


//
// Created by lhl on 2026/2/19.
//
#include <stdlib.h>
#include <string.h>
#define MAX 100005

int countBinarySubstrings(char* s) {
    int length = strlen(s);
    int result = 0;
    int cur_status = s[0] == '0' ? 0 : 1;
    for (int i = 1; i < length; i++){
        int status = s[i] == '0' ? 0 : 1;
        if (status != cur_status){
            int l = i - 1, r = i;
            while (l >= 0 && r < length){
                int l_status = s[l] == '0' ? 0 : 1;
                int r_status = s[r] == '0' ? 0 : 1;
                if (l_status == cur_status && r_status == status){
                    result++;
                    l--;
                    r++;
                    continue;
                }
                break;
            }
        }
        cur_status = status;
    }
    return result;
}
