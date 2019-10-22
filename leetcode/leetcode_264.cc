/*
264. Ugly Number II
Medium
https://leetcode.com/problems/ugly-number-ii/

Write a program to find the n-th ugly number.

Ugly numbers are positive numbers whose prime factors only include 2, 3, 5.

Example:

Input: n = 10
Output: 12
Explanation: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 is the sequence of the first 10 ugly numbers.
Note:

1 is typically treated as an ugly number.
n does not exceed 1690.
*/
class Solution {
public:
    int nthUglyNumber(int n) {
        if (n == 1) return 1;
        queue<long> q2, q3, q5;
        q2.push(2);
        q3.push(3);
        q5.push(5);
        int m = 1;
        int km = 1;
        while (m < n) {
            km = min(min(q2.front(), q3.front()), q5.front());
            if (km == q2.front()) {
                q2.pop();
                q2.push(km * 2L);
                q3.push(km * 3L);
                q5.push(km * 5L);
            } else if (km == q3.front()) {
                q3.pop();
                q3.push(km * 3L);
                q5.push(km * 5L);
            } else {
                q5.pop();
                q5.push(km * 5L);
            }
            m++;
        }
        return km;
    }
};
