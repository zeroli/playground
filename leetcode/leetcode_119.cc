/*
119. Pascal's Triangle II
Given a non-negative index k where k ≤ 33, return the kth index row of the Pascal's triangle.

Note that the row index starts from 0.

In Pascal's triangle, each number is the sum of the two numbers directly above it.

Example:

Input: 3
Output: [1,3,3,1]
*/
class Solution {
public:
    vector<int> getRow(int rowIndex) {
        if (rowIndex == 0) return vector<int>{1};
        if (rowIndex == 1) return vector<int>{1, 1};

        vector<int> res(rowIndex+1, 1);
        for (int i = 2; i <= rowIndex; i++) {
            for (int j = i-1; j > 0; j--) {
                res[j] += res[j-1];
            }
        }
        return res;
    }
};
