//
// Created by GPT on 2026/2/17.
//
/*#include <stdio.h>
#include <stdlib.h>

char** readBinaryWatch(int turnedOn, int* returnSize) {
    char** res = (char**)malloc(sizeof(char*) * 720);
    int cnt = 0;

    for (int h = 0; h < 12; h++) {
        for (int m = 0; m < 60; m++) {
            if (__builtin_popcount((unsigned)h) + __builtin_popcount((unsigned)m) == turnedOn) {
                res[cnt] = (char*)malloc(6);              // "11:59" + '\0'
                snprintf(res[cnt], 6, "%d:%02d", h, m);   // 分钟补 0
                cnt++;
            }
        }
    }

    *returnSize = cnt;
    return res;
}*/

//
// Created by lhl on 2026/2/17.
//
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

#include <stdlib.h>
#define MAX_H 3
#define MAX_M 5
#define Hour 12
#define Min 60

void gen(int* H, int* M, char** res, int* cnt);
void possible_result(int** H, int** M);

char** readBinaryWatch(int turnedOn, int* returnSize) {
    char** res = (char**)malloc(sizeof(char*) * Hour * Min);
    int** H = (int**)malloc(sizeof(int*) * (MAX_H + 1));
    int** M = (int**)malloc(sizeof(int*) * (MAX_M + 1));
    possible_result(H, M);
    if (turnedOn > MAX_H + MAX_M){
        *returnSize = 0;
        return res;
    }
    int cnt = 0;
    for (int i = 0; i <= MAX_H; i++){
        if (turnedOn - i > MAX_M) continue;
        if (turnedOn < i) break;
        gen(H[i], M[turnedOn - i], res, &cnt);
    }
    *returnSize = cnt;
    return res;
}

int cnt_bin_1(int num) {
    if (num == 0) return 0;
    int cnt = 0;
    while (num > 0){
        if ((num & 1) == 1) cnt++;
        num >>= 1;
    }
    return cnt;
}

void possible_result(int** H, int** M) {
    for (int i = 0; i <= MAX_H; i++){
        int* temp = (int*)malloc(sizeof(int) * (Hour + 1));
        *temp = 0; //用于可能性计数
        H[i] = temp;
    }
    for (int i = 0; i < Hour; i++){
        H[cnt_bin_1(i)][++H[cnt_bin_1(i)][0]] = i;
    }
    for (int i = 0; i <= MAX_M; i++){
        int* temp = (int*)malloc(sizeof(int) * (Min + 1));
        *temp = 0; //用于可能性计数
        M[i] = temp;
    }
    for (int i = 0; i < Min; i++){
        M[cnt_bin_1(i)][++M[cnt_bin_1(i)][0]] = i;
    }
}

void generate_time(char* res, int H, int M) {
    int index = 0;
    if (H >= 10) res[index++] = '1';
    res[index++] = H % 10 + '0';
    res[index++] = ':';
    if (M >= 10){
        res[index++] = M / 10 + '0';
    }
    else{
        res[index++] = '0';
    }
    res[index++] = M % 10 + '0';
    res[index] = '\0';
}

void gen(int* H, int* M, char** res, int* cnt) {
    int H_size = H[0];
    int M_size = M[0];
    for (int i = 1; i <= H_size; i++){
        for (int j = 1; j <= M_size; j++){
            res[*cnt] = malloc(sizeof(char) * 6);
            generate_time(res[*cnt], H[i], M[j]);
            (*cnt)++;
        }
    }
}

#include<stdio.h>

int main(void) {
    int tests[] = {1, 2, 3, 5, 8};
    int ntests = (int)(sizeof(tests) / sizeof(tests[0]));

    for (int t = 0; t < ntests; t++){
        int turnedOn = tests[t];
        int returnSize = 0;

        char** ans = readBinaryWatch(turnedOn, &returnSize);

        printf("turnedOn = %d, returnSize = %d\n", turnedOn, returnSize);
        for (int i = 0; i < returnSize; i++){
            printf("%s\n", ans[i]);
        }
        printf("----\n");
    }
    return 0;
}
