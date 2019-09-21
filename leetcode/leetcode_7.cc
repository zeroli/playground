/*
7. Reverse Integer
https://leetcode.com/problems/reverse-integer/

Given a 32-bit signed integer, reverse digits of an integer.

Example 1:

Input: 123
Output: 321
Example 2:

Input: -123
Output: -321
Example 3:

Input: 120
Output: 21
Note:
Assume we are dealing with an environment which could only store integers within the 32-bit signed integer range: [−231,  231 − 1].
For the purpose of this problem, assume that your function returns 0 when the reversed integer overflows.
*/
class Solution {
public:
    int reverse(int x) {
        long y = 0; // use long to avoid overflow in computation
        bool negative = false;
        if (x < 0) {
            negative = true;
            if (x == INT_MIN) return 0; // handle -2147483648
            x = -x;
        }
        while (x) {
            y = y * 10 + (x % 10);
            x /= 10;
        }
        if (negative) {
            y = -y;
        }
        if (y < INT_MIN or y > INT_MAX) return 0;
        return (int)y;
    }
};
