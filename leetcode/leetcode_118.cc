/*
118. Pascal's Triangle
https://leetcode.com/problems/pascals-triangle/

Given a non-negative integer numRows, generate the first numRows of Pascal's triangle.
In Pascal's triangle, each number is the sum of the two numbers directly above it.

Example:

Input: 5
Output:
[
     [1],
    [1,1],
   [1,2,1],
  [1,3,3,1],
 [1,4,6,4,1]
]
*/
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> res;
        if (numRows >= 1) {
            res.push_back({1});
        }
        if (numRows >= 2) {
            res.push_back({1, 1});
        }
        for (int i = 2; i < numRows; i++) {
            res.push_back({});
            auto& row = res.back();
            row.push_back(1);
            for (int j = 1; j < i; j++) {
                row.push_back(res[i-1][j] + res[i-1][j-1]);
            }
            row.push_back(1);
        }
        return res;
    }
};