/*
1051. Height Checker

Students are asked to stand in non-decreasing order of heights for an annual photo.

Return the minimum number of students not standing in the right positions.  (This is the number of students that must move in order for all students to be standing in non-decreasing order of height.)



Example 1:

Input: [1,1,4,2,1,3]
Output: 3
Explanation:
Students with heights 4, 3 and the last 1 are not standing in the right positions.


Note:

1 <= heights.length <= 100
1 <= heights[i] <= 100
*/
class Solution {
public:
    int heightChecker(vector<int>& heights) {
        int sz = int(heights.size());
        vector<int> sortedh(heights);
        insertSort(sortedh);
        int cnt = 0;
        for (int i = 0; i < sz; i++) {
            if (heights[i] != sortedh[i]) {
                cnt++;
            }
        }
        return cnt;
    }
private:
    void insertSort(vector<int>& sorted) {
        int sz = int(sorted.size());
        for (int j = 1; j < sz; j++) {
            int h = sorted[j];
            int i = j - 1;
            while (i >= 0 and h < sorted[i]) {
                sorted[i+1] = sorted[i];
                i--;
            }
            sorted[i+1] = h;
        }
    }
};
