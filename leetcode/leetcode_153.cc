/*
153. Find Minimum in Rotated Sorted Array
Medium
https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/

Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e.,  [0,1,2,4,5,6,7] might become  [4,5,6,7,0,1,2]).

Find the minimum element.

You may assume no duplicate exists in the array.

Example 1:

Input: [3,4,5,1,2]
Output: 1
Example 2:

Input: [4,5,6,7,0,1,2]
Output: 0
*/
class Solution {
public:
    int findMin(vector<int>& nums) {
        int sz = (int)nums.size();
        int l = 0, r = sz-1;
        while (l < r) {
            if (nums[l] < nums[r]) { // early termination
                return nums[l];
            }
            int mid = l + (r-l)/2;
            // = check for only 2 values is there(mid=l case)
            if (nums[mid] >= nums[l]) {  // left is sorted
                l = mid + 1; // minimum is at right
            } else {
                r = mid; // minimum is at left
            }
        }
        return nums[l];
    }
    // if duplicates exist
    int findMin(vector<int>& nums) {
        int sz = (int)nums.size();
        int l = 0, r = sz-1;
        while (l < r) {
            if (nums[l] < nums[r]) { // early termination
                return nums[l];
            }
            int mid = l + (r-l)/2;
            if (nums[mid] == nums[l] and nums[mid] == nums[r]) {
                // there are 3 cases that could result in this
                // 1) low => low => jump up => lower => mid
                // 2) low => low => low => low => mid (all equal)
                // 3) low => low => jump down => higher => mid
                while (l < mid) {
                    if (nums[l] == nums[mid]) { // case 2
                        l++; // eventually min will be found at right side
                    } else if (nums[l] < nums[mid]) { // case 3
                        return nums[l];
                    } else { // case 1
                        r = mid;
                        break; // continue to do again
                    }
                }
            } else {
                // = check for only 2 values is there(mid=l case)
                if (nums[mid] >= nums[l]) {  // left is sorted
                    l = mid + 1; // minimum is at right
                } else {
                    r = mid; // minimum is at left
                }
            }
        }
        return nums[l];
    }
};
