/*
14. Longest Common Prefix
https://leetcode.com/problems/longest-common-prefix/

Write a function to find the longest common prefix string amongst an array of strings.

If there is no common prefix, return an empty string "".

Example 1:

Input: ["flower","flow","flight"]
Output: "fl"
Example 2:

Input: ["dog","racecar","car"]
Output: ""
Explanation: There is no common prefix among the input strings.
Note:

All given inputs are in lowercase letters a-z.
*/
/*
This solution runtime complexity: O(m*n) (m is average lenght of all strings, and n is number of all strings)
no extra space used.
While this problem could be solved by Trie structure.
after build the trie, find the first node which has >=2 children.
*/
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.empty()) return "";
        int j = 0;
        while (j < (int)strs[0].size()) {
            char c = strs[0][j];
            for (int i = 1; i < (int)strs.size(); i++) {
                if ((j >= strs[i].size()) or (c != strs[i][j])) {
                    return strs[0].substr(0, j);
                }
            }
            j++;
        }
        return strs[0].substr(0, j);
    }
};
