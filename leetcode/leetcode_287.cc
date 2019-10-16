/*
287. Find the Duplicate Number
Medium
https://leetcode.com/problems/find-the-duplicate-number/

Given an array nums containing n + 1 integers where each integer is between 1 and n (inclusive), prove that at least one duplicate number must exist. Assume that there is only one duplicate number, find the duplicate one.

Example 1:

Input: [1,3,4,2,2]
Output: 2
Example 2:

Input: [3,1,3,4,2]
Output: 3
Note:

You must not modify the array (assume the array is read only).
You must use only constant, O(1) extra space.
Your runtime complexity should be less than O(n2).
There is only one duplicate number in the array, but it could be repeated more than once.
*/
class Solution {
public:
    // use solution of cycle finding in linked list
    // find the entrance of the cycle, that is the duplicated number
    // [1,3,4,2,2]
    // => linked list: 1 => 3 => 2 (second 2 at index 3, indexed by second number 3)=> 4 => 2 (go back)
    // if problem allows to modify input array, we could change slot number that current number is indexing to negative
    // and then once we found that that number is negative, when we reach to one number later, that means this slot number
    // already was modified or indexed by another same number, and this number is duplicated
    int findDuplicate(vector<int>& nums) {
        if (nums.size() <= 1) return 0;
        int slow = nums[0];
        int fast = nums[0];
        while (1) {
            fast = nums[nums[fast]];
            slow = nums[slow];
            if (fast == slow) break;
        }
        slow = nums[0];
        while (slow != fast) {
            slow = nums[slow];
            fast = nums[fast];
        }
        return slow;
    }
};
