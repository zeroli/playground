/*
784. Letter Case Permutation
https://leetcode.com/problems/letter-case-permutation/

Given a string S, we can transform every letter individually to be lowercase or uppercase to create another string.  Return a list of all possible strings we could create.

Examples:
Input: S = "a1b2"
Output: ["a1b2", "a1B2", "A1b2", "A1B2"]

Input: S = "3z4"
Output: ["3z4", "3Z4"]

Input: S = "12345"
Output: ["12345"]
Note:

S will be a string with length between 1 and 12.
S will consist only of letters or digits.
*/
class Solution {
public:
    // use bit manipulation
    // treat those alpha as 1/0 to vary
    vector<string> letterCasePermutation(string S) {
        vector<int> index;
        for (int i = 0; i < S.size(); ++i)
            if (isalpha(S[i]))
                index.push_back(i);

        vector<string> result;
        int num = pow(2,index.size());
        for (int i = 0; i < num; ++i) {
            for (int j = 0; j < index.size(); ++j) {
                if ((i >> j) & 1)
                    S[index[j]] = toupper(S[index[j]]);
                else
                    S[index[j]] = tolower(S[index[j]]);
            }

            result.push_back(S);
        }

        return result;
    }
    vector<string> letterCasePermutation1(string S) {
        vector<string> reslist;
        string res0;
        _letterCasePermutation(S, 0, res0, reslist);
        return reslist;
    }
private:
    void _letterCasePermutation(string S, int k, string res0, vector<string>& reslist) {
        if (k >= (int)S.size()) {
            reslist.push_back(res0);
            return;
        }

        if (isdigit(S[k])) {
            _letterCasePermutation(S, k+1, res0 + S[k], reslist);
        } else {
            _letterCasePermutation(S, k+1, res0 + (char)toupper(S[k]), reslist);
            _letterCasePermutation(S, k+1, res0 + (char)tolower(S[k]), reslist);
        }
    }
};
