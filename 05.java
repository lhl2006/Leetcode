class Solution {
    int maxlen = 1;
    int start = 0;
    public String longestPalindrome(String s) {
        int maxlen = 1;
        int start = 0;
        int length = s.length();
        int[][] dp = new int [length][length];
        for(int i = 0;i < length;i++){
            dp[i][i] = 1;
        }
        for(int i = 2;i <= length;i++){
            for(int left = 0;left < length;left++){
                int right = left + i - 1;
                if(right >= length) break;
                if(s.charAt(left) == s.charAt(right)){
                    if(i <= 3){
                        dp[left][right] = 1;
                    }else{
                        dp[left][right] = dp[left + 1][right - 1];
                    }
                }
                if(dp[left][right] == 1 && i > maxlen){
                    maxlen = right - left + 1;
                    start = left;
                }
            }
        }
        
        return s.substring(start,start + maxlen);
    }
}