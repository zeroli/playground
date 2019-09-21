/*
110. Balanced Binary Tree
https://leetcode.com/problems/balanced-binary-tree/

Given a binary tree, determine if it is height-balanced.

For this problem, a height-balanced binary tree is defined as:

a binary tree in which the depth of the two subtrees of every node never differ by more than 1.

Example 1:

Given the following tree [3,9,20,null,null,15,7]:

    3
   / \
  9  20
    /  \
   15   7
Return true.

Example 2:

Given the following tree [1,2,2,3,3,null,null,4,4]:

       1
      / \
     2   2
    / \
   3   3
  / \
 4   4
Return false.
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
    bool isBalanced(TreeNode* root) {
        if (not root) return true;
        return dfsHeight(root) != -1;
    }
    bool _isBalanced(TreeNode* root) {
        if (not root) return true;
        int leftDepth = 0, rightDepth = 0;
        return isBalancedWithDepth(root, leftDepth, rightDepth);
    }
private:
    int dfsHeight(TreeNode* root) {
        if (not root) return 0;
        int leftHeight = dfsHeight(root->left);
        if (leftHeight < 0) return -1;
        int rightHeight = dfsHeight(root->right);
        if (rightHeight < 0) return -1;
        if (abs(leftHeight - rightHeight) > 1) return -1;
        else return max(leftHeight, rightHeight) + 1;
    }
private:
    bool isBalancedWithDepth(TreeNode* root, int& leftDepth, int& rightDepth) {
        if (not root) return true;
        if (not root->left) {
            leftDepth = 0;
        }
        if (not root->right) {
            rightDepth = 0;
        }
        bool leftBalanced = true;
        bool rightBalanced = true;
        if (root->left) {
            int l = 0, r = 0;
            leftBalanced = isBalancedWithDepth(root->left, l, r);
            leftDepth = max(l, r) + 1;
        }
        if (root->right) {
            int l = 0, r = 0;
            rightBalanced = isBalancedWithDepth(root->right, l, r);
            rightDepth = max(l, r) + 1;
        }
        return leftBalanced and rightBalanced and abs(leftDepth-rightDepth) <= 1;
    }
};
