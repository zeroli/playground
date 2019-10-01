/*
107. Binary Tree Level Order Traversal II
https://leetcode.com/problems/binary-tree-level-order-traversal-ii/

Given a binary tree, return the bottom-up level order traversal of its nodes' values. (ie, from left to right, level by level from leaf to root).

For example:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
return its bottom-up level order traversal as:
[
  [15,7],
  [9,20],
  [3]
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
    // this solution ran faster than version 1
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        auto res = levelOrder(root);
        reverse(res.begin(), res.end());
        return res;
    }
    vector<vector<int>> levelOrderBottom1(TreeNode* root) {
        vector<vector<int>> res;
        _levelOrderBottom(res, root, 0);
        return res;
    }
private:
    void _levelOrderBottom(vector<vector<int>>& res, TreeNode* root, int level) {
        if (not root) return;

        if (level >= res.size())
            res.insert(res.begin(), vector<int>{});
        _levelOrderBottom(res, root->left, level+1);
        _levelOrderBottom(res, root->right, level+1);
        res[res.size()-level-1].push_back(root->val);
    }
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        _levelOrder(res, root, 0);
        return res;
    }
private:
    void _levelOrder(vector<vector<int>>& res, TreeNode* root, int level) {
        if (not root) return;

        if (level >= res.size())
            res.push_back({});
        res[level].push_back(root->val);
        _levelOrder(res, root->left, level+1);
        _levelOrder(res, root->right, level+1);
    }
};
