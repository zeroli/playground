/*
430. Flatten a Multilevel Doubly Linked List
https://leetcode.com/problems/flatten-a-multilevel-doubly-linked-list/

You are given a doubly linked list which in addition to the next and previous pointers, it could have a child pointer, which may or may not point to a separate doubly linked list. These child lists may have one or more children of their own, and so on, to produce a multilevel data structure, as shown in the example below.

Flatten the list so that all the nodes appear in a single-level, doubly linked list. You are given the head of the first level of the list.



Example:

Input:
 1---2---3---4---5---6--NULL
         |
         7---8---9---10--NULL
             |
             11--12--NULL

Output:
1-2-3-7-8-11-12-9-10-4-5-6-NULL


Explanation for the above example:
*/
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;

    Node() {}

    Node(int _val, Node* _prev, Node* _next, Node* _child) {
        val = _val;
        prev = _prev;
        next = _next;
        child = _child;
    }
};
*/
class Solution {
public:
    // iterative solution
    Node* flatten(Node* head) {
        Node* curr = head;
        while (curr) {
            if (curr->child) {
                // find the tail of the child
                Node* childHead = curr->child;
                Node* childTail = curr->child;
                while (childTail->next)
                    childTail = childTail->next;
                // connect the current tail to the tail of the child
                childTail->next = curr->next;
                if (curr->next)
                    curr->next->prev = childTail;
                // move the head of child to next
                curr->next = childHead;
                childHead->prev = curr;
                curr->child = nullptr; // reset child
            }
            // process the next
            curr = curr->next;
        }
        return head;
    }
    // recurisve solution
    Node* flatten1(Node* head) {
        return _flatten(head).first;
    }
private:
    pair<Node*, Node*> _flatten(Node* head) {
        Node* p = head;
        Node* tail = head;
        while (p) {
            if (p->child) {
                pair<Node*, Node*> head_tail = _flatten(p->child);

                head_tail.first->prev = p;
                head_tail.second->next = p->next;
                if (p->next) {
                    p->next->prev = head_tail.second;
                }
                p->next = head_tail.first;

                p->child = 0;
                p = head_tail.second->next;
                tail = head_tail.second;
            } else {
                tail = p;
                p = p->next;
            }
        }
        return make_pair(head, tail);
    }
};
