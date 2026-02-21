//
// Created by GPT on 2026/2/20.
//

import java.util.*;

class Solution {
    public String makeLargestSpecial(String s) {
        // base: 长度<=2（"10"或空）已经是最大
        if (s.length() <= 2) return s;

        List<String> parts = new ArrayList<>();
        int bal = 0, start = 0;

        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            bal += (c == '1') ? 1 : -1;

            if (bal == 0) {
                // s[start..i] 是一个最外层 special 块：1 + inner + 0
                String inner = s.substring(start + 1, i);
                String bestInner = makeLargestSpecial(inner);
                parts.add("1" + bestInner + "0");
                start = i + 1;
            }
        }

        // 字典序降序：大的块放前面
        parts.sort(Collections.reverseOrder());

        StringBuilder sb = new StringBuilder();
        for (String p : parts) sb.append(p);
        return sb.toString();
    }
}