/*
113. Path Sum II
Medium
https://leetcode.com/problems/path-sum-ii/

Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.

Note: A leaf is a node with no children.

Example:

Given the below binary tree and sum = 22,

      5
     / \
    4   8
   /   / \
  11  13  4
 /  \    / \
7    2  5   1
Return:

[
   [5,4,11,2],
   [5,8,4,5]
]
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
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int>> res;
        if (not root) return res;
        vector<int> path;
        path.push_back(root->val);
        pathSum(root, sum, res, path);
        return res;
    }
private:
    void pathSum(TreeNode* root, int sum, vector<vector<int>>& res, vector<int>& path) {
        if (not root) return;

        if (not root->left and not root->right and sum==root->val)
        {
            res.push_back(path);
            return;
        }
        if (root->left) {
            path.push_back(root->left->val);
            pathSum(root->left, sum-root->val, res, path);
            path.pop_back();
        }
        if (root->right) {
            path.push_back(root->right->val);
            pathSum(root->right, sum-root->val, res, path);
            path.pop_back();
        }
    }
};
