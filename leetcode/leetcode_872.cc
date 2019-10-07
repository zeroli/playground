/*
872. Leaf-Similar Trees
Easy
https://leetcode.com/problems/leaf-similar-trees/

Consider all the leaves of a binary tree.  From left to right order, the values of those leaves form a leaf value sequence.



For example, in the given tree above, the leaf value sequence is (6, 7, 4, 9, 8).

Two binary trees are considered leaf-similar if their leaf value sequence is the same.

Return true if and only if the two given trees with head nodes root1 and root2 are leaf-similar.



Note:

Both of the given trees will have between 1 and 100 nodes.
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
    bool leafSimilar(TreeNode* root1, TreeNode* root2) {
        stack<TreeNode*> s1, s2;
        s1.push(root1);
        s2.push(root2);
        while (!s1.empty() and !s2.empty()) {
            if (dfs(s1) != dfs(s2)) return false;
        }
        return s1.empty() and s2.empty();
    }
    int dfs(stack<TreeNode*>& s) {
        while (!s.empty()) {
            TreeNode* p = s.top();
            s.pop();
            if (p->right) s.push(p->right);
            if (p->left) s.push(p->left);
            if (not p->left and not p->right) return p->val;
        }
        return -1;
    }

    bool leafSimilar1(TreeNode* root1, TreeNode* root2) {
        // pre-order traveral
        vector<int> treeleaf1;
        preorderLeafs(root1, treeleaf1);
        vector<int> treeleaf2;
        preorderLeafs(root2, treeleaf2);
        return treeleaf1 == treeleaf2;
    }
private:
    void preorderLeafs(TreeNode* root, vector<int>& leafs) {
        if (not root) return;
        if (not root->left and not root->right) {
            leafs.push_back(root->val);
            return;
        }
        preorderLeafs(root->left, leafs);
        preorderLeafs(root->right, leafs);
    }
};
