int check(int x,int y,int size,int threshold,int** mat,int **P){
    int sum = P[x + size][y + size] - P[x][y + size] - P[x + size][y] + P[x][y];
    if(sum <= threshold) return 1;
    return 0;
}

int maxSideLength(int** mat, int matSize, int* matColSize, int threshold) {
    // 二维前缀和
    int** P = (int**)malloc(sizeof(int*) * (matSize + 1));
    for(int i = 0; i <= matSize; i++) {
    // 使用 calloc 可以直接初始化为 0，省去手动赋 0 的步骤
        P[i] = (int*)calloc(matColSize[0] + 1, sizeof(int));
    }

    for(int i = 1;i < matSize + 1;i++){
        for(int j = 1;j < matColSize[0] + 1;j++){
            P[i][j] = P[i][j - 1] + P[i - 1][j] - P[i - 1][j - 1] + mat[i - 1][j - 1];
        }
    }
    
    int maxSize = matSize < matColSize[0] ? matSize : matColSize[0];
    for(int size = maxSize;size > 0;size--){
        for(int i = 0;i <= matSize - size;i++){
            for(int j = 0;j <= matColSize[0] - size;j++){
                if(check(i,j,size,threshold,mat,P)){
                    return size;
                }
            }
        }
    }
    return 0;
}