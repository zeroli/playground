/*
88. Merge Sorted Array
https://leetcode.com/problems/merge-sorted-array/

Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as one sorted array.

Note:

The number of elements initialized in nums1 and nums2 are m and n respectively.
You may assume that nums1 has enough space (size that is greater or equal to m + n) to hold additional elements from nums2.
Example:

Input:
nums1 = [1,2,3,0,0,0], m = 3
nums2 = [2,5,6],       n = 3

Output: [1,2,2,3,5,6]
*/
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        m--;
        n--;
        // merge from end to beginning
        int mm = (int)nums1.size();
        for (int i = mm-1; i >= 0; i--) {
            if (m >= 0 and n >= 0) {
                if (nums1[m] > nums2[n]) {
                    nums1[i] = nums1[m];
                    m--;
                } else {
                    nums1[i] = nums2[n];
                    n--;
                }
            } else if (m < 0) {
                nums1[i] = nums2[n];
                n--;
            } else if (n < 0) {
                nums1[i] = nums1[m];
                m--;
            }
        }
    }
    void _merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        for (int i = 0; i < (int)nums2.size(); i++) {
            insertSort(nums1, m++, nums2[i]);
        }
    }
private:
    void insertSort(vector<int>& nums, int m, int k) {
        int i = m-1;
        while (i >= 0 and k < nums[i]) {
            nums[i+1] = nums[i];
            i--;
        }
        nums[i+1] = k;
    }
};
