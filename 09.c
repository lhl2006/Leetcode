int min(int x,int y){
    return x < y ? x : y;
}

int max(int x,int y){
    return x > y ? x : y;
}

long long calculateSize(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4){
    int x = min(x2,x4) - max(x1,x3);
    int y = min(y2,y4) - max(y1,y3);
    if(x <= 0 || y <= 0){
        return 0;
    }
    long long length = min(x,y);
    return length * length;
}

long long largestSquareArea(int** bottomLeft, int bottomLeftSize, int* bottomLeftColSize, int** topRight, int topRightSize, int* topRightColSize) {
    long long ans = 0;
    for(int i = 0; i < bottomLeftSize;i++){
        for(int j = i + 1;j < bottomLeftSize;j++){
            long long temp = calculateSize(bottomLeft[i][0],bottomLeft[i][1],topRight[i][0],topRight[i][1],
            bottomLeft[j][0],bottomLeft[j][1],topRight[j][0],topRight[j][1]);
            ans = temp > ans ? temp : ans;
        }
    }
    return ans;
}