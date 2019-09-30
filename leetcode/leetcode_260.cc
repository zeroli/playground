/*
260. Single Number III
https://leetcode.com/problems/single-number-iii/

Given an array of numbers nums, in which exactly two elements appear only once and all the other elements appear exactly twice. Find the two elements that appear only once.

Example:

Input:  [1,2,1,3,2,5]
Output: [3,5]
Note:

The order of the result is not important. So in the above example, [5, 3] is also correct.
Your algorithm should run in linear runtime complexity. Could you implement it using only constant space complexity?
*/
class Solution {
public:
    // use right most bit
    vector<int> singleNumber(vector<int>& nums) {
        int x = 0;
        for (auto n : nums) x ^= n;
        int p = x & (~(x-1)); // ******, get right-most bit

        int a = 0, b = 0;
        for (auto n : nums) {
            if ((n & p)) {
                a ^= n;
            }
            else {
                b ^= n;
            }
        }
        vector<int> ans;
        ans.push_back(a);
        ans.push_back(b);
        return ans;
    }
    // use left most bit
    vector<int> singleNumber1(vector<int>& nums) {
        int x = 0;
        for (auto n : nums) x ^= n;
        int p;
        for (int i = 31; i>=0; --i) {
            if (((1u) << i) & x) {
                p = (1u) << i;
                break;
            }
        }
        int a = 0, b=  0;
        for (auto n : nums) {
            if ((n & p)) {
                a ^= n;
            }
            else {
                b ^= n;
            }
        }
        vector<int> ans;
        ans.push_back(a);
        ans.push_back(b);
        return ans;
    }
};h
