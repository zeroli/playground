/*
387. First Unique Character in a String
Easy
https://leetcode.com/problems/first-unique-character-in-a-string/

Given a string, find the first non-repeating character in it and return it's index. If it doesn't exist, return -1.

Examples:

s = "leetcode"
return 0.

s = "loveleetcode",
return 2.
Note: You may assume the string contain only lowercase letters.
*/
class Solution {
public:
    int firstUniqChar(string s) {
        int h[26];
        memset(h, 0, 26 * sizeof(int));
        for (int i = 0; i < (int)s.size(); i++) {
            h[s[i]-'a']++;
        }

        for (int i = 0; i < (int)s.size(); i++) {
            if (h[s[i]-'a'] == 1) {
                return i;
            }
        }
        return -1;
    }
};
