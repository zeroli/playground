/*
81. Search in Rotated Sorted Array II
Medium
https://leetcode.com/problems/search-in-rotated-sorted-array-ii/

Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e., [0,0,1,2,2,5,6] might become [2,5,6,0,0,1,2]).

You are given a target value to search. If found in the array return true, otherwise return false.

Example 1:

Input: nums = [2,5,6,0,0,1,2], target = 0
Output: true
Example 2:

Input: nums = [2,5,6,0,0,1,2], target = 3
Output: false
Follow up:

This is a follow up problem to Search in Rotated Sorted Array, where nums may contain duplicates.
Would this affect the run-time complexity? How and why?
*/
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int l = 0, r = (int)nums.size()-1;
        while (l <= r) {
            int mid = l + (r-l)/2;
            if (nums[mid] == target) {
                return true;
            }
            if (nums[mid] == nums[r] and nums[mid] == nums[l]) {
                l++;
                r--;
                continue;
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
        return false;
    }
};
