/*
https://www.geeksforgeeks.org/swap-nodes-in-a-linked-list-without-swapping-data/

Given a linked list and two keys in it, swap nodes for two given keys. Nodes should be swapped by changing links. Swapping data of nodes may be expensive in many situations when data contains many fields.
It may be assumed that all keys in linked list are distinct.

Examples:

Input:  10->15->12->13->20->14,  x = 12, y = 20
Output: 10->15->20->13->12->14

Input:  10->15->12->13->20->14,  x = 10, y = 20
Output: 20->15->12->13->10->14

Input:  10->15->12->13->20->14,  x = 12, y = 13
Output: 10->15->13->12->20->14
Recommended: Please try your approach on {IDE} first, before moving on to the solution.


This may look a simple problem, but is interesting question as it has following cases to be handled.
1) x and y may or may not be adjacent.
2) Either x or y may be a head node.
3) Either x or y may be last node.
4) x and/or y may not be present in linked list.
*/

/* This program swaps the nodes of linked list rather
than swapping the field from the nodes.*/
#include <bits/stdc++.h>
using namespace std;

/* A linked list node */
class Node
{
    public:
    int data;
    Node *next;
};

/* Function to swap nodes x and y in linked list by
changing links */
void swapNodes(Node **head_ref, int x, int y)
{
// Nothing to do if x and y are same
if (x == y) return;

// Search for x (keep track of prevX and CurrX
Node *prevX = NULL, *currX = *head_ref;
while (currX && currX->data != x)
{
    prevX = currX;
    currX = currX->next;
}

// Search for y (keep track of prevY and CurrY
Node *prevY = NULL, *currY = *head_ref;
while (currY && currY->data != y)
{
    prevY = currY;
    currY = currY->next;
}

// If either x or y is not present, nothing to do
if (currX == NULL || currY == NULL)
    return;

// If x is not head of linked list
if (prevX != NULL)
    prevX->next = currY;
else // Else make y as new head
    *head_ref = currY;

// If y is not head of linked list
if (prevY != NULL)
    prevY->next = currX;
else // Else make x as new head
    *head_ref = currX;

// Swap next pointers
Node *temp = currY->next;
currY->next = currX->next;
currX->next = temp;
}

/* Function to add a node at the beginning of List */
void push(Node** head_ref, int new_data)
{
    /* allocate node */
    Node* new_node =new Node();

    /* put in the data */
    new_node->data = new_data;

    /* link the old list off the new node */
    new_node->next = (*head_ref);

    /* move the head to point to the new node */
    (*head_ref) = new_node;
}

/* Function to print nodes in a given linked list */
void printList(Node *node)
{
    while(node != NULL)
    {
        cout<<node->data<<" ";
        node = node->next;
    }
}

/* Driver program to test above function */
int main()
{
    Node *start = NULL;

    /* The constructed linked list is:
    1->2->3->4->5->6->7 */
    push(&start, 7);
    push(&start, 6);
    push(&start, 5);
    push(&start, 4);
    push(&start, 3);
    push(&start, 2);
    push(&start, 1);

    cout << "Linked list before calling swapNodes() ";
    printList(start);

    swapNodes(&start, 4, 3);

    cout << "\nLinked list after calling swapNodes() ";
    printList(start);

    return 0;
}

// more clean code
// C++ program to swap two given nodes of a linked list
#include <iostream>

using namespace std;

// A linked list node class
class Node {

public:
	int data;
	class Node* next;

	// constructor
	Node(int val, Node* next)
		: data(val), next(next)
	{
	}

	// print list from this
	// to last till null
	void printList()
	{

		Node* node = this;

		while (node != NULL) {

			cout << node->data;
			node = node->next;
		}

		cout << endl;
	}
};

// Function to add a node
// at the beginning of List
void push(Node** head_ref, int new_data)
{

	// allocate node
	(*head_ref) = new Node(new_data, *head_ref);
}

void swap(Node*& a, Node*& b)
{

	Node* temp = a;
	a = b;
	b = temp;
}

void swapNodes(Node** head_ref, int x, int y)
{

	// Nothing to do if x and y are same
	if (x == y)
		return;

	Node **a = NULL, **b = NULL;

	// search for x and y in the linked list
	// and store therir pointer in a and b
	while (*head_ref) {

		if ((*head_ref)->data == x) {
			a = head_ref;
		}

		else if ((*head_ref)->data == y) {
			b = head_ref;
		}

		head_ref = &((*head_ref)->next);
	}

	// if we have found both a and b
	// in the linked list swap current
	// pointer and next pointer of these
	if (a && b) {

		swap(*a, *b);
		swap(((*a)->next), ((*b)->next));
	}
}

// Driver code
int main()
{

	Node* start = NULL;

	// The constructed linked list is:
	// 1->2->3->4->5->6->7
	push(&start, 7);
	push(&start, 6);
	push(&start, 5);
	push(&start, 4);
	push(&start, 3);
	push(&start, 2);
	push(&start, 1);

	cout << "Linked list before calling swapNodes() ";
	start->printList();

	swapNodes(&start, 6, 3);

	cout << "Linked list after calling swapNodes() ";
	start->printList();
}
