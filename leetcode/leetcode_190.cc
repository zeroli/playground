/*
190. Reverse Bits
https://leetcode.com/problems/reverse-bits/

Reverse bits of a given 32 bits unsigned integer.



Example 1:

Input: 00000010100101000001111010011100
Output: 00111001011110000010100101000000
Explanation: The input binary string 00000010100101000001111010011100 represents the unsigned integer 43261596, so return 964176192 which its binary representation is 00111001011110000010100101000000.
Example 2:

Input: 11111111111111111111111111111101
Output: 10111111111111111111111111111111
Explanation: The input binary string 11111111111111111111111111111101 represents the unsigned integer 4294967293, so return 3221225471 which its binary representation is 10101111110010110010011101101001.


Note:

Note that in some languages such as Java, there is no unsigned integer type. In this case, both input and output will be given as signed integer type and should not affect your implementation, as the internal binary representation of the integer is the same whether it is signed or unsigned.
In Java, the compiler represents the signed integers using 2's complement notation. Therefore, in Example 2 above the input represents the signed integer -3 and the output represents the signed integer -1073741825.

 */
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        int j = 0, k = 0;
        while (j < 16) {
            k = 32 - j - 1;
            n = swapBit(n, j, k);
            j++;
        }
        return n;
    }
private:
    #define getBit(n, j) \
       (n & (0x1L << j)) >> j
    #define setBit(n, j, v) \
        n = (n & ~(((0x1L << j) - 1) | (0x1L << j))) | \
                (n & ((0x1L << j) - 1)) |  \
                (v << j) // that bit

    uint32_t swapBit(uint32_t n, int j, int k) {
        uint32_t jj = getBit(n, j);
        uint32_t kk = getBit(n, k);
        setBit(n, j, kk);
        setBit(n, k, jj);
        return n;
    }
};
