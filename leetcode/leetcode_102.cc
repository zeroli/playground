/*
102. Binary Tree Level Order Traversal
https://leetcode.com/problems/binary-tree-level-order-traversal/

Given a binary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).

For example:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
return its level order traversal as:
[
  [3],
  [9,20],
  [15,7]
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
public:
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
    // iterative using queue
    vector<vector<int>> levelOrder1(TreeNode* root) {
        vector<vector<int>> res;
        if (not root) return res;
        queue<TreeNode*> q;
        q.push(root);
        q.push(NULL);
        res.push_back(vector<int>());
        while (!q.empty()) {
            TreeNode* n = q.front();
            q.pop();
            if (n) {
                res.back().push_back(n->val);
                if (n->left) q.push(n->left);
                if (n->right) q.push(n->right);
            } else { // this level ends
                if (!q.empty()) {
                    q.push(NULL);
                    res.push_back(vector<int>());
                }
            }
        }
        return res;
    }
};
