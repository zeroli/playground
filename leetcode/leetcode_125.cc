/*
125. Valid Palindrome
https://leetcode.com/problems/valid-palindrome/

Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.

Note: For the purpose of this problem, we define empty string as valid palindrome.

Example 1:

Input: "A man, a plan, a canal: Panama"
Output: true
Example 2:

Input: "race a car"
Output: false
*/
/*
this solution is using iterative, while it also could be solved using recursive method
*/
class Solution {
public:
    bool isPalindrome(string s) {
        int i = 0;
        int j = (int)s.size() -1;
        while (i < j) {
            while (not isalnum(s[i])) {
                i++;
                if (i >= (int)s.size()) return true; // take care of this
            }
            while (not isalnum(s[j])) {
                j--;
                if (j < 0) return true; // take care of this
            }
            if (i >= j) break;
            if (tolower(s[i]) == tolower(s[j])) {
                i++;
                j--;
            } else {
                return false;
            }
        }
        return true;
    }
};
