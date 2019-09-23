/*
92. Reverse Linked List II
https://leetcode.com/problems/reverse-linked-list-ii/

Reverse a linked list from position m to n. Do it in one-pass.

Note: 1 ≤ m ≤ n ≤ length of list.

Example:

Input: 1->2->3->4->5->NULL, m = 2, n = 4
Output: 1->4->3->2->5->NULL
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
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        ListNode* p = head;
        ListNode** pp = &head;
        m--;
        n -= m;

        while (m--) {
            pp = &(p->next);
            p = p->next;
        }

        ListNode* prev = 0, *cur = p, *next = 0;
        while (n--) {
            next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        p->next = cur;
        *pp = prev;
        return head;
    }
};
