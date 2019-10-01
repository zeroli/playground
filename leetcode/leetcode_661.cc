/*
661. Image Smoother
https://leetcode.com/problems/image-smoother/

Given a 2D integer matrix M representing the gray scale of an image, you need to design a smoother to make the gray scale of each cell becomes the average gray scale (rounding down) of all the 8 surrounding cells and itself. If a cell has less than 8 surrounding cells, then use as many as you can.

Example 1:
Input:
[[1,1,1],
 [1,0,1],
 [1,1,1]]
Output:
[[0, 0, 0],
 [0, 0, 0],
 [0, 0, 0]]
Explanation:
For the point (0,0), (0,2), (2,0), (2,2): floor(3/4) = floor(0.75) = 0
For the point (0,1), (1,0), (1,2), (2,1): floor(5/6) = floor(0.83333333) = 0
For the point (1,1): floor(8/9) = floor(0.88888889) = 0
Note:
The value in the given matrix is in the range of [0, 255].
The length and width of the given matrix are in the range of [1, 150].
*/
class Solution {
public:
    vector<vector<int>> imageSmoother(vector<vector<int>>& M) {
        int rows = (int)M.size();
        int cols = (int)(M[0].size());
        vector<vector<int>> res(rows, vector<int>(cols, 0));
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                res[i][j] = average(M, i, j);
            }
        }
        return res;
    }
private:
    int average(vector<vector<int>>& M, int i, int j) {
        int rows = (int)M.size();
        int cols = (int)(M[0].size());
        int sum = 0;
        int cnt = 0;
        for (int ix = -1; ix <= 1; ix++) {
            for (int iy = -1; iy <= 1; iy++) {
                int x = j + ix;
                int y = i + iy;
                if (x < 0 or y < 0 or x >= cols or y >= rows) continue;
                sum += M[y][x];
                cnt++;
            }
        }
        return (int)floor(sum * 1.0 / cnt);
    }
};
