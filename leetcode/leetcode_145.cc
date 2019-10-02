/*
145. Binary Tree Postorder Traversal
Hard
https://leetcode.com/problems/binary-tree-postorder-traversal/

Given a binary tree, return the postorder traversal of its nodes' values.

Example:

Input: [1,null,2,3]
   1
    \
     2
    /
   3

Output: [3,2,1]
Follow up: Recursive solution is trivial, could you do it iteratively?
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
    vector<int> postorderTraversal(TreeNode* root) {
        if (not root) return vector<int>();

        stack<TreeNode*> stk1;
        stack<TreeNode*> stk2;
        TreeNode* p = root;
        stk1.push(p);
        while (!stk1.empty()) {
            p = stk1.top();
            stk1.pop();
            stk2.push(p);
            if (p->left)
                stk1.push(p->left);
            if (p->right)
                stk1.push(p->right);
        }
        vector<int> res;
        res.reserve(stk2.size());
        while (!stk2.empty()) {
            res.push_back(stk2.top()->val);
            stk2.pop();
        }
        return res;
    }
    // another solution, using double push
    vector<int> postorderTraversal(TreeNode *root) {
        vector<int> ret;
        if(!root) return ret;
        stack<TreeNode*> st;
        st.push(root);
        st.push(root);
        TreeNode *cur;
        while(!st.empty()){
            cur = st.top();
            st.pop();
            if(!st.empty()&&st.top() == cur){
                if(cur->right) {
                    st.push(cur->right);
                    st.push(cur->right);
                }
                if(cur->left){
                    st.push(cur->left);
                    st.push(cur->left);
                }
            }
            else
                ret.push_back(cur->val);
        }
        return ret;
    }
};
