/*
665. Non-decreasing Array
https://leetcode.com/problems/non-decreasing-array/

Given an array with n integers, your task is to check if it could become non-decreasing by modifying at most 1 element.

We define an array is non-decreasing if array[i] <= array[i + 1] holds for every i (1 <= i < n).

Example 1:
Input: [4,2,3]
Output: True
Explanation: You could modify the first 4 to 1 to get a non-decreasing array.
Example 2:
Input: [4,2,1]
Output: False
Explanation: You can't get a non-decreasing array by modify at most one element.
Note: The n belongs to [1, 10,000].
*/
class Solution {
public:
    bool checkPossibility(vector<int>& nums) {
        int cnt = 0;
        int n = (int)nums.size();
        for (int i = 0; i < n-1; i++) {
            if (nums[i] > nums[i+1]) {
                if (cnt++ > 0) return false;
                // either make nums[i] ==> nums[i+1] or nums[i+1] ==> num[i]
                if (i < 1 or nums[i+1] >= nums[i-1]) {
                    nums[i] = nums[i+1]; // lower i
                } else { // i >= 1 and nums[i+1] < nums[i-1]
                    nums[i+1] = nums[i]; // raise i+1
                }
            }
        }
        return true;
    }
    bool checkPossibility1(vector<int>& nums) {
        int n = (int)nums.size();
        for (int i = 0; i < n; i++) {
            bool ret = nondecrease(nums, 0, i-1);
            if (i >= 1 and i <= n-2 and nums[i-1] > nums[i+1])
                ret = false;
            ret = ret && nondecrease(nums, i+1, n-1);
            if (ret) return true;
        }
        return false;
    }
private:
    bool nondecrease(vector<int>& nums, int l, int r) {
        for (int m = l; m < r; m++) {
            if (nums[m] > nums[m+1])
                return false;
        }
        return true;
    }
};
