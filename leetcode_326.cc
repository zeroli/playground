/*
326. Power of Three
https://leetcode.com/problems/power-of-three/
Given an integer, write a function to determine if it is a power of three.

Example 1:

Input: 27
Output: true
Example 2:

Input: 0
Output: false
Example 3:

Input: 9
Output: true
Example 4:

Input: 45
Output: false
*/
class Solution {
public:
    bool isPowerOfThree(int n) {
        if (n == 1) return true;
        if (n < 3) return false;
        if (n == 3) return true;
        // 3 ^ 19 < 2 ^ 31, and 3 is prime number
        // all n will be divisor of this below number
        int maxpower3 = 1162261467;
        return (maxpower3 % n) == 0;
    }

    bool _isPowerOfThree(int n) {
        if (n == 1) return true;
        if (n < 3) return false;
        if (n == 3) return true;

        while (n > 1) {
            if ((n % 3) != 0) return false;
            n /= 3;
        }
        return true;
    }
};
