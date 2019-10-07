/*
1008. Construct Binary Search Tree from Preorder Traversal
Medium
https://leetcode.com/problems/construct-binary-search-tree-from-preorder-traversal/

Return the root node of a binary search tree that matches the given preorder traversal.

(Recall that a binary search tree is a binary tree where for every node, any descendant of node.left has a value < node.val, and any descendant of node.right has a value > node.val.  Also recall that a preorder traversal displays the value of the node first, then traverses node.left, then traverses node.right.)



Example 1:

Input: [8,5,1,7,10,12]
Output: [8,5,10,1,7,null,12]



Note:

1 <= preorder.length <= 100
The values of preorder are distinct.
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
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        return bstFromPreorder(preorder, 0, (int)preorder.size()-1);
    }

private:
    TreeNode* bstFromPreorder(vector<int>& preorder, int l, int r) {
        if (l > r) return 0;
        TreeNode* root = new TreeNode(preorder[l]);
        int right = findRightRoot(preorder, l+1, r, preorder[l]);
        root->left = bstFromPreorder(preorder, l+1, right-1);
        root->right = bstFromPreorder(preorder, right, r);
        return root;
    }
    // find the first value which is bigger than num, in range [l, r]
    int findRightRoot(vector<int>& preorder, int l, int r, int num) {
        while (l <= r) {
            if (preorder[l] > num) {
                return l;
            }
            l++;
        }
        return l;
    }
};
