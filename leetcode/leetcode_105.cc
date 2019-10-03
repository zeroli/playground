/*
105. Construct Binary Tree from Preorder and Inorder Traversal
Medium
https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/

Given preorder and inorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree.

For example, given

preorder = [3,9,20,15,7]
inorder = [9,3,15,20,7]
Return the following binary tree:

    3
   / \
  9  20
    /  \
   15   7
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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if (preorder.empty() or inorder.empty()) return 0;
        if (preorder.size() != inorder.size()) return 0;
        int pl = 0;
        return buildTree(preorder, pl, inorder, 0, (int)inorder.size()-1);
    }
private:
    int findRootInInorder(vector<int>& inorder, int l, int r, int root) {
        for (int i = l; i <= r; i++) {
            if (inorder[i] == root) { return i; }
        }
        return -1;
    }
    TreeNode* buildTree(vector<int>& preorder, int& pl, vector<int>& inorder, int il, int ir) {
        if (pl >= (int)preorder.size()) return 0;
        TreeNode* root = new TreeNode(preorder[pl]);

        int iroot = findRootInInorder(inorder, il, ir, preorder[pl]);
        int il1 = il, ir1 = iroot - 1;
        if (il1 <= ir1)
            root->left = buildTree(preorder, ++pl, inorder, il1, ir1);

        il1 = iroot + 1, ir1 = ir;
        if (il1 <= ir1)
            root->right = buildTree(preorder, ++pl, inorder, il1, ir1);
        return root;
    }
};
