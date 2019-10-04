/*
222. Count Complete Tree Nodes
Medium
https://leetcode.com/problems/count-complete-tree-nodes/

Given a complete binary tree, count the number of nodes.

Note:

Definition of a complete binary tree from Wikipedia:
In a complete binary tree every level, except possibly the last, is completely filled, and all nodes in the last level are as far left as possible. It can have between 1 and 2h nodes inclusive at the last level h.

Example:

Input:
    1
   / \
  2   3
 / \  /
4  5 6

Output: 6
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
    int countNodes(TreeNode* root) {

        if(!root) return 0;

        int hl=0, hr=0;

        TreeNode *l=root, *r=root;

        while(l) {hl++;l=l->left;}

        while(r) {hr++;r=r->right;}

        if(hl==hr) return pow(2,hl)-1;

        return 1+countNodes(root->left)+countNodes(root->right);

    }
    int countNodes1(TreeNode* root) {
        int maxdepth = 0;
        int leafnodes = 0;
        countNodes(root, 0, maxdepth, leafnodes);
        return (int)pow(2, maxdepth) - 1 + leafnodes;
    }
private:
    bool countNodes(TreeNode* root, int depth, int& maxdepth, int& leafnodes) {
        if (not root) return false;

        if (not root->left and not root->right) { // leaf node
            if (depth < maxdepth) { // not bottom leaf
                return false; // stop to traverse
            } else {
                maxdepth = max(depth, maxdepth);
                leafnodes++;
                return true;
            }
        }

        if (not countNodes(root->left, depth+1, maxdepth, leafnodes))
            return false;
        if (not countNodes(root->right, depth+1, maxdepth, leafnodes))
            return false;
        return true;
    }
};
