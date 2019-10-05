/*
897. Increasing Order Search Tree
Easy
https://leetcode.com/problems/increasing-order-search-tree/

Given a binary search tree, rearrange the tree in in-order so that the leftmost node in the tree is now the root of the tree, and every node has no left child and only 1 right child.

Example 1:
Input: [5,3,6,2,4,null,8,1,null,null,null,7,9]

       5
      / \
    3    6
   / \    \
  2   4    8
 /        / \
1        7   9

Output: [1,null,2,null,3,null,4,null,5,null,6,null,7,null,8,null,9]

 1
  \
   2
    \
     3
      \
       4
        \
         5
          \
           6
            \
             7
              \
               8
                \
                 9
Note:

The number of nodes in the given tree will be between 1 and 100.
Each node will have a unique integer value from 0 to 1000.
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
    TreeNode* increasingBST(TreeNode* root) {
        return inorderRight(root, 0);
    }
    // it will output [1,null,2,null,3,null,4,null,5,null,6,null,7,null,8,null,9]
    TreeNode* inorderRight(TreeNode* root, TreeNode* next) {
        if (not root) return next;
        TreeNode* res = inorderRight(root->left, root);
        root->left = 0;
        root->right = inorderRight(root->right, next);
        return res;
    }
    // it will output [9,8,null,7,null,6,null,5,null,4,null,3,null,2,null,1]
    TreeNode* inorderLeft(TreeNode* root, TreeNode* prev) {
        if (not root) return prev;
        TreeNode* res = inorderLeft(root->right, root);
        root->right = 0;
        root->left = inorderLeft(root->left, prev);
        return res;
    }
};
