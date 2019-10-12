/*
515. Find Largest Value in Each Tree Row
Medium
https://leetcode.com/problems/find-largest-value-in-each-tree-row/

You need to find the largest value in each row of a binary tree.

Example:
Input:

          1
         / \
        3   2
       / \   \
      5   3   9

Output: [1, 3, 9]
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
    vector<int> res;
    vector<int> largestValues(TreeNode* root) {
        if (not root) return res;

        levelTraverse(root, 0);
    }
    void levelTraverse(TreeNode* root, int depth) {
        if (not root) return;
        if (depth >= res.size()) {
            res.push_back(root->val);
        } else {
            if (res[depth] < root->val) {
                res[depth] = root->val;
            }
        }
        levelTraverse(root->left, depth+1);
        levelTraverse(root->right, depth+1);
    }
    vector<int> largestValues1(TreeNode* root) {
        vector<int> res;
        if (not root) return res;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            int sz = (int)q.size();
            int maxval = INT_MIN;
            for (int i = 0; i < sz; i++) {
                TreeNode* p = q.front();
                maxval = max(p->val, maxval);
                q.pop();
                if (p->left) q.push(p->left);
                if (p->right) q.push(p->right);
            }
            res.push_back(maxval);
        }
        return res;
    }
};
