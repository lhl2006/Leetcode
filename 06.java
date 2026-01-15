class Solution {
    public String convert(String s, int numRows) {
        if(numRows == 1) return s;
        int length = s.length();
        StringBuilder sb = new StringBuilder();
        for(int i = 1;i <= numRows;i++){
            int index = i - 1;
            boolean is_up = true;
            while(index < length){
                sb.append(s.charAt(index));
                int add = 0;
                if(is_up){
                    add = 2 * (numRows - i);
                    if(add == 0){
                        add = 2 * (i - 1);
                    }
                }else{
                    add = 2 * (i - 1);
                    if(add == 0){
                        add = 2 * (numRows - i);
                    }
                }
                index += add;
                if(is_up){
                    is_up = false;
                }else{
                    is_up = true;
                }
            }
        }
        return sb.toString();
    }
}