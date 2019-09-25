/*
445. Add Two Numbers II
https://leetcode.com/problems/add-two-numbers-ii/

You are given two non-empty linked lists representing two non-negative integers. The most significant digit comes first and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Follow up:
What if you cannot modify the input lists? In other words, reversing the lists is not allowed.

Example:

Input: (7 -> 2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 8 -> 0 -> 7
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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        l1 = reverse(l1);
        l2 = reverse(l2);
        ListNode* nn = 0;
        ListNode** pnn = &nn;
        int c = 0;
        while (l1 or l2) {
            ListNode* kn = new ListNode(0);
            if (l1 and l2) {
                kn->val = l1->val + l2->val + c;

                l1 = l1->next;
                l2 = l2->next;
            } else if (l1) {
                kn->val = l1->val + c;

                l1 = l1->next;
            } else {
                kn->val = l2->val + c;

                l2 = l2->next;
            }
            c = kn->val / 10;
            kn->val %= 10;
            *pnn = kn;
            pnn = &(kn->next);
        }
        if (c) {
            *pnn = new ListNode(c);
        }
        nn = reverse(nn);
        return nn;
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
};
