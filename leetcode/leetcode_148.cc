/*
148. Sort List
https://leetcode.com/problems/sort-list/

Sort a linked list in O(n log n) time using constant space complexity.

Example 1:

Input: 4->2->1->3
Output: 1->2->3->4
Example 2:

Input: -1->5->3->4->0
Output: -1->0->3->4->5
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
    // merge sort version
    ListNode* sortList(ListNode* head) {
        ListNode* fast = head;
        ListNode* slow = head;
        ListNode* prev = 0;
        while (fast) {
            fast = fast->next;
            if (fast) {
                fast = fast->next;
                prev = slow;
                slow = slow->next;
            }
        }
        if (prev) {
            prev->next = 0;
			head = sortList(head);
			slow = sortList(slow);
            head = mergeTwoLists(head, slow);
        }
        return head;
    }
private:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (not l1) return l2;
        if (not l2) return l1;
        ListNode* res = l1;
        ListNode** p = 0;
        while (l1 or l2) {
            if (l1 and l2) {
                if (l1->val <= l2->val) {
                    p = &(l1->next);
                    l1 = l1->next;
                } else { // move l2 before l1
                    ListNode* next = l2->next;
                    // first goes here, [2] and [1], p may be null
                    // so that l2 will be new head for result
                    if (p) *p = l2;
                    else { res = l2; }
                    l2->next = l1;
                    p = &(l2->next);
                    l2 = next;
                }
            } else {
                if (l1) {
                    break;
                }
                if (l2) {
                    *p = l2;
                    break;
                }
            }
        }
        return res;
    }
private:
    // quick sort version
	struct ListSegment {
		ListNode* head;
		ListNode** tail;
	};
	ListNode* sortList1(ListNode* head) {
		if (not head) return head;

		ListSegment ls;
		ls.head = head;
		ls.tail = &(head->next);
		while (head) {
			ls.tail = &(head->next);
			head = head->next;
		}
		quickSort(&ls);
		return ls.head;
	}
	void quickSort(ListSegment* head) {
		if (not head) return;
		if (not head->head) return;

		ListSegment before, equal, after;
		partition(head->head, before, equal, after);
		quickSort(&before);
		quickSort(&after);
		head->head = 0;
		if (before.head) {
			*(before.tail) = equal.head;
			if (not head->head) {
				head->head = before.head;
			}
			head->tail = before.tail;
		}
		if (equal.head) {
			*(equal.tail) = after.head;
			if (not head->head) {
				head->head = equal.head;
			}
			head->tail = equal.tail;
		}
		if (after.head) {
			*(after.tail) = 0;
			if (not head->head) {
				head->head = after.head;
			}
			head->tail = after.tail;
		}
	}
	// partition list to before, equal, greater than
	// return partition node, and update head
	void partition(ListNode* head,
		ListSegment& before,
		ListSegment& equal,
		ListSegment& after)
	{
		if (not head) return;

		before.head = 0;
		equal.head = 0;
		after.tail = 0;
		before.tail = &before.head;
		equal.tail = &equal.head;
		after.tail = &after.head;

		int x = head->val;
		while (head) {
			if (head->val < x) {
				*(before.tail) = head;
				before.tail = &(head->next);
			}
			else if (head->val > x) {
				*(after.tail) = head;
				after.tail = &(head->next);
			}
			else {
				*(equal.tail) = head;
				equal.tail = &(head->next);
			}
			head = head->next;
		}
		*before.tail = 0;
		*equal.tail = 0;
		*after.tail = 0;
	}
};
