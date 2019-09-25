/*
142. Linked List Cycle II
https://leetcode.com/problems/linked-list-cycle-ii/

Given a linked list, return the node where the cycle begins. If there is no cycle, return null.

To represent a cycle in the given linked list, we use an integer pos which represents the position (0-indexed) in the linked list where tail connects to. If pos is -1, then there is no cycle in the linked list.

Note: Do not modify the linked list.



Example 1:

Input: head = [3,2,0,-4], pos = 1
Output: tail connects to node index 1
Explanation: There is a cycle in the linked list, where tail connects to the second node.


Example 2:

Input: head = [1,2], pos = 0
Output: tail connects to node index 0
Explanation: There is a cycle in the linked list, where tail connects to the first node.


Example 3:

Input: head = [1], pos = -1
Output: no cycle
Explanation: There is no cycle in the linked list.
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
    ListNode *detectCycle(ListNode *head) {
        ListNode* fast = head;
        ListNode* slow = head;
        ListNode* tmp = head;
        while (fast) {
            fast = fast->next;
            if (fast) {
                fast = fast->next;
                slow = slow->next;
            }
            if (fast and fast == slow) {
                // cycle exists
                // when fast takes 2n steps here, slow takes n steps here
                // so if slow takes n more steps, and another one takes n steps from head
                // they will definitely meet at this exact location eventually,
                // and more at some intermediate node, they already met. that node is cycle starting point
                while (slow != tmp) {
                    slow = slow->next;
                    tmp = tmp->next;
                }
                return slow;
            }
        }
        return 0;
    }

    ListNode *detectCycle1(ListNode *head) {
        ListNode* fast = head;
        ListNode* slow = head;
        while (fast) {
            fast = fast->next;
            if (fast) {
                fast = fast->next;
                slow = slow->next;
            }
            if (fast and fast == slow) {
                // cycle exists
                break;
            }
        }
        if (not fast) return 0;

        // break it at that 'slow' node
        ListNode* l1 = head;
        ListNode* l2 = slow->next;
        slow = slow->next;
        fast->next = 0;

        int l1len = 0;
        while (l1) {
            l1len++;
            l1 = l1->next;
        }
        l1 = head;

        int l2len = 0;
        while (l2) {
            l2len++;
            l2 = l2->next;
        }
        l2 = slow;

        if (l1len > l2len) {
            while (l1len-- > l2len) {
                l1 = l1->next;
            }
        } else if (l1len < l2len) {
            while (l2len-- > l1len) {
                l2 = l2->next;
            }
        }
        while (l1 and l2) {
            if (l1 == l2) {
                return l1;
            }
            l1 = l1->next;
            l2 = l2->next;
        }
        return 0;
    }
};
