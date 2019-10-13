/*
173. Binary Search Tree Iterator
Medium
https://leetcode.com/problems/binary-search-tree-iterator/

Implement an iterator over a binary search tree (BST). Your iterator will be initialized with the root node of a BST.

Calling next() will return the next smallest number in the BST.



Example:



BSTIterator iterator = new BSTIterator(root);
iterator.next();    // return 3
iterator.next();    // return 7
iterator.hasNext(); // return true
iterator.next();    // return 9
iterator.hasNext(); // return true
iterator.next();    // return 15
iterator.hasNext(); // return true
iterator.next();    // return 20
iterator.hasNext(); // return false


Note:

next() and hasNext() should run in average O(1) time and uses O(h) memory, where h is the height of the tree.
You may assume that next() call will always be valid, that is, there will be at least a next smallest number in the BST when next() is called.
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
class BSTIterator {
public:
    BSTIterator(TreeNode* root) {
        traveseLeft(root);
    }

    /** @return the next smallest number */
    // average runtime is O(1), space is O(h)
    // some times, it will take O(n), for next() call next time
    int next() {
        TreeNode* ret =  d_stk.top();
        d_stk.pop();
        if (ret->right) {
            traveseLeft(ret->right);
        }
        return ret->val;
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return (!d_stk.empty());
    }
private:
    void traveseLeft(TreeNode* root) {
        while (root) {
            d_stk.push(root);
            root = root->left;
        }
    }
private:
    stack<TreeNode*> d_stk;
};

class BSTIterator1 {
public:
    BSTIterator1(TreeNode* root) {
        inorderReverse(root);
    }

    /** @return the next smallest number */
    int next() {
        TreeNode* ret =  d_stk.top();
        d_stk.pop();
        return ret->val;
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return (!d_stk.empty());
    }
private:
    void inorderReverse(TreeNode* root) {
        if (not root) return;
        inorderReverse(root->right);
        d_stk.push(root);
        inorderReverse(root->left);
    }
private:
    stack<TreeNode*> d_stk;
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
