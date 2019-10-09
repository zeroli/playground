/*
33. Search in Rotated Sorted Array
Medium
https://leetcode.com/problems/search-in-rotated-sorted-array/

Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e., [0,1,2,4,5,6,7] might become [4,5,6,7,0,1,2]).

You are given a target value to search. If found in the array return its index, otherwise return -1.

You may assume no duplicate exists in the array.

Your algorithm's runtime complexity must be in the order of O(log n).

Example 1:

Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4
Example 2:

Input: nums = [4,5,6,7,0,1,2], target = 3
Output: -1
*/
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l = 0, r = (int)nums.size()-1;
        while (l <= r) {
            int mid = l + (r-l)/2;
            if (nums[mid] == target) {
                return mid;
            }
            if (nums[mid] <= nums[r]) { // ascending order at right
                if (target > nums[mid] and target <= nums[r]) { // in the range of right side
                    l = mid + 1;
                } else { // in the range of left side
                    r = mid - 1;
                }
            } else if (nums[mid] >= nums[l]) { // ascending order at left
                if (target >= nums[l] and target < nums[mid]) {  // in the range of left side
                    r = mid - 1;
                } else { // in the range of right side
                    l = mid + 1;
                }
            }
        }
        return -1;
    }
};
