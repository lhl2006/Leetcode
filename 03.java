class Solution {
    public int lengthOfLongestSubstring(String s) {
        int length = s.length();
        if(length == 0) return 0;
        if(length == 1) return 1;
        int result = 0;
        int begin = 0,end = 0;
        for(int i = 1;i < length;i++){
            end = i;
            char c = s.charAt(i);
            int index = check(s,begin,end - 1,c);
            if(index != -1){
                result = result > end - begin ? result : end - begin;
                begin = index + 1;
            }
        }
        end++;
        result = result > end - begin ? result : end - begin;
        return result;
    }
    public int check(String s,int begin,int end,char c){
        for(int i = begin;i <= end;i++){
            if(s.charAt(i) == c){
                return i;
            }
        }
        return -1;
    }
    public void main(String[] args) {
        String s = "bbbbb";
        System.out.print(lengthOfLongestSubstring(s));
    }
}