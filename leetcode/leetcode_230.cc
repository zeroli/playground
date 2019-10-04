/*
230. Kth Smallest Element in a BST
Medium
https://leetcode.com/problems/kth-smallest-element-in-a-bst/

Given a binary search tree, write a function kthSmallest to find the kth smallest element in it.

Note:
You may assume k is always valid, 1 ≤ k ≤ BST's total elements.

Example 1:

Input: root = [3,1,4,null,2], k = 1
   3
  / \
 1   4
  \
   2
Output: 1
Example 2:

Input: root = [5,3,6,2,4,null,null,1], k = 3
       5
      / \
     3   6
    / \
   2   4
  /
 1
Output: 3
Follow up:
What if the BST is modified (insert/delete operations) often and you need to find the kth smallest frequently? How would you optimize the kthSmallest routine?
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
    int kthSmallest(TreeNode* root, int k) {
        // inorder travesal
        stack<TreeNode*> stk;
        TreeNode* p = root;
        while (p or !stk.empty()) {
            if (p) {
                stk.push(p);
                p = p->left;
            } else {
                p = stk.top();
                stk.pop();
                if (--k == 0) {
                    return p->val;
                }
                p = p->right;
            }
        }
        return -1;
    }
    int kthSmallest2(TreeNode* root, int k) {
        return _kthSmallest(root, k)->val;
    }
private:
    int _kthSmallest(TreeNode* root, int& k) {
        if (root) {
            int found = _kthSmallest(root->left, k);
            if (k == 0) return found;
            if (--k == 0) {
                return root;
            }
            found = _kthSmallest(root->right, k);
            if (k == 0) return found;
        }
        return -1;
    }
private:
    int kthSmallest1(TreeNode* root, int k) {
        while (root) {
            int p = countNodes(root->left);
            if (p+1 == k) {
                return root->val;
            } else if (k <= p+1) {
                root = root->left;
            } else { // k > p+1
                root = root->right;
                k -= (p+1);
            }
        }
        return -1;
    }
private:
    int countNodes(TreeNode* root) {
        if (not root) return 0;
        return 1 + countNodes(root->left) + countNodes(root->right);
    }
};
