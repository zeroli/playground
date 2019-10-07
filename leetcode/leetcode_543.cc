/*
543. Diameter of Binary Tree
Easy
https://leetcode.com/problems/diameter-of-binary-tree/

Given a binary tree, you need to compute the length of the diameter of the tree. The diameter of a binary tree is the length of the longest path between any two nodes in a tree. This path may or may not pass through the root.

Example:
Given a binary tree
          1
         / \
        2   3
       / \
      4   5
Return 3, which is the length of the path [4,2,1,3] or [5,2,1,3].

Note: The length of path between two nodes is represented by the number of edges between them.
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
    int diameterOfBinaryTree(TreeNode* root) {
        // post-order traversal
        int diameter = 0;
        postorder(root, diameter);
        return diameter;
    }
    int postorder(TreeNode* root, int& diameter) {
        if (not root) return 0;
        if (not root->left and not root->right) return 0;
        int maxleft = postorder(root->left, diameter);
        int maxright = postorder(root->right, diameter);
        diameter = max(diameter, maxleft+maxright+(root->left?1:0)+(root->right?1:0));
        return 1 + max(maxleft, maxright);
    }
};
