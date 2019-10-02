/*
572. Subtree of Another Tree
https://leetcode.com/problems/subtree-of-another-tree/

Given two non-empty binary trees s and t, check whether tree t has exactly the same structure and node values with a subtree of s. A subtree of s is a tree consists of a node in s and all of this node's descendants. The tree s could also be considered as a subtree of itself.

Example 1:
Given tree s:

     3
    / \
   4   5
  / \
 1   2
Given tree t:
   4
  / \
 1   2
Return true, because t has the same structure and node values with a subtree of s.
Example 2:
Given tree s:

     3
    / \
   4   5
  / \
 1   2
    /
   0
Given tree t:
   4
  / \
 1   2
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
    bool isSubtree(TreeNode* s, TreeNode* t) {
        if (not s and not t) return true;
        if (not s or not t) return false;

        if (s->val == t->val) {
            if (isSameTree(s, t)) return true;
        }
        if (isSubtree(s->left, t)) return true;
        if (isSubtree(s->right, t)) return true;
        return false;
    }
private:
    bool isSameTree(TreeNode* s, TreeNode* t) {
        if (not s and not t) return true;
        if (not s or not t) return false;
        return (s->val == t->val) and isSameTree(s->left, t->left) and isSameTree(s->right, t->right);
    }
};
