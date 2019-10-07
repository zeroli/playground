/*
671. Second Minimum Node In a Binary Tree
Easy
https://leetcode.com/problems/second-minimum-node-in-a-binary-tree/

Given a non-empty special binary tree consisting of nodes with the non-negative value, where each node in this tree has exactly two or zero sub-node. If the node has two sub-nodes, then this node's value is the smaller value among its two sub-nodes. More formally, the property root.val = min(root.left.val, root.right.val) always holds.

Given such a binary tree, you need to output the second minimum value in the set made of all the nodes' value in the whole tree.

If no such second minimum value exists, output -1 instead.

Example 1:

Input:
    2
   / \
  2   5
     / \
    5   7

Output: 5
Explanation: The smallest value is 2, the second smallest value is 5.


Example 2:

Input:
    2
   / \
  2   2

Output: -1
Explanation: The smallest value is 2, but there isn't any second smallest value.
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
    int findSecondMinimumValue(TreeNode* root) {
        if (not root) return -1;
        if (not root->left and not root->right) return -1;

        int left = root->left->val;
        if (root->left->val == root->val) {
            left = findSecondMinimumValue(root->left);
        }
        int right = root->right->val;
        if (root->right->val == root->val) {
            right = findSecondMinimumValue(root->right);
        }
        if (left != -1 and right != -1) {
            return min(left, right);
        }
        if (left != -1) {
            return left;
        }
        if (right != -1) {
            return right;
        }
        return -1;
    }
};
