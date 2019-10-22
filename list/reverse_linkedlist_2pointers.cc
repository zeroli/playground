/*
Iteratively Reverse a linked list using only 2 pointers (An Interesting Method)
Examples:

Input : Head of following linked list
       1->2->3->4->NULL
Output : Linked list should be changed to,
       4->3->2->1->NULL

Input : Head of following linked list
       1->2->3->4->5->NULL
Output : Linked list should be changed to,
       5->4->3->2->1->NULL
*/
// C++ program to reverse a linked list using two pointers.
#include <bits/stdc++.h>
using namespace std;
typedef uintptr_t ut;

/* Link list node */
struct Node {
	int data;
	struct Node* next;
};

/* Function to reverse the linked list using 2 pointers */
void reverse(struct Node** head_ref)
{
	struct Node* prev = NULL;
	struct Node* current = *head_ref;

	// at last prev points to new head
	while (current != NULL) {
		// This expression evaluates from left to right
		// current->next = prev, changes the link fron
		// next to prev node
		// prev = current, moves prev to current node for
		// next reversal of node
		// This example of list will clear it more 1->2->3->4
		// initially prev = 1, current = 2
		// Final expression will be current = 1^2^3^2^1,
		// as we know that bitwise XOR of two same
		// numbers will always be 0 i.e; 1^1 = 2^2 = 0
		// After the evaluation of expression current = 3 that
		// means it has been moved by one node from its
		// previous position
		current = (struct Node*)((ut)prev ^ (ut)current ^ (ut)(current->next) ^ (ut)(current->next = prev) ^ (ut)(prev = current));
	}

	*head_ref = prev;
}

/* Function to push a node */
void push(struct Node** head_ref, int new_data)
{
	/* allocate node */
	struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

	/* put in the data */
	new_node->data = new_data;

	/* link the old list off the new node */
	new_node->next = (*head_ref);

	/* move the head to point to the new node */
	(*head_ref) = new_node;
}

/* Function to print linked list */
void printList(struct Node* head)
{
	struct Node* temp = head;
	while (temp != NULL) {
		printf("%d ", temp->data);
		temp = temp->next;
	}
}

/* Driver program to test above function*/
int main()
{
	/* Start with the empty list */
	struct Node* head = NULL;

	push(&head, 20);
	push(&head, 4);
	push(&head, 15);
	push(&head, 85);

	printf("Given linked list\n");
	printList(head);
	reverse(&head);
	printf("\nReversed Linked list \n");
	printList(head);
	return 0;
}

// C++ program to reverse a linked list using two pointers.
#include <bits/stdc++.h>
using namespace std;
typedef uintptr_t ut;

/* Link list node */
struct Node {
	int data;
	struct Node* next;
};

/* Function to reverse the linked list using 2 pointers */
void reverse(struct Node** head_ref)
{
	struct Node* current = *head_ref;
	struct Node* next;
	while (current->next != NULL) {
		next = current->next;
		current->next = next->next;
		next->next = (*head_ref);
		*head_ref = next;
	}
}

/* Function to push a node */
void push(struct Node** head_ref, int new_data)
{
	struct Node* new_node = new Node;
	new_node->data = new_data;
	new_node->next = (*head_ref);
	(*head_ref) = new_node;
}

/* Function to print linked list */
void printList(struct Node* head)
{
	struct Node* temp = head;
	while (temp != NULL) {
		printf("%d ", temp->data);
		temp = temp->next;
	}
}

/* Driver program to test above function*/
int main()
{
	/* Start with the empty list */
	struct Node* head = NULL;

	push(&head, 20);
	push(&head, 4);
	push(&head, 15);
	push(&head, 85);

	printf("Given linked list\n");
	printList(head);
	reverse(&head);
	printf("\nReversed Linked list \n");
	printList(head);
	return 0;
}
