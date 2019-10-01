/*
82. Remove Duplicates from Sorted List II
https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/

Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.

Example 1:

Input: 1->2->3->3->4->4->5
Output: 1->2->5
Example 2:

Input: 1->1->1->2->3
Output: 2->3
*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (not head) return head;
        ListNode** pp = &head;
        ListNode* p = head;
        ListNode* nn = 0;
        while (p) {
            nn = findFirstDiffNode(p, p->val);
            if (nn != p->next) { // no change to pp
                *pp = nn;
            } else {
                pp = &(p->next);
            }
            p = nn;
        }
        return head;
    }
private:
    ListNode* findFirstDiffNode(ListNode* head, int val) {
        ListNode* p = head;
        while (p) {
            if (p->val != val) {
                break;
            } else {
                head = p->next;
                p = p->next;
            }
        }
        return head;
    }

//https://www.geeksforgeeks.org/remove-occurrences-duplicates-sorted-linked-list/
// Function to remove all occurrences
// of duplicate elements
void removeAllDuplicates(struct Node* &start)
{
    // create a dummy node
    // that acts like a fake
    // head of list pointing
    // to the original head
    Node* dummy = new Node;

    // dummy node points
    // to the original head
    dummy -> next = start;

    // Node pointing to last
    // node which has no duplicate.
    Node* prev = dummy;

    // Node used to traverse
    // the linked list.
    Node* current = start;

    while(current != NULL)
    {
        // Until the current and
        // previous values are
        // same, keep updating current
        while(current -> next != NULL &&
              prev -> next -> data == current -> next -> data)
            current = current -> next;

        // if current has unique value
        // i.e current is not updated,
        // Move the prev pointer to
        // next node
        if (prev -> next == current)
            prev = prev -> next;

        // when current is updated
        // to the last duplicate
        // value of that segment,
        // make prev the next of current
        else
            prev -> next = current -> next;

        current = current -> next;
    }

    // update original head to
    // the next of dummy node
    start = dummy -> next;
}
};
