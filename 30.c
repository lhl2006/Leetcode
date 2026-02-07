//
// Created by lhl on 2026/2/7.
//

#include <string.h>
#include <stdlib.h>

int minimumDeletions(char* s) {
    int length = strlen(s);
    int* num_of_a = malloc(sizeof(int) * length);
    int* num_of_b = malloc(sizeof(int) * length);
    int cnt = 0;
    for (int i = 0; i < length; i++){
        num_of_b[i] = cnt;
        if (s[i] == 'b') cnt++;
    }
    cnt = 0;
    for (int i = length - 1; i >= 0; i--){
        num_of_a[i] = cnt;
        if (s[i] == 'a') cnt++;
    }
    int result = num_of_a[0];
    for (int i = 0; i < length; i++){
        int temp = num_of_a[i] + num_of_b[i];
        if (temp < result){
            result = temp;
        }
    }
    free(num_of_a);
    free(num_of_b);
    return result;
}


// Gemini Version
#include <string.h>

int minimumDeletions_by_Gemini(char* s) {
    int b_count = 0; // 记录遍历过程中遇到的 'b' 的数量
    int deletions = 0; // 记录最小删除次数

    // 只需要一次遍历，利用类似栈/贪心的思想
    for (int i = 0; s[i] != '\0'; i++){
        if (s[i] == 'b'){
            b_count++;
        }
        else{
            // 遇到了 'a'
            // 只有当前面有 'b' 时，这个 'a' 才会造成不平衡
            if (b_count > 0){
                deletions++; // 我们选择删除一次（逻辑上是删除了前面的一个 b 和当前的 a 配对中的某一个）
                b_count--; // 抵消掉一个 b
            }
        }
    }
    return deletions;
}
