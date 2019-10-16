/*
434. Number of Segments in a String
Easy
https://leetcode.com/problems/number-of-segments-in-a-string/

Count the number of segments in a string, where a segment is defined to be a contiguous sequence of non-space characters.

Please note that the string does not contain any non-printable characters.

Example:

Input: "Hello, my name is John"
Output: 5
*/
class Solution {
public:
    int countSegments(string s) {
        int cnt = 0;
        int sz = (int)s.size();
        for (int i = 0; i < sz; i++) {
            if ((i == 0 or s[i-1] == ' ') and s[i] != ' ')
                cnt++;
        }
        return cnt;
    }
    int countSegments1(string s) {
        int cnt = 0;
        int sz = (int)s.size();
        for (int i = 0; i < sz; i++) {
            while (i < sz and s[i] == ' ') {
                i++;
            }
            if (i == sz) break;
            while (i < sz and s[i] != ' ') {
                i++;
            }
            cnt++;
        }
        return cnt;
    }
};
