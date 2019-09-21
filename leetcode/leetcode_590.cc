/*
590. N-ary Tree Postorder Traversal

Given an n-ary tree, return the postorder traversal of its nodes' values.

For example, given a 3-ary tree:
     1
   / | \
 3   2  4
/ \
5 6

Return its postorder traversal as: [5,6,3,2,4,1].
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

Recursive solution is trivial, could you do it iteratively?
*/
class Solution {
public:
    vector<int> postorder(Node* root) {
        vector<int> v;
        _postorder(root, v);
        return v;
    }
private:
    void _postorder(Node* root, vector<int>& v) {
        if (root == NULL) return;
        for (size_t i = 0; i < root->children.size(); i++) {
            _postorder(root->children[i], v);
        }
        v.push_back(root->val);
    }
};
