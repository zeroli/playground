/*
21. Merge Two Sorted Lists
https://leetcode.com/problems/merge-two-sorted-lists/

Merge two sorted linked lists and return it as a new list. The new list should be made by splicing together the nodes of the first two lists.

Example:

Input: 1->2->4, 1->3->4
Output: 1->1->2->3->4->4
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
};
