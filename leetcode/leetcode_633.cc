/*
633. Sum of Square Numbers
https://leetcode.com/problems/sum-of-square-numbers/

Given a non-negative integer c, your task is to decide whether there're two integers a and b such that a2 + b2 = c.

Example 1:

Input: 5
Output: True
Explanation: 1 * 1 + 2 * 2 = 5


Example 2:

Input: 3
Output: False
*/
class Solution {
public:
    bool judgeSquareSum(int c) {
        return judgeSquareSum1(c);
    }
private:
    bool judgeSquareSum1(int c) {
        int lc = (int)sqrt(c);
        int l = 0, r = lc;
        while (l <= r) {
            int vv = c - l*l;
            if (vv < l) {
                break;
            }
            vv = binarySearch(l, vv, vv);
            if (vv < 0) {
                l++;
            } else { // we find them
                return true;
            }
        }
        return false;
    }
    bool judgeSquareSum2(int c) {
        int l = 0;
        while (l*l <= c) {
            int vv = (int)sqrt(c - l*l);
            if (vv < l) break;
            if (vv * vv + l * l == c) { return true; }
            l++;
        }
        return false;
    }
    bool judgeSquareSum3(int c) {
        long l = 0;
        while (l*l <= c) {
            long vv = c - l*l;
            if (isSquaredNum(vv)) return true;
            l++;
        }
        return false;
    }
private:
    int binarySearch(int l, int r, int vv) {
        while (l <= r) {
            int mid = l + (r-l)/2;
            long mm = long(mid) * mid;
            if (vv == mm) {
                return mid;
            } else if (vv < mm) {
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return -1;
    }
    bool isSquaredNum(long b) {
        //n^2 =1+3+5+...+(2⋅n−1)=∑(2⋅i−1) (i=1..n)
        long sum = 0;
        int i = 1;
        while (sum < b) {
            sum += i;
            i += 2;
        }
        return sum == b;
    }
};
