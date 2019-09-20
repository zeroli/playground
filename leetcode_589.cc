/*
589. N-ary Tree Preorder Traversal
Given an n-ary tree, return the preorder traversal of its nodes' values.

For example, given a 3-ary tree:
     1
   / | \
 3   2  4
/ \
5 6
Return its preorder traversal as: [1,3,5,6,2,4].
Note:

Recursive solution is trivial, could you do it iteratively?
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
    vector<int> preorder(Node* root) {
        vector<int> v;
        _preorder(root, v);
        return v;
    }
private:
    void _preorder(Node* root, vector<int>& v) {
        if (root == NULL) return;
        v.push_back(root->val);
        for (size_t i = 0; i < root->children.size(); i++) {
            _preorder(root->children[i], v);
        }
    }
};
