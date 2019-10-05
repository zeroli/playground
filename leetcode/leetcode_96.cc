/*
96. Unique Binary Search Trees
Medium
https://leetcode.com/problems/unique-binary-search-trees/

Given n, how many structurally unique BST's (binary search trees) that store values 1 ... n?

Example:

Input: 3
Output: 5
Explanation:
Given n = 3, there are a total of 5 unique BST's:

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3
*/
class Solution {
public:
    int numTrees(int n) {
        std::vector<int> tbl(n+1, 0);
        tbl[0] = 1;
        int k = 1;
        while (k <= n) {
            for (int i = 0; i < k; i++) {
                tbl[k] += tbl[i] * tbl[k-i-1];
            }
            k++;
        }
        return tbl[n];
    }
};
