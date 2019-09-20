/*
344. Reverse String
Write a function that reverses a string. The input string is given as an array of characters char[].

Do not allocate extra space for another array, you must do this by modifying the input array in-place with O(1) extra memory.

You may assume all the characters consist of printable ascii characters.



Example 1:

Input: ["h","e","l","l","o"]
Output: ["o","l","l","e","h"]
Example 2:

Input: ["H","a","n","n","a","h"]
Output: ["h","a","n","n","a","H"]
*/
class Solution {
public:
    void reverseString(vector<char>& s) {
        size_t sz = s.size();
        size_t midpos = sz / 2;
        for (size_t ip = 0; ip < midpos; ip++) {
            char c = s[ip];
            s[ip] = s[sz - ip - 1];
            s[sz - ip - 1] = c;
        }
    }
};
