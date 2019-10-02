/*
111. Minimum Depth of Binary Tree
Given a binary tree, find its minimum depth.

The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.

Note: A leaf is a node with no children.

Example:

Given binary tree [3,9,20,null,null,15,7],

    3
   / \
  9  20
    /  \
   15   7
return its minimum depth = 2.
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
    int minDepth(TreeNode* root) {
        if (not root) return 0;
        int mindepth = INT_MAX;
        _minDepth(root, 1, mindepth);
        return mindepth;
    }
private:
    void _minDepth(TreeNode* node, int depth, int& mindepth) {
        if (not node->left and not node->right) // leaf node
            mindepth = min(depth, mindepth);
        else {
            if (node->left)
                _minDepth(node->left, depth+1, mindepth);
            if (node->right)
                _minDepth(node->right, depth+1, mindepth);
        }
    }
};
