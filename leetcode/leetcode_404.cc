/*
404. Sum of Left Leaves
Easy
https://leetcode.com/problems/sum-of-left-leaves/

Find the sum of all left leaves in a given binary tree.

Example:

    3
   / \
  9  20
    /  \
   15   7

There are two left leaves in the binary tree, with values 9 and 15 respectively. Return 24.
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
    int sumOfLeftLeaves(TreeNode* root) {
        int sum = 0;
        preorder(root, sum, false);
        return sum;
    }
    void preorder(TreeNode* root, int& sum, bool left) {
        if (not root) return;
        if (not root->left and not root->right) {
            if (left) sum += root->val;
            return;
        }
        preorder(root->left, sum, true);
        preorder(root->right, sum, false);
    }
};
