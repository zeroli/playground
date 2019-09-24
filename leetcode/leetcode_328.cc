/*
328. Odd Even Linked List
https://leetcode.com/problems/odd-even-linked-list/

Given a singly linked list, group all odd nodes together followed by the even nodes. Please note here we are talking about the node number and not the value in the nodes.

You should try to do it in place. The program should run in O(1) space complexity and O(nodes) time complexity.

Example 1:

Input: 1->2->3->4->5->NULL
Output: 1->3->5->2->4->NULL
Example 2:

Input: 2->1->3->5->6->4->7->NULL
Output: 2->3->6->7->1->5->4->NULL
Note:

The relative order inside both the even and odd groups should remain as it was in the input.
The first node is considered odd, the second node even and so on ...
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
    ListNode* oddEvenList(ListNode* head) {
        if (not head) return head;
        ListNode* odd = head;
        ListNode* even = head->next;
        ListNode* evenHead = even;
        while (even and even->next) {
            odd->next = even->next;
            odd = odd->next;
            even->next = odd->next;
            even = even->next;
        }
        odd->next = evenHead;
        return head;
    }
private:
    ListNode* oddEvenList1(ListNode* head) {
        ListNode* even = 0;
        ListNode* odd = 0;
        ListNode** pe = &even;
        ListNode** po = &odd;
        int iflag = 1;
        while (head) {
            if (iflag & 1) { // odd index
                *po = head;
                po = &(head->next);
            } else { // even index
                *pe = head;
                pe = &(head->next);
            }
            head = head->next;
            iflag++;
        }
        *po = even;
        *pe = 0;
        return odd;
    }
};
