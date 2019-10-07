/*
653. Two Sum IV - Input is a BST
Easy
https://leetcode.com/problems/two-sum-iv-input-is-a-bst/

Given a Binary Search Tree and a target number, return true if there exist two elements in the BST such that their sum is equal to the given target.

Example 1:

Input:
    5
   / \
  3   6
 / \   \
2   4   7

Target = 9

Output: True


Example 2:

Input:
    5
   / \
  3   6
 / \   \
2   4   7

Target = 28

Output: False
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
    // use another extra hash table to store all nodes
    set<int> s;
    bool findTarget(TreeNode* root, int k) {
        if (!root) return false;
        if (s.count(k - root->val)) return true;
        s.insert(root->val);
        return findTarget(root->left, k) || findTarget(root->right, k);
    }
    bool findTarget(TreeNode* root, int k) {
        stack<TreeNode*> s1, s2;
        TreeNode* p1 = root;
        TreeNode* p2 = root;

        p1 = dfsLeft(p1, s1);
        p2 = dfsRight(p2, s2);
        while (p1 and p2 and p1 != p2) {
            int sum = p1->val + p2->val;
            if (sum == k) { return true; }
            if (sum > k) { // decrease right
                p2 = dfsRight(p2->left, s2);
            } else { // increase left
                p1 = dfsLeft(p1->right, s1);
            }
        }
        return false;
    }

    TreeNode* dfsLeft(TreeNode* p1, stack<TreeNode*>& s1) {
        while (p1 or !s1.empty()) {
            if (p1) {
                s1.push(p1);
                p1 = p1->left;
            } else {
                p1 = s1.top();
                s1.pop();
                return p1;
            }
        }
        return 0;
    }
    TreeNode* dfsRight(TreeNode* p2, stack<TreeNode*>& s2) {
        while (p2 or !s2.empty()) {
            if (p2) {
                s2.push(p2);
                p2 = p2->right;
            } else {
                p2 = s2.top();
                s2.pop();
                return p2;
            }
        }
        return 0;
    }
};
