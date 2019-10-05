/*
965. Univalued Binary Tree
Easy
https://leetcode.com/problems/univalued-binary-tree/

A binary tree is univalued if every node in the tree has the same value.

Return true if and only if the given tree is univalued.



Example 1:


Input: [1,1,1,1,1,null,1]
Output: true
Example 2:


Input: [2,2,2,5,2]
Output: false


Note:

The number of nodes in the given tree will be in the range [1, 100].
Each node's value will be an integer in the range [0, 99].
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
    bool isUnivalTree(TreeNode* root) {
        // inorder traversal to see any next value is different fromt previous one
        TreeNode* prev = 0;
        return inorder(root, prev);
    }
private:
    bool inorder(TreeNode* root, TreeNode*& prev) {
        if (not root) return true;
        if (not inorder(root->left, prev))
            return false;
        if (prev and prev->val != root->val)
            return false;
        prev = root;
        if (not inorder(root->right, prev))
            return false;
        return true;
    }
};
