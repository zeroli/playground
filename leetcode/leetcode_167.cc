/*
167. Two Sum II - Input array is sorted
https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/

Given an array of integers that is already sorted in ascending order, find two numbers such that they add up to a specific target number.

The function twoSum should return indices of the two numbers such that they add up to the target, where index1 must be less than index2.

Note:

Your returned answers (both index1 and index2) are not zero-based.
You may assume that each input would have exactly one solution and you may not use the same element twice.
Example:

Input: numbers = [2,7,11,15], target = 9
Output: [1,2]
Explanation: The sum of 2 and 7 is 9. Therefore index1 = 1, index2 = 2.
*/
class Solution {
public:
    // O(n)
    vector<int> twoSum(vector<int>& numbers, int target) {
        int i = 0;
        int j = (int)numbers.size()-1;
        while (i < j) {
            int check = numbers[i] + numbers[j];
            if (check == target) {
                return vector<int>{i+1, j+1};
            } else if (check < target) {
                i++;
            } else {
                j--;
            }
        }
        return vector<int>();
    }
    // use binary search O(nlgn)
    vector<int> twoSum1(vector<int>& numbers, int target) {
        for (int i = 0; i < (int)numbers.size(); i++) {
            int val = target - numbers[i];
            if (val < numbers[i]) {
                break;
            } else {
                int f = binarySearch(numbers, i+1, (int)numbers.size()-1, val);
                if (f < 0) {
                    continue;
                } else {
                    return vector<int>({i+1, f+1});
                }
            }
        }
        return vector<int>{0, 0};
    }
private:
    int binarySearch(vector<int>& numbers, int l, int r, int val) {
        while (l <= r) {
            int mid = l + (r-l)/2;
            if (numbers[mid] == val) {
                return mid;
            } else if (val < numbers[mid]) {
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return -1;
    }
};
