/*
Given a non-empty array of integers, every element appears twice except for one. Find that single one.

Note:

Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?

Example 1:

Input: [2,2,1]
Output: 1
Example 2:

Input: [4,1,2,1,2]
Output: 4
*/

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int res = 0;
        for (int i = 0; i < (int)nums.size(); i++) {
            res ^= nums[i];
        }
        return res;
    }
    int _singleNumber(vector<int>& nums) {
        int l = 0, r = int(nums.size()) - 1;
        while (l < r) {
            int equal = -1;
            int pivot = partition(nums, l, r, equal);
            if ((pivot - l) % 2 == 0) { // left part# is even, single number should be there or this pivot
                if (equal == -1) {
                    return nums[pivot];
                } else {
                    swap(nums[l], nums[equal]);
                    l++;
                    r = pivot - 1;
                }
            } else { // otherwise, single number should be at right
                l = pivot + 1;
            }
        }
        return nums[l];
    }
private:
    // partition list to left part(<=pivot), pivot, right part(>pivot)
    int partition(vector<int>& nums, int l, int r, int& equal) {
        if (l >= r) return l;
        int p = r;
        int pivot = nums[p];
        int i = l, j = l;
        while (j < r) {
            if (nums[j] <= pivot) {
                swap(nums[j], nums[i]);
                if (nums[i] == pivot) {
                    equal = i; // record swapped position
                }
                i++;
            }
            j++;
        }
        swap(nums[i], nums[p]);
        return i;
    }
};
