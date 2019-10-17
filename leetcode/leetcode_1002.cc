/*
1002. Find Common Characters
Easy
https://leetcode.com/problems/find-common-characters/

Given an array A of strings made only from lowercase letters, return a list of all characters that show up in all strings within the list (including duplicates).  For example, if a character occurs 3 times in all strings but not 4 times, you need to include that character three times in the final answer.

You may return the answer in any order.



Example 1:

Input: ["bella","label","roller"]
Output: ["e","l","l"]
Example 2:

Input: ["cool","lock","cook"]
Output: ["c","o"]


Note:

1 <= A.length <= 100
1 <= A[i].length <= 100
A[i][j] is a lowercase letter
*/
class Solution {
public:
    vector<string> commonChars(vector<string>& A) {
        vector<int> m(26, INT_MAX);
        for (int i = 0; i < A.size(); i++) {
            vector<int> m1(26, 0);
            for (int j = 0; j < A[i].size(); j++) {
                m1[A[i][j]-'a']++;
            }
            for (int k = 0; k < 26; k++) {
                m[k] = min(m1[k], m[k]);
            }
        }
        vector<string> res;
        for (int k = 0; k < 26; k++) {
            if (m[k] > 0) {
                while (m[k]-- > 0) {
                    res.push_back(string(1, 'a' + k));
                }
            }
        }
        return res;
    }
};
