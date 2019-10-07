/*
530. Minimum Absolute Difference in BST
Easy
https://leetcode.com/problems/minimum-absolute-difference-in-bst/

Given a binary search tree with non-negative values, find the minimum absolute difference between values of any two nodes.

Example:

Input:

   1
    \
     3
    /
   2

Output:
1

Explanation:
The minimum absolute difference is 1, which is the difference between 2 and 1 (or between 2 and 3).


Note: There are at least two nodes in this BST.
*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int getMinimumDifference(TreeNode* root) {
        TreeNode* prev = 0;
        int minDiff = INT_MAX;
        inorder(root, prev, minDiff);
        return minDiff;
    }
    TreeNode* inorder(TreeNode* root, TreeNode* prev, int& minDiff) {
        if (not root) return prev;

        prev = inorder(root->left, prev, minDiff);

        if (prev) {
            minDiff = min(minDiff, root->val - prev->val);
        }
        prev = root;
        return inorder(root->right, prev, minDiff);
    }
};
