/*
1209. Remove All Adjacent Duplicates in String II
Medium
https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string-ii/

Given a string s, a k duplicate removal consists of choosing k adjacent and equal letters from s and removing them causing the left and the right side of the deleted substring to concatenate together.

We repeatedly make k duplicate removals on s until we no longer can.

Return the final string after all such duplicate removals have been made.

It is guaranteed that the answer is unique.



Example 1:

Input: s = "abcd", k = 2
Output: "abcd"
Explanation: There's nothing to delete.
Example 2:

Input: s = "deeedbbcccbdaa", k = 3
Output: "aa"
Explanation:
First delete "eee" and "ccc", get "ddbbbdaa"
Then delete "bbb", get "dddaa"
Finally delete "ddd", get "aa"
Example 3:

Input: s = "pbbcggttciiippooaais", k = 2
Output: "ps"


Constraints:

1 <= s.length <= 10^5
2 <= k <= 10^4
s only contains lower case English letters.
*/
class Solution {
public:
    string removeDuplicates(string s, int k) {
        int pos = (int)s.size() - 1;
        pos = removeDuplicates(s, pos, k);
        return s.substr(0, pos+1);
    }
    int removeDuplicates(string& s, int pos, int k) {
        int cnt = 0;
        int i = -1, j = 0;
        int sz = pos + 1;
        while (j < sz) {
            if (i < 0 or s[j] != s[i]) {
                s[++i] = s[j++];
                cnt = 0;
            } else {
                cnt++;
                if (cnt == k-1) {
                    i -= cnt;
                    j++;
                    cnt = 0;
                } else {
                    s[++i] = s[j++];
                }
            }
        }
        if (i < pos) {
            return removeDuplicates(s, i, k);
        } else {
            return pos;
        }
    }
};
