/*
513. Find Bottom Left Tree Value
Medium
https://leetcode.com/problems/find-bottom-left-tree-value/

Given a binary tree, find the leftmost value in the last row of the tree.

Example 1:
Input:

    2
   / \
  1   3

Output:
1
Example 2:
Input:

        1
       / \
      2   3
     /   / \
    4   5   6
       /
      7

Output:
7
Note: You may assume the tree (i.e., the given root node) is not NULL.
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
    int blv = -1;
    int findBottomLeftValue(TreeNode* root) {
        int maxdepth = -1; // initialize to -1 to handle [0] single node tree
        findBottomLeftValue(root, 0, maxdepth);
        return blv;
    }
    void findBottomLeftValue(TreeNode* root, int depth, int& maxdepth) {
        if (not root) return;
        if (not root->left and not root->right) {
            if (depth > maxdepth) { // first maxdepth will be firstmost node
                blv = root->val;
                maxdepth = depth;
            }
            return;
        }
        findBottomLeftValue(root->left, depth+1, maxdepth);
        findBottomLeftValue(root->right, depth+1, maxdepth);
    }
};
