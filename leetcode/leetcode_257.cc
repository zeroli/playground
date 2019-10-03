/*
257. Binary Tree Paths
Easy
https://leetcode.com/problems/binary-tree-paths/

Given a binary tree, return all root-to-leaf paths.

Note: A leaf is a node with no children.

Example:

Input:

   1
 /   \
2     3
 \
  5

Output: ["1->2->5", "1->3"]

Explanation: All root-to-leaf paths are: 1->2->5, 1->3
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
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> res;
        if (not root) return res;
        vector<int> path;
        path.push_back(root->val);
        binaryTreePaths(root, res, path);
        return res;
    }
private:
    void binaryTreePaths(TreeNode* root, vector<string>& res, vector<int>& path) {
        if (not root) return;
        if (not root->left and not root->right) {
            ostringstream outstr;
            outstr << path[0];
            for (int i = 1; i < (int)path.size(); i++) {
                outstr << "->" << path[i];
            }
            res.push_back(outstr.str());
            return;
        }
        if (root->left) {
            path.push_back(root->left->val);
            binaryTreePaths(root->left, res, path);
            path.pop_back();
        }
        if (root->right) {
            path.push_back(root->right->val);
            binaryTreePaths(root->right, res, path);
            path.pop_back();
        }
    }
};
