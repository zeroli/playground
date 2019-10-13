/*
402. Remove K Digits
Medium
https://leetcode.com/problems/remove-k-digits/

Given a non-negative integer num represented as a string, remove k digits from the number so that the new number is the smallest possible.

Note:
The length of num is less than 10002 and will be ≥ k.
The given num does not contain any leading zero.
Example 1:

Input: num = "1432219", k = 3
Output: "1219"
Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219 which is the smallest.
Example 2:

Input: num = "10200", k = 1
Output: "200"
Explanation: Remove the leading 1 and the number is 200. Note that the output must not contain leading zeroes.
Example 3:

Input: num = "10", k = 2
Output: "0"
Explanation: Remove all the digits from the number and it is left with nothing which is 0.
*/
/*
The first algorithm is straight-forward. Let's think about the simplest case:
how to remove 1 digit from the number so that the new number is the smallest possible？
Well, one can simply scan from left to right, and remove the first "peak" digit;
the peak digit is larger than its right neighbor.
One can repeat this procedure k times, and obtain the first algorithm:

string removeKdigits(string num, int k) {
        while (k > 0) {
            int n = num.size();
            int i = 0;
            while (i+1<n && num[i]<=num[i+1])  i++;
            num.erase(i, 1);
            k--;
        }
        // trim leading zeros
        int s = 0;
        while (s<(int)num.size()-1 && num[s]=='0')  s++;
        num.erase(0, s);

        return num=="" ? "0" : num;
    }
The above algorithm is a bit inefficient because it frequently remove a particular element from a string and has complexity O(k*n).

One can simulate the above procedure by using a stack, and obtain a O(n) algorithm.
Note, when the result stack (i.e. res) pop a digit, it is equivalent as remove that "peak" digit.

string removeKdigits(string num, int k) {
        string res;
        int keep = num.size() - k;
        for (int i=0; i<num.size(); i++) {
            while (res.size()>0 && res.back()>num[i] && k>0) {
                res.pop_back();
                k--;
            }
            res.push_back(num[i]);
        }
        res.erase(keep, string::npos);

        // trim leading zeros
        int s = 0;
        while (s<(int)res.size()-1 && res[s]=='0')  s++;
        res.erase(0, s);

        return res=="" ? "0" : res;
    }
*/

class Solution {
public:
    string removeKdigits(string num, int k) {
        string ans = "";                                         // treat ans as a stack in below for loop
        for (char c : num) {
            while (ans.length() && ans.back() > c && k) {
                ans.pop_back();                                  // make sure digits in ans are in ascending order
                k--;                                             // remove one char
            }
            if (ans.length() || c != '0') { ans.push_back(c); }  // can't have leading '0'
        }

        while (ans.length() && k--) { ans.pop_back(); }          // make sure remove k digits in total
        return ans.empty() ? "0" : ans;
    }
    // wrong solution
    string removeKdigits(string num, int k) {
        if (k == 0) {
            int i = 0;
            while (i < (int)num.size()) {
                if (num[i] != '0') break;
                i++;
            }
            return num.substr(i);
        }
        if (k >= (int)num.size()) return "0";

        if (num.size() >= 2) {
            if (num[0] < num[1]) {
                swap(num[0], num[1]);
                int n1 = atoi(&num[1]);
                swap(num[0], num[1]);
                int max = findmax(num, 0, (int)num.size()-1);
                int n2 = str2num(num, 0, (int)num.size()-1, max);
                if (n1 < n2) {
                    swap(num[0], num[1]);
                    return removeKdigits(num.substr(1), k-1);
                } else {
                    return removeKdigits(num.erase(max, 1), k-1);
                }
            } else {
                return removeKdigits(num.substr(1), k-1);
            }
        }
    }
    int findmax(string& num, int l, int r) {
        int max = l;
        while (l <= r) {
            if (num[l] > max) {
                max = l;
            }
            l++;
        }
        return max;
    }
    int str2num(string& num, int l, int r, int skip) {
        int ret = 0;
        while (l <= r) {
            if (l == skip) { l++; continue; }
            ret = ret * 10 + (num[l] - '0');
        }
        return ret;
    }
};
