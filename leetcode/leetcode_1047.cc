/*
1047. Remove All Adjacent Duplicates In String
Easy
https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string/

Given a string S of lowercase letters, a duplicate removal consists of choosing two adjacent and equal letters, and removing them.

We repeatedly make duplicate removals on S until we no longer can.

Return the final string after all such duplicate removals have been made.  It is guaranteed the answer is unique.



Example 1:

Input: "abbaca"
Output: "ca"
Explanation:
For example, in "abbaca" we could remove "bb" since the letters are adjacent and equal, and this is the only possible move.  The result of this move is that the string is "aaca", of which only "aa" is possible, so the final string is "ca".


Note:

1 <= S.length <= 20000
S consists only of English lowercase letters.
*/
class Solution {
public:
    string removeDuplicates(string S) {
        // use stack similar structure, but not create one stack really
        int i = -1, j = 0;
        int sz = (int)S.size();
        while (j < sz) {
            if (i < 0 or S[j] != S[i]) {
                S[++i] = S[j++];
            } else {
                j++;
                i--;
            }
        }
        return S.substr(0, i+1);
    }
};
