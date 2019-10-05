/*
429. N-ary Tree Level Order Traversal
Easy
https://leetcode.com/problems/n-ary-tree-level-order-traversal/

Given an n-ary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).

For example, given a 3-ary tree:







We should return its level order traversal:

[
     [1],
     [3,2,4],
     [5,6]
]


Note:

The depth of the tree is at most 1000.
The total number of nodes is at most 5000.
*/
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/
class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
        vector<vector<int>> res;
        levelOrder(root, res, 0);
        return res;
    }
    void levelOrder(Node* root, vector<vector<int>>& res, int level) {
        if (not root) return;
        if (level >= (int)res.size()) {
            res.push_back(vector<int>());
        }
        res[level].push_back(root->val);
        for (int i = 0; i < (int)root->children.size(); i++) {
            levelOrder(root->children[i], res, level+1);
        }
    }
};
