/*
561. Array Partition I
Given an array of 2n integers, your task is to group these integers into n pairs of integer, say (a1, b1), (a2, b2), ..., (an, bn) which makes sum of min(ai, bi) for all i from 1 to n as large as possible.

Example 1:
Input: [1,4,3,2]

Output: 4
Explanation: n is 2, and the maximum sum of pairs is 4 = min(1, 2) + min(3, 4).
Note:
n is a positive integer, which is in the range of [1, 10000].
All the integers in the array will be in the range of [-10000, 10000].
*/
class Solution {
public:
    int arrayPairSum(vector<int>& nums) {
        int counts[20001] = {0};
        int sz = int(nums.size());
        for (int i = 0; i < sz; i++) {
            counts[nums[i]+10000]++;
        }
        bool even = true;
        int sum = 0;
        for (int i = 0; i < 20001; i++) {
            while (counts[i] > 0) {
                if (even) {
                    sum += i - 10000;
                }
                even = !even;
                counts[i]--;
            }
        }
        return sum;
    }
    int _arrayPairSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int sz = int(nums.size());
        int sum = 0;
        for (int i = 0; i < sz; i+=2) {
            sum += nums[i];
        }
        return sum;
    }
};
