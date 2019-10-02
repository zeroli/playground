/*
138. Copy List with Random Pointer
https://leetcode.com/problems/copy-list-with-random-pointer/

A linked list is given such that each node contains an additional random pointer which could point to any node in the list or null.

Return a deep copy of the list.



Example 1:



Input:
{"$id":"1","next":{"$id":"2","next":null,"random":{"$ref":"2"},"val":2},"random":{"$ref":"2"},"val":1}

Explanation:
Node 1's value is 1, both of its next and random pointer points to Node 2.
Node 2's value is 2, its next pointer points to null and its random pointer points to itself.
*/
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node() {}

    Node(int _val, Node* _next, Node* _random) {
        val = _val;
        next = _next;
        random = _random;
    }
};
*/
class Solution {
public:
    std::map<Node*, Node*> m;
    Node* copyRandomList(Node* head) {
        if(not head )
            return head;
        if(m.find(head) != m.end())
            return m[head];
        Node* copy_node = new Node();
        m[head] = copy_node;
        copy_node->val = head->val;
        copy_node->next = copyRandomList(head->next);
        copy_node->random = copyRandomList(head->random);
        return copy_node;
    }

    // solution doesnot use extra space O(n)
    Node* copyRandomList(Node* head) {
        copyNodes(head);
        setupRandomLink(head);
        return splitNewList(head);
    }
private:
    void copyNodes(Node* head) {
        Node* p = head;
        while (p) {
            Node* np = new Node(p->val);
            // insert np after this p
            np->next = p->next;
            p->next = np;
            p = np->next;
        }
    }
    void setupRandomLink(Node* head) {
        Node* p = head;
        while (p) {
            if (p->random) {
                Node* np = p->next;
                np->random = p->random->next;
            }
        }
    }
    Node* splitNewList(Node* head) {
        // copy nodes at even position
        Node* nhead = head->next;
        head->next = 0;
        Node* p = nhead->next;
        Node** ptail = &(head->next);
        Node** pntail = &(nhead->next);
        while (p) {
            *ptail = p;
            ptail = &(p->next);
            *pntail = p->next;
            p = p->next;
            pntail = &(p->next);
            p = p->next;
        }
        return nhead;
    }
};
