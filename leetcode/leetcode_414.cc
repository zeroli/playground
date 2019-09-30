/*
414. Third Maximum Number
https://leetcode.com/problems/third-maximum-number/

Given a non-empty array of integers, return the third maximum number in this array. If it does not exist, return the maximum number. The time complexity must be in O(n).

Example 1:
Input: [3, 2, 1]

Output: 1

Explanation: The third maximum is 1.
Example 2:
Input: [1, 2]

Output: 2

Explanation: The third maximum does not exist, so the maximum (2) is returned instead.
Example 3:
Input: [2, 2, 3, 1]

Output: 1

Explanation: Note that the third maximum here means the third maximum distinct number.
Both numbers with value 2 are both considered as second maximum.
*/
class Solution {
public:
    int thirdMax(vector<int>& nums) {
        if (nums.size() < 3) return max(nums[0], nums[1]);

        // input may contains INT_MIN
        long a = (long)INT_MIN-1, b = (long)INT_MIN-1, c = (long)INT_MIN-1;
        // a > b > c
        for (int i = 0; i < (int)nums.size(); i++) {
            int k = nums[i];
            if (k < c or k == a or k == b) continue;
            c = k;
            if (c > b) swap(b, c);
            if (b > a) swap(a, b);
        }
        return c == (long)INT_MIN-1 ? (int)a : (int)c;
    }
};
