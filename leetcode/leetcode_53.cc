/*
53. Maximum Subarray
https://leetcode.com/problems/maximum-subarray/

Given an integer array nums, find the contiguous subarray (containing at least one number) which has the largest sum and return its sum.

Example:

Input: [-2,1,-3,4,-1,2,1,-5,4],
Output: 6
Explanation: [4,-1,2,1] has the largest sum = 6.
Follow up:

If you have figured out the O(n) solution, try coding another solution using the divide and conquer approach, which is more subtle.
*/
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int sum = 0;
        int maxsum = 0;
        bool allnegative = true;
        int maxnegative = INT_MIN;
        for (size_t i = 0; i < nums.size(); i++) {
            if (nums[i] >= 0) {
                allnegative = false;
            } else if (allnegative) {
                maxnegative = nums[i] > maxnegative ? nums[i] : maxnegative;
            }
            sum += nums[i];
            if (sum > maxsum) {
                maxsum = sum;
            } else if (sum < 0) {
                sum = 0;
            }
        }
        if (allnegative) {
            return maxnegative;
        }
        return maxsum;
    }
};
