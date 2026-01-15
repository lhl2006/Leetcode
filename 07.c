#include <stdlib.h>

int compare(const void *a, const void *b) {
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;

    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int maximizeSquareHoleArea(int n, int m, int* hBars, int hBarsSize, int* vBars, int vBarsSize) {
    qsort(hBars , hBarsSize, sizeof(int), compare);
    qsort(vBars , vBarsSize, sizeof(int), compare);
    int h_max_link = 1;
    for(int i = 0;i < hBarsSize;i++){
        int link = 1;
        for(int j = i + 1;j < hBarsSize;j++){
            if(hBars[j] == hBars[j - 1] + 1){
                link++;
                if(j != hBarsSize - 1){
                    continue;
                }
            }
            if(link > h_max_link) h_max_link = link;
            i = j - 1;
            break;
        }
    }
    int v_max_link = 1;
    for(int i = 0;i < vBarsSize;i++){
        int link = 1;
        for(int j = i + 1;j < vBarsSize;j++){
            if(vBars[j] == vBars[j - 1] + 1){
                link++;
                if(j != vBarsSize - 1){
                    continue;
                }
            }
            if(link > v_max_link) v_max_link = link;
            i = j - 1;
            break;
        }
    }
    int link = h_max_link > v_max_link ? v_max_link : h_max_link;
    return (link + 1) * (link + 1);
}