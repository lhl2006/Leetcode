int check(int** grid,int x,int y,int size){
    int sum = 0;
    for(int i = y;i < y + size;i++){
        sum += grid[x][i];
    }
    for(int i = x + 1;i < x + size;i++){
        int temp = 0;
        for(int j = y;j < y + size;j++){
            temp += grid[i][j];
        }
        if(temp != sum) return 0;
    }
    for(int j = y;j < y + size;j++){
        int temp = 0;
        for(int i = x;i < x + size;i++){
            temp += grid[i][j];
        }
        if(temp != sum) return 0;
    }
    int temp = 0;
    for(int i = 0;i < size;i++){
        temp += grid[x + i][y + i];
    }
    if(temp != sum) return 0;
    temp = 0;
    for(int i = 0;i < size;i++){
        temp += grid[x + i][y + size - 1 - i];
    }
    if(temp != sum) return 0;
    return 1;
}

int largestMagicSquare(int** grid, int gridSize, int* gridColSize) {
    int maxSize = gridSize < gridColSize[0] ? gridSize : gridColSize[0];
    for(int i = maxSize; i > 1; i--){
        for(int x = 0;x + i <= gridSize;x++){
            for(int y = 0;y + i <= gridColSize[0];y++){
                if(check(grid,x,y,i)){
                    return i;
                }
            }
        }
    }
    return 1;
}