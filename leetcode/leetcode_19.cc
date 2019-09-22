/*
19. Remove Nth Node From End of List
https://leetcode.com/problems/remove-nth-node-from-end-of-list/

Given a linked list, remove the n-th node from the end of list and return its head.

Example:

Given linked list: 1->2->3->4->5, and n = 2.

After removing the second node from the end, the linked list becomes 1->2->3->5.
Note:

Given n will always be valid.

Follow up:

Could you do this in one pass?
*/
class Solution {
public:
    // 1 pass solution
    // two pointers solution
    // 1 pointer which is 'ahead' pointer, and 1 pointer which is 'after' pointer
    // 'ahead' pointer will take n steps head of 'after' pointer
    // when 'ahead' pointer reaches the last node of list, the 'after' pointer should be that specified node to be deleted
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* ahead = head;
        ListNode* after = head;
        int steps = n;
        while (steps--) {
            ahead = ahead->next;
        }
        if (not ahead) {
            head = head->next;
            return head;
        }
        while (ahead->next) {
            ahead = ahead->next;
            after = after->next;
        }
        after->next = after->next->next;
        return head;
    }
    // 2 passes solution:
    // 1)first calculate list's length
    //   and then get the index for that node which is to be deleted, from beginnning
    // 2) finally loop list again to delete that node
    ListNode* removeNthFromEnd1(ListNode* head, int n) {
        int nn = listLength(head) - n;
        if (nn == 0) {
            return head->next;
        } else {
            ListNode* p = head;
            ListNode** pp = 0;
            while (nn--) {
                pp = &(p->next);
                p = p->next;
            }
            *pp = p->next;
            return head;
        }
    }
private:
    int listLength(ListNode* head) {
        int len = 0;
        while (head) {
            len++;
            head = head->next;
        }
        return len;
    }
};
