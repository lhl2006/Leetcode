class Solution {
    public long minimumCost(String source, String target, char[] original, char[] changed, int[] cost) {
        int [][]box = new int[26][26];
        for(int i = 0;i < 26;i++){
            for(int j = 0;j < 26;j++){
                box[i][j] = 10000000;
            }
        }
        for(int i = 0;i < original.length;i++){
            char ori = original[i];
            char cha = changed[i];
            if(box[ori - 'a'][cha - 'a'] > cost[i]){
                box[ori - 'a'][cha - 'a'] = cost[i];
            }
        }
        for(int k = 0;k < 26;k++){
            for(int i = 0;i < 26;i++){
                for(int j = 0;j < 26;j++){
                    int cost1 = box[i][k],cost2 = box[k][j];
                    if(cost1 == 10000000 || cost2 == 10000000) continue;
                    if(cost1 + cost2 < box[i][j]) box[i][j] = cost1 + cost2;
                }
            }
        }
        long result = 0;
        for(int i = 0;i < source.length();i++){
            char a = source.charAt(i);
            char b = target.charAt(i);
            if(a == b) continue;
            int cos = box[a - 'a'][b - 'a'];
            if(cos == 10000000) return -1;
            else result += cos;
        }
        return result;
    }
}