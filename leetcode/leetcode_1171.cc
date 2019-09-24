/*
1171. Remove Zero Sum Consecutive Nodes from Linked List
https://leetcode.com/problems/remove-zero-sum-consecutive-nodes-from-linked-list/

Given the head of a linked list, we repeatedly delete consecutive sequences of nodes that sum to 0 until there are no such sequences.

After doing so, return the head of the final linked list.  You may return any such answer.



(Note that in the examples below, all sequences are serializations of ListNode objects.)

Example 1:

Input: head = [1,2,-3,3,1]
Output: [3,1]
Note: The answer [1,2,1] would also be accepted.
Example 2:

Input: head = [1,2,3,-3,4]
Output: [1,2,4]
Example 3:

Input: head = [1,2,3,-3,-2]
Output: [1]


Constraints:

The given linked list will contain between 1 and 1000 nodes.
Each node in the linked list has -1000 <= node.val <= 1000.
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
	ListNode* removeZeroSumSublists(ListNode* head) {
		// accumulate previous node's value to next
		head = increase(head);
		head = removeSublists(head);
		head = decrease(head);
		return head;
	}
private:
    ListNode* increase(ListNode* head) {
		ListNode* p = head;
		while (p->next) {
			p->next->val += p->val;
			p = p->next;
		}
        return head;
    }
	ListNode* removeSublists(ListNode* head) {
		// for example: 1, 2, -3, 3, 1
		// => 1, 3, 0, 3, 4
		if (not head) return 0;
		// we'd like to find 2 nodes which have same value, like above 2nd node and 4-th node
		ListNode* p = head;
		while (p) {
			ListNode* st = p->next;
			while (st) {
				if (st->val == p->val) {
					p->next = st->next;
				}
				st = st->next;
			}
			p = p->next;
		}
        // find 0, which means all previous nodes accumulated to 0
        p = head;
        while (p) {
            if (p->val == 0) {
                head = p->next;
            }
            p = p->next;
        }
		return head;
	}
	ListNode* decrease(ListNode* head) {
		if (not head) return head;
		ListNode* next = decrease(head->next);
		if (next) {
			next->val -= head->val;
		}
		return head;
	}
};
