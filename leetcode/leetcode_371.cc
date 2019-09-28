/*
371. Sum of Two Integers
https://leetcode.com/problems/sum-of-two-integers/

Calculate the sum of two integers a and b, but you are not allowed to use the operator + and -.

Example 1:

Input: a = 1, b = 2
Output: 3
Example 2:

Input: a = -2, b = 3
Output: 1
*/
class Solution {
public:
    int getSum(int a, int b) {
        while(b != 0)
        {
            unsigned int carry = a&b;
            a = a^b;
            b = carry<<1;
        }

        return a;
    }
	int getSum1(int a, int b) {
		int res = 0;
		unsigned pos = 0;
		unsigned c = 0;
		while (pos < 32) {
			unsigned k = bitAdd(a, b, pos, c);
			res |= k;
			pos++;
		}
		return res;
	}
private:
	unsigned bitpos(unsigned pos) {
		return 1 << pos;
	}
	unsigned bitAdd(unsigned a, unsigned b, unsigned pos, unsigned& c) {
		unsigned p = a ^ b;
		unsigned q = a & b;
		unsigned bp = bitpos(pos);
		p = p & bp;
		q = q & bp;
		if (c > 0) {
			unsigned c0 = 0;
			p = bitAdd(p, (c << pos), pos, c0);
			unsigned c1 = 0;
			q = bitAdd(q, (c0 << pos), pos, c1);
		}
		c = q >> pos;
		return p;
	}
};
