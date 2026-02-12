//
// Created by lhl on 2026/2/12.
//
#include <string.h>
#include <stdbool.h>
#define MAX 1001

int longestBalanced(char* s) {
    int result = 1;
    int length = strlen(s);
    for (int i = 0; i < length; i++){
        int box[26] = {0};
        box[s[i] - 'a']++;
        int distinct = 1;
        for (int j = i + 1; j < length; j++){
            bool flag = true;
            if (box[s[j] - 'a'] == 0){
                distinct++;
            }
            box[s[j] - 'a']++;
            int base = box[s[i] - 'a'];
            if ((j - i + 1) % distinct != 0) continue;
            for (int k = 0; k < 26; k++){
                if (box[k] != base && box[k] != 0){
                    flag = false;
                    break;
                }
            }
            if (flag){
                result = result > j - i + 1 ? result : j - i + 1;
            }
        }
    }
    return result;
}
