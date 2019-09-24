/*
143. Reorder List
https://leetcode.com/problems/reorder-list/

Given a singly linked list L: L0→L1→…→Ln-1→Ln,
reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…

You may not modify the values in the list's nodes, only nodes itself may be changed.

Example 1:

Given 1->2->3->4, reorder it to 1->4->2->3.
Example 2:

Given 1->2->3->4->5, reorder it to 1->5->2->4->3.
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
    void reorderList(ListNode* head) {
        if (not head) return;

        ListNode* fast = head;
        ListNode* slow = head;
        while (fast) {
            fast = fast->next;
            if (fast) {
                fast = fast->next;
            }
            if (fast) {
                slow = slow->next;
            }
        }
        ListNode* l2 = slow->next;
        slow->next = 0;
        l2 = reverse(l2);
        merge(head, l2);
    }
private:
    ListNode* reverse(ListNode* head) {
        ListNode* prev = 0, *cur = head, *next = 0;
        while (cur) {
            next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        return prev;
    }
    void merge(ListNode* head, ListNode* l2) {
        ListNode* p1 = head;
        ListNode* p2 = l2;
        ListNode** pp1 = &(p1->next);
        while (p1 and p2) {
            p1 = p1->next;
            *pp1 = p2;
            p2 = p2->next;
            (*pp1)->next = p1;
            if (p1)
                pp1 = &(p1->next);
        }
        if (p2) {
            (*pp1)->next = p2;
        }
    }
};
