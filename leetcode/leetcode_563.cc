/*
563. Binary Tree Tilt
Easy
https://leetcode.com/problems/binary-tree-tilt/

Given a binary tree, return the tilt of the whole tree.

The tilt of a tree node is defined as the absolute difference between the sum of all left subtree node values and the sum of all right subtree node values. Null node has tilt 0.

The tilt of the whole tree is defined as the sum of all nodes' tilt.

Example:
Input:
         1
       /   \
      2     3
Output: 1
Explanation:
Tilt of node 2 : 0
Tilt of node 3 : 0
Tilt of node 1 : |2-3| = 1
Tilt of binary tree : 0 + 0 + 1 = 1
Note:

The sum of node values in any subtree won't exceed the range of 32-bit integer.
All the tilt values won't exceed the range of 32-bit integer.
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
    int findTilt(TreeNode* root) {
        int tilt = 0;
        traverse(root, tilt);
    }
    // return sum
    int traverse(TreeNode* root, int& tilt) {
        if (not root) return 0;
        int left = traverse(root->left, tilt);
        int right = traverse(root->right, tilt);
        tilt += abs(left-right);
        return left+right+root->val;
    }
    int findTilt1(TreeNode* root) {
        int sum = 0;
        return findTilt(root, sum);
    }
    // return tilt
    int findTilt(TreeNode* root, int& sum) {
        if (not root) return 0;
        sum += root->val;
        if (not root->left and not root->right) {
            return 0;
        }
        int left_sum = 0, right_sum = 0;
        int left_tilt = findTilt(root->left, left_sum);
        int right_tilt = findTilt(root->right, right_sum);
        int tilt = abs(left_sum - right_sum);
        sum += left_sum + right_sum;
        return left_tilt + right_tilt + tilt;
    }
};
