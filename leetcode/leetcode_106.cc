/*
106. Construct Binary Tree from Inorder and Postorder Traversal
Medium
https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/

Given inorder and postorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree.

For example, given

inorder = [9,3,15,20,7]
postorder = [9,15,7,20,3]
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
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if (inorder.empty() or postorder.empty()) return 0;
        if (inorder.size() != postorder.size()) return 0;

        return buildTree(inorder, 0, (int)inorder.size()-1, postorder, 0, (int)postorder.size()-1);
    }
private:
    int findRootInInorder(vector<int>& inorder, int l, int r, int root) {
        for (int i = l; i <= r; i++) {
            if (inorder[i] == root) { return i; }
        }
        return -1;
    }
    TreeNode* buildTree(vector<int>& inorder, int il, int ir, vector<int>& postorder, int pl, int pr) {
        if (il > ir) return 0;
        TreeNode* root = new TreeNode(postorder[pr]);

        int iroot = findRootInInorder(inorder, il, ir, postorder[pr]);

        int s = il, e = iroot - 1;
        root->left = buildTree(inorder, s, e, postorder, pl, pl+e-s);

        s = iroot+1, e = ir;
        root->right = buildTree(inorder, s, e, postorder, pr-1-(e-s), pr-1);

        return root;
    }
};
