/*
559. Maximum Depth of N-ary Tree
Easy
https://leetcode.com/problems/maximum-depth-of-n-ary-tree/

Given a n-ary tree, find its maximum depth.

The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.

For example, given a 3-ary tree:






We should return its max depth, which is 3.



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
    int maxDepth(Node* root) {
        if (not root) return 0;
        int maxdepth = 0;
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            maxdepth++;
            int size = q.size();
            while (size--) {
                Node* p = q.front();
                q.pop();
                for (int i = 0; i < (int)p->children.size(); i++) {
                    q.push(p->children[i]);
                }
            }
        }
        return maxdepth;
    }
    // recursive solution
    int maxDepth1(Node* root) {
        if (not root) return 0;
        int maxdepth = 0;
        for (int i = 0; i < (int)root->children.size(); i++) {
            maxdepth = max(maxdepth, maxDepth(root->children[i]));
        }
        return maxdepth + 1;
    }
};
