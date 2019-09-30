/*
189. Rotate Array
https://leetcode.com/problems/rotate-array/

Given an array, rotate the array to the right by k steps, where k is non-negative.

Example 1:

Input: [1,2,3,4,5,6,7] and k = 3
Output: [5,6,7,1,2,3,4]
Explanation:
rotate 1 steps to the right: [7,1,2,3,4,5,6]
rotate 2 steps to the right: [6,7,1,2,3,4,5]
rotate 3 steps to the right: [5,6,7,1,2,3,4]
Example 2:

Input: [-1,-100,3,99] and k = 2
Output: [3,99,-1,-100]
Explanation:
rotate 1 steps to the right: [99,-1,-100,3]
rotate 2 steps to the right: [3,99,-1,-100]
Note:

Try to come up as many solutions as you can, there are at least 3 different ways to solve this problem.
Could you do it in-place with O(1) extra space?
*/
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = (int)nums.size();
        k = k % n;
        if (k == 0) return;

        int l1 = 0, r1 = n-k-1, l2 = r1+1, r2 = n-1;
        swapPortions(nums, l1, r1, l2, r2);
    }

private:
    void swapPortions(vector<int>& nums, int l1, int r1, int l2, int r2) {
        int len1 = r1-l1+1;
        int len2 = r2-l2+1;
        if (len1 == 0 or len2 == 0) return;

        if (len1 <= len2) {
            int s1 = r1, s2 = r2;
            while (s1 >= l1) {
                swap(nums[s1--], nums[s2--]);
            }
            swapPortions(nums, l1, r1, l2, s2);
        } else {
            int s1 = l1, s2 = l2;
            while (s2 <= r2) {
                swap(nums[s1++], nums[s2++]);
            }
            swapPortions(nums, s1, r1, l2, r2);
        }
    }
};
