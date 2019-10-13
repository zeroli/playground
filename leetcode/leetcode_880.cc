/*
880. Decoded String at Index
Medium
https://leetcode.com/problems/decoded-string-at-index/

An encoded string S is given.  To find and write the decoded string to a tape, the encoded string is read one character at a time and the following steps are taken:

If the character read is a letter, that letter is written onto the tape.
If the character read is a digit (say d), the entire current tape is repeatedly written d-1 more times in total.
Now for some encoded string S, and an index K, find and return the K-th letter (1 indexed) in the decoded string.



Example 1:

Input: S = "leet2code3", K = 10
Output: "o"
Explanation:
The decoded string is "leetleetcodeleetleetcodeleetleetcode".
The 10th letter in the string is "o".
Example 2:

Input: S = "ha22", K = 5
Output: "h"
Explanation:
The decoded string is "hahahaha".  The 5th letter is "h".
Example 3:

Input: S = "a2345678999999999999999", K = 1
Output: "a"
Explanation:
The decoded string is "a" repeated 8301530446056247680 times.  The 1st letter is "a".


Note:

2 <= S.length <= 100
S will only contain lowercase letters and digits 2 through 9.
S starts with a letter.
1 <= K <= 10^9
The decoded string is guaranteed to have less than 2^63 letters.
*/
class Solution {
public:
    string decodeAtIndex(string S, int K) {
        long size = 0;
        for (int i = 0; i < (int)S.size(); i++) {
            if (S[i] <= 'z' and S[i] >= 'a') {
                size++;
            } else {
                size = size * (S[i] - '0');
            }
        }
        for (int i = (int)S.size()-1; i >= 0; i--) {
            K %= size;
            if (K == 0 and (S[i] <= 'z' and S[i] >= 'a')) {
                return string(1, S[i]);
            }
            if (isdigit(S[i])) {
                size /= S[i] - '0';
            } else {
                size--;
            }
        }
        return "";
    }
    // recursive solution
    string decodeAtIndex3(string S, int K) {
        long long strLength = 0;
        for (int i = 0; i < S.length(); i++) {
            if (isalpha(S[i])) {
                if (strLength == K-1) return S.substr(i, 1);
                strLength++;
            } else {
                if (strLength * (S[i]-'0') >= K) return decodeAtIndex(S.substr(0, i), (K-1)%strLength+1);
                strLength *= S[i]-'0';
            }
        }
    }
    string decodeAtIndex2(string S, int K) {
        int sz = (int)S.size();
        vector<pair<int, int>> letters_stk;
        vector<int> n_stk;
        int k1 = -1, k2 = -2;
        for (int i = 0; i < sz; i++) {
            if (S[i] <= 'z' and S[i] >= 'a') {
                if (k1 < 0) k1 = i;
                k2 = i;
                if (i == sz - 1) {
                    letters_stk.push_back(make_pair(k1, k2));
                    n_stk.push_back(1);
                }
            } else {
                letters_stk.push_back(make_pair(k1, k2));
                n_stk.push_back((int)(S[i] - '0'));
                k1 = -1, k2 = -2;
            }
        }
        sz = (int)letters_stk.size();
        long len = 0;
        for (int i = 0; i < sz; i++) {
            long len0 = len;
            long len1 = letters_stk[i].second - letters_stk[i].first + 1;
            len = (len0 + len1) * n_stk[i];
            if (len >= K) {
                int k = K-1;
                while (i >= 0) {
                    k = k % (len0 + len1);
                    if (k < len0) { // at left side
                        len1 = letters_stk[i-1].second - letters_stk[i-1].first + 1;
                        len0 = len0 / n_stk[i-1] - len1;
                        i--;
                    } else { // at right side
                        return string(1, S[k-len0+letters_stk[i].first]);
                    }
                }
            }
        }
        return "";
    }
    string decodeAtIndex1(string S, int K) {
        int sz = (int)S.size();
        string res;
        for (int i = 0; i < sz; i++) {
            if (S[i] <= 'z' and S[i] >= 'a') {
                res.push_back(S[i]);
            } else {
                if (!repeat(res, (int)(S[i]-'0'), K)) {
                    return string(1, res[K-1]);
                }
            }
        }
        return (K > (int)res.size()) ? "" : string(1, res[K-1]);
    }
private:
    bool repeat(string& res, int d, int K) {
        if ((int)res.size() >= K) {
            return false;
        }
        string res0 = res;
        while (--d > 0) {
            res += res0;
            if ((int)res.size() >= K) {
                return false;
            }
        }
        return true;
    }
};
