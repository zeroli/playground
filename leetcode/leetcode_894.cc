/*
894. All Possible Full Binary Trees
Medium
https://leetcode.com/problems/all-possible-full-binary-trees/

A full binary tree is a binary tree where each node has exactly 0 or 2 children.

Return a list of all possible full binary trees with N nodes.  Each element of the answer is the root node of one possible tree.

Each node of each tree in the answer must have node.val = 0.

You may return the final list of trees in any order.



Example 1:

Input: 7
Output: [[0,0,0,null,null,0,0,null,null,0,0],[0,0,0,null,null,0,0,0,0],[0,0,0,0,0,0,0],[0,0,0,0,0,null,null,null,null,0,0],[0,0,0,0,0,null,null,0,0]]
Explanation:



Note:

1 <= N <= 20
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
    vector<TreeNode*> allPossibleFBT(int N) {
        vector<TreeNode*> res;
        if ((N & 1) == 0) return res; // even, no return
        if (N == 1) {
            res.push_back(new TreeNode(0));
            return res;
        }
        for (int i = 0; i < N; i++) {
            vector<TreeNode*> lefts = allPossibleFBT(i);
            vector<TreeNode*> rights = allPossibleFBT(N-i-1);
            for (int l = 0; l < lefts.size(); l++) {
                for (int r = 0; r < rights.size(); r++) {
                    TreeNode* root = new TreeNode(0);
                    root->left = lefts[l];
                    root->right = rights[r];
                    res.push_back(root);
                }
            }
        }
        return res;
    }
};
