/*
114. Flatten Binary Tree to Linked List
Medium
https://leetcode.com/problems/flatten-binary-tree-to-linked-list/

Given a binary tree, flatten it to a linked list in-place.

For example, given the following tree:

    1
   / \
  2   5
 / \   \
3   4   6
The flattened tree should look like:

1
 \
  2
   \
    3
     \
      4
       \
        5
         \
          6
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
    // iterative
    void flatten(TreeNode* root) {
        stack<TreeNode*> st;
        TreeNode* p = root;
        while (p || !st.empty()) {
            if (p) {
                if (p->right)
                    st.push(p->right);

                p->right = p->left;
                p->left = NULL;
                // below code is key, we need connect this one with its right
                if (not p->right && !st.empty()) {
                    p->right = st.top();
                    st.pop();
                }
                p = p->right;
            } else {
                p = st.top();
                st.pop();
            }
        }
    }
    // recursive
    void flatten2(TreeNode* root) {
        flatten(root, NULL);
    }
private:
    TreeNode* flatten(TreeNode* root, TreeNode* prev)
    {
        if (not root) return prev;

        prev = flatten(root->right, prev);
        prev = flatten(root->left, prev);
        root->right = prev;
        root->left = 0;
        prev = root;
        return prev;
    }
private:
    void flatten1(TreeNode* root) {
        // preorder traversal
        TreeNode* head = root, *tail = root;
        flatten(root, &head, &tail);
    }
private:
    void flatten(TreeNode* root, TreeNode** head, TreeNode** tail) {
        if (not root) return;
        TreeNode* left = root->left;
        TreeNode* right = root->right;
        if (not left and not right) return;

        root->left = 0;
        TreeNode* left_head = left, *left_tail = left;
        flatten(left, &left_head, &left_tail);
        root->right = left_head;
        if (not left_tail) left_tail = root;

        TreeNode* right_head = right, *right_tail = right;
        flatten(right, &right_head, &right_tail);
        left_tail->right = right_head;
        if (not right_tail) right_tail = left_tail;

        *head = root;
        *tail = right_tail;
    }
};
