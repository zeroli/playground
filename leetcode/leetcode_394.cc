/*
394. Decode String
Medium
https://leetcode.com/problems/decode-string/

Given an encoded string, return its decoded string.

The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times. Note that k is guaranteed to be a positive integer.

You may assume that the input string is always valid; No extra white spaces, square brackets are well-formed, etc.

Furthermore, you may assume that the original data does not contain any digits and that digits are only for those repeat numbers, k. For example, there won't be input like 3a or 2[4].

Examples:

s = "3[a]2[bc]", return "aaabcbc".
s = "3[a2[c]]", return "accaccacc".
s = "2[abc]3[cd]ef", return "abcabccdcdcdef".
*/
class Solution {
public:
    string decodeString(string s) {
        int p = 0;
        return decodeString(s, p);
    }
    string decodeString(string& s, int& p) {
        string res;
        int sz = (int)s.size();
        while (p < sz) {
            if (isdigit(s[p])) {
                int k = 0;
                int n = atoi(&s[p]);
                while (s[p] != '[') p++;
                p++;
                string str = decodeString(s, p);
                while (k++ < n) {
                    res += str;
                }
            } else if (s[p] == ']') {
                p++;
                break;
            } else {
                res += s[p++];
            }
        }
        return res;
    }
};
