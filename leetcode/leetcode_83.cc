/*
83. Remove Duplicates from Sorted List
https://leetcode.com/problems/remove-duplicates-from-sorted-list/

Given a sorted linked list, delete all duplicates such that each element appear only once.

Example 1:

Input: 1->1->2
Output: 1->2
Example 2:

Input: 1->1->2->3->3
Output: 1->2->3
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
        ListNode** pp = &(head->next);
        ListNode* p = head;
        while (p->next) {
            if (p->val == p->next->val) {
                *pp = p->next->next; // don't change p
            } else {
                p = p->next;
                pp = &(p->next);
            }
        }
        return head;
    }
};
