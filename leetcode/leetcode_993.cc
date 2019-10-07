/*
993. Cousins in Binary Tree
Easy
https://leetcode.com/problems/cousins-in-binary-tree/

In a binary tree, the root node is at depth 0, and children of each depth k node are at depth k+1.

Two nodes of a binary tree are cousins if they have the same depth, but have different parents.

We are given the root of a binary tree with unique values, and the values x and y of two different nodes in the tree.

Return true if and only if the nodes corresponding to the values x and y are cousins.



Example 1:


Input: root = [1,2,3,4], x = 4, y = 3
Output: false
Example 2:


Input: root = [1,2,3,null,4,null,5], x = 5, y = 4
Output: true
Example 3:



Input: root = [1,2,3,null,4], x = 2, y = 3
Output: false


Note:

The number of nodes in the tree will be between 2 and 100.
Each node has a unique integer value from 1 to 100.
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
    bool isCousins(TreeNode* root, int x, int y) {
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            int sz = (int)q.size();
            int ix = -1, iy = -1;
            for (int i = 0; i < sz; i++) {
                TreeNode* p = q.front();
                q.pop();
                if (not p) {
                    q.push(NULL);
                    q.push(NULL);
                    continue;
                }
                if (p->val == x) { ix = i; }
                if (p->val == y) { iy = i; }
                q.push(p->left);
                q.push(p->right);
            }
            if (ix < 0 and iy < 0) continue; // not found at this level
            else {
                if (ix >= 0 and iy >= 0) { // found both at this level
                    return (ix - iy >= 2 or iy - ix >= 2);
                }
                if (ix >= 0 or iy >= 0) return false; // found only one at this level
            }
        }
        return false;
    }
    bool isCousins1(TreeNode* root, int x, int y) {
        TreeNode* xparent = 0;
        int xdepth = getDepth(root, x, 0, &xparent);
        TreeNode* yparent = 0;
        int ydepth = getDepth(root, y, 0, &yparent);
        return (xdepth == ydepth and xparent != yparent);
    }
private:
    int getDepth(TreeNode* root, int x, int depth, TreeNode** parent) {
        if (not root) return -1;
        if (root->val == x) {
            return depth;
        }

        int ret = getDepth(root->left, x, depth+1, parent);
        if (ret >= 0) {
            if (not *parent) *parent = root;
            return ret;
        }

        ret = getDepth(root->right, x, depth+1, parent);
        if (ret >= 0) {
            if (not *parent) *parent = root;
            return ret;
        }
        return -1;
    }
};
