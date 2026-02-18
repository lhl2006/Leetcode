//
// Created by lhl on 2026/2/18.
//
#include <stdbool.h>

bool hasAlternatingBits(int n) {
    int status = (n & 1);
    while (n > 0){
        n >>= 1;
        if (status == (n & 1)) return false;
        status = (n & 1);
    }
    return true;
}
