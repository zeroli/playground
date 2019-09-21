/*
342. Power of Four

Given an integer (signed 32 bits), write a function to check whether it is a power of 4.

Example 1:

Input: 16
Output: true
Example 2:

Input: 5
Output: false
Follow up: Could you solve it without loops/recursion?
*/
class Solution {
public:
    bool isPowerOfFour(int num) {
        if (num <= 0) return false;
        if (num == 1) return true;

        double x = log2(num) / 2;
        if (x - int(x) < 1e-8) {
            return true;
        }
        return false;
    }
};

class Solution {
public:
    bool isPowerOfFour(int num) {
        /*
        4 ^ x = n => x = log4(n) = log2(n) / log2(4) => x = log2(n) / 2
        if n is power of 2, and then log2(n) is even number, x will be one integer, so that num will be power of 4
        the problem of n is power of 2 will be using num & (num-1) to check
        */
        if (num == 1) return true;
        if (num == 4) return true;
        if (num < 4) return false;
        if (num & (num-1)) { // not power of 2
            return false;
        } else {
            int pos = 0;
            while (num = num >> 1) {
                pos++;
            }
            return (pos & 0x01) == 0;
        }
    }
};
