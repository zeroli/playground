/*
203. Remove Linked List Elements
https://leetcode.com/problems/remove-linked-list-elements/

Remove all elements from a linked list of integers that have value val.

Example:

Input:  1->2->6->3->4->5->6, val = 6
Output: 1->2->3->4->5
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
    ListNode* removeElements(ListNode* head, int val) {
        if (not head) return 0;
        if (head->val == val) {
            head = removeElements(head->next, val);
        } else {
            head->next = removeElements(head->next, val);
        }
        return head;
    }
    ListNode* _removeElements(ListNode* head, int val) {
        ListNode* nn = head;
        ListNode** pp = 0;
        ListNode* p = head;
        while (p) {
            if (p->val == val) {
                if (not pp) {
                    p = p->next;
                    nn = p;
                } else {
                    *pp = p->next;
                    p = p->next;
                }
            } else {
                pp = &(p->next);
                p = p->next;
            }
        }
        return nn;
    }
};
