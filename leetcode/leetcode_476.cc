/*
476. Number Complement
https://leetcode.com/problems/number-complement/

Given a positive integer, output its complement number. The complement strategy is to flip the bits of its binary representation.

Note:
The given integer is guaranteed to fit within the range of a 32-bit signed integer.
You could assume no leading zero bit in the integer’s binary representation.
Example 1:
Input: 5
Output: 2
Explanation: The binary representation of 5 is 101 (no leading zero bits), and its complement is 010. So you need to output 2.
Example 2:
Input: 1
Output: 0
Explanation: The binary representation of 1 is 1 (no leading zero bits), and its complement is 0. So you need to output 0.
*/
class Solution {
public:
    int findComplement(int num) {
        if (num == 0) return 1;
        int res = num;
        int i = 0;
        unsigned unum = num;
        while (unum) {
            res ^= (1<<i); // xor operation means bit ~
            i++;
            unum >>= 1;
        }

        return res;
    }
    // below solution is wrong, we cannot use ~ to implement complement
    int findComplement1(int num) {
        if (num == 0) return 1;
        int res = 0;
        unsigned unum = num;
        int n = 0;
        while (unum) {
            res |= ((~unum) & 1) << n;
            unum >>= 1;
            n++;
        }
        return res;
    }
};
