/*
101. Symmetric Tree
https://leetcode.com/problems/symmetric-tree/

Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).

For example, this binary tree [1,2,2,3,4,4,3] is symmetric:

    1
   / \
  2   2
 / \ / \
3  4 4  3


But the following [1,2,2,null,3,null,3] is not:

    1
   / \
  2   2
   \   \
   3    3


Note:
Bonus points if you could solve it both recursively and iteratively.
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
    bool isSymmetric(TreeNode* root) {
        if (not root) return true;
        return isSymmetric(root->left, root->right);
    }
private:
    bool isSymmetric(TreeNode* r1, TreeNode* r2) {
        if (not r1 or not r2) return r1 == r2;
        if (r1->val != r2->val) return false;
        return isSymmetric(r1->left, r2->right) and isSymmetric(r1->right, r2->left);
    }
};

// BFS using queue iteratively
bool isSymmetric(TreeNode* root) {
    if(!root) return true;
    queue<nodepair> q;
    q.push(make_pair(root->left, root->right));
    while(!q.empty()){
        nodepair p = q.front();
        q.pop();
        if(!p.first && !p.second) continue;
        if(!p.first || !p.second) return false;
        if(p.first->val != p.second->val) return false;
        q.push(make_pair(p.first->left, p.second->right));
        q.push(make_pair(p.first->right, p.second->left));
    }
    return true;
}

// Iterative in DFS:

bool isSymmetric(TreeNode* root) {
    if(!root) return true;
    stack<TreeNode*> sl, sr;
    sl.push(root);
    sr.push(root);
    TreeNode * lp = root->left, *rp = root->right;
    while(lp || ! sl.empty() || rp || !sl.empty()){
        if((!lp && rp) || (lp && !rp)) return false;
        if(lp && rp){
            if(lp->val != rp->val) return false;
            sl.push(lp);
            sr.push(rp);
            lp = lp->left;
            rp = rp->right;
        }else{
            lp = sl.top()->right;
            rp = sr.top()->left;
            sl.pop();
            sr.pop();
        }
    }
    return true;
}
