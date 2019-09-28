/*
268. Missing Number
https://leetcode.com/problems/missing-number/

Given an array containing n distinct numbers taken from 0, 1, 2, ..., n, find the one that is missing from the array.

Example 1:

Input: [3,0,1]
Output: 2
Example 2:

Input: [9,6,4,2,3,5,7,0,1]
Output: 8
Note:
Your algorithm should run in linear runtime complexity. Could you implement it using only constant extra space complexity?
*/
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = (int)nums.size();
        int res = 0;
        for (int i = 0; i < n; i++) {
            res ^= (i ^ nums[i]);
        }
        res ^= n;
        return res;
    }
    int missingNumber1(vector<int>& nums) {
        int n = (int)nums.size();
        // gauss formula
        int actualSum = 0;
        for (int i = 0; i < n; i++) {
            actualSum += nums[i];
        }
        return n * (n+1)/2 - actualSum;
    }
};
