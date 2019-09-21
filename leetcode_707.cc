/*
707. Design Linked List
https://leetcode.com/problems/design-linked-list/

Design your implementation of the linked list. You can choose to use the singly linked list or the doubly linked list. A node in a singly linked list should have two attributes: val and next. val is the value of the current node, and next is a pointer/reference to the next node. If you want to use the doubly linked list, you will need one more attribute prev to indicate the previous node in the linked list. Assume all nodes in the linked list are 0-indexed.

Implement these functions in your linked list class:

get(index) : Get the value of the index-th node in the linked list. If the index is invalid, return -1.
addAtHead(val) : Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list.
addAtTail(val) : Append a node of value val to the last element of the linked list.
addAtIndex(index, val) : Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. If index is negative, the node will be inserted at the head of the list.
deleteAtIndex(index) : Delete the index-th node in the linked list, if the index is valid.
Example:

MyLinkedList linkedList = new MyLinkedList();
linkedList.addAtHead(1);
linkedList.addAtTail(3);
linkedList.addAtIndex(1, 2);  // linked list becomes 1->2->3
linkedList.get(1);            // returns 2
linkedList.deleteAtIndex(1);  // now the linked list is 1->3
linkedList.get(1);            // returns 3
Note:

All values will be in the range of [1, 1000].
The number of operations will be in the range of [1, 1000].
Please do not use the built-in LinkedList library.
*/
class MyLinkedList {
private:
    struct Node {
        explicit Node(int v) : val(v), next(0) { }
        int val;
        Node* next;
    };
    Node* d_head;
    int d_size;
public:
    /** Initialize your data structure here. */
    MyLinkedList() : d_head(0), d_size(0) {

    }

    ~MyLinkedList() {
        while (d_size--) {
            Node* p = d_head;
            d_head = d_head->next;
            delete p;
        }
        d_head = 0;
    }
    void print() const {
        std::cout << "(" << d_size << ")";
        Node* p = d_head;
        while (p) {
            std::cout << p->val << ", ";
            p = p->next;
        }
        std::cout << std::endl;
    }
    /** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
    int get(int index) {
        if (index < 0 or index >= d_size) return -1;
        Node* p = d_head;
        while (index--) {
            p = p->next;
        }
        return p->val;
    }

    /** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
    void addAtHead(int val) {
        Node* p = new Node(val);
        p->next = d_head;
        d_head = p;
        d_size++;
    }

    /** Append a node of value val to the last element of the linked list. */
    void addAtTail(int val) {
        Node* p = new Node(val);
        if (not d_head) {
            d_head = p;
        } else {
            Node* k = d_head;
            Node* pp = 0;
            while (k) {
                pp = k;
                k = k->next;
            }
            pp->next = p;
        }
        d_size++;
    }

    /** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
    void addAtIndex(int index, int val) {
        if (index == d_size) {
            addAtTail(val);
            return;
        }
        if (index > d_size) {
            return;
        }
        if (index < 0) index = 0;
        Node* prev = 0;
        Node* p = d_head;
        while (index--) {
            prev = p;
            p = p->next;
        }
        if (prev) {
            Node* p = new Node(val);
            p->next = prev->next;
            prev->next = p;
            d_size++;
        } else {
            addAtHead(val);
        }
    }

    /** Delete the index-th node in the linked list, if the index is valid. */
    void deleteAtIndex(int index) {
        if (index < 0 or index >= d_size) return;
        Node* prev = 0;
        Node* p = d_head;
        while (index--) {
            prev = p;
            p = p->next;
        }
        if (prev) {
            prev->next = prev->next->next;
        } else {
            d_head = p->next;
        }
        delete p;
        d_size--;
    }
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */
