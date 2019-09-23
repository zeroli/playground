/*
86. Partition List
https://leetcode.com/problems/partition-list/

Given a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.

You should preserve the original relative order of the nodes in each of the two partitions.

Example:

Input: head = 1->4->3->2->5->2, x = 3
Output: 1->2->2->4->3->5
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
    ListNode* partition(ListNode* head, int x) {
        if (not head) return head;

        ListNode* before = 0;
        ListNode** pb = &before;
        ListNode* after = 0;
        ListNode** pa = &after;
        while (head) {
            if (head->val < x) {
                // move to before list
                *pb = head;
                pb = &(head->next);
            } else {
                // move to after list
                *pa = head;
                pa = &(head->next);
            }
            head = head->next;
        }
        *pb = after;
        *pa = 0;
        head = before;
        return head;
    }
};
