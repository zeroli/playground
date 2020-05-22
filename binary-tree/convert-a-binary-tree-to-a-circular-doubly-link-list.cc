/*
Convert a Binary Tree to a Circular Doubly Link List
Given a Binary Tree, convert it to a Circular Doubly Linked List (In-Place).

The left and right pointers in nodes are to be used as previous and next pointers respectively in converted Circular Linked List.
The order of nodes in List must be same as Inorder of the given Binary Tree.
The first node of Inorder traversal must be head node of the Circular List.
Example:
tree to list

Recommended: Please solve it on “PRACTICE” first, before moving on to the solution.
The idea can be described using below steps.
1) Write a general purpose function that concatenates two given circular doubly lists (This function is explained below).
2) Now traverse the given tree
….a) Recursively convert left subtree to a circular DLL. Let the converted list be leftList.
….a) Recursively convert right subtree to a circular DLL. Let the converted list be rightList.
….c) Make a circular linked list of root of the tree, make left and right of root to point to itself.
….d) Concatenate leftList with list of single root node.
….e) Concatenate the list produced in step above (d) with rightList.



Note that the above code traverses tree in Postorder fashion. We can traverse in inorder fashion also. We can first concatenate left subtree and root, then recur for right subtree and concatenate the result with left-root concatenation.

How to Concatenate two circular DLLs?

Get the last node of the left list. Retrieving the last node is an O(1) operation, since the prev pointer of the head points to the last node of the list.
Connect it with the first node of the right list
Get the last node of the second list
Connect it with the head of the list.
Below are implementations of above idea.
*/
// C++ Program to convert a Binary Tree
// to a Circular Doubly Linked List
#include<iostream>
using namespace std;

// To represents a node of a Binary Tree
struct Node
{
	struct Node *left, *right;
	int data;
};

// A function that appends rightList at the end
// of leftList.
Node *concatenate(Node *leftList, Node *rightList)
{
	// If either of the list is empty
	// then return the other list
	if (leftList == NULL)
		return rightList;
	if (rightList == NULL)
		return leftList;

	// Store the last Node of left List
	Node *leftLast = leftList->left;

	// Store the last Node of right List
	Node *rightLast = rightList->left;

	// Connect the last node of Left List
	// with the first Node of the right List
	leftLast->right = rightList;
	rightList->left = leftLast;

	// Left of first node points to
	// the last node in the list
	leftList->left = rightLast;

	// Right of last node refers to the first
	// node of the List
	rightLast->right = leftList;

	return leftList;
}

// Function converts a tree to a circular Linked List
// and then returns the head of the Linked List
Node *bTreeToCList(Node *root)
{
	if (root == NULL)
		return NULL;

	// Recursively convert left and right subtrees
	Node *left = bTreeToCList(root->left);
	Node *right = bTreeToCList(root->right);

	// Make a circular linked list of single node
	// (or root). To do so, make the right and
	// left pointers of this node point to itself
	root->left = root->right = root;

	// Step 1 (concatenate the left list with the list
	//		 with single node, i.e., current node)
	// Step 2 (concatenate the returned list with the
	//		 right List)
	return concatenate(concatenate(left, root), right);
}

// Display Circular Link List
void displayCList(Node *head)
{
	cout << "Circular Linked List is :\n";
	Node *itr = head;
	do
	{
		cout << itr->data <<" ";
		itr = itr->right;
	} while (head!=itr);
	cout << "\n";
}


// Create a new Node and return its address
Node *newNode(int data)
{
	Node *temp = new Node();
	temp->data = data;
	temp->left = temp->right = NULL;
	return temp;
}

// Driver Program to test above function
int main()
{
	Node *root = newNode(10);
	root->left = newNode(12);
	root->right = newNode(15);
	root->left->left = newNode(25);
	root->left->right = newNode(30);
	root->right->left = newNode(36);

	Node *head = bTreeToCList(root);
	displayCList(head);

	return 0;
}
