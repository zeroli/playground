/*
234. Palindrome Linked List
https://leetcode.com/problems/palindrome-linked-list/

Given a singly linked list, determine if it is a palindrome.

Example 1:

Input: 1->2
Output: false
Example 2:

Input: 1->2->2->1
Output: true
Follow up:
Could you do it in O(n) time and O(1) space?
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
    bool isPalindrome(ListNode* head) {
        ListNode* mid = findMid(head);
        mid = reverse(mid);
        while (head and mid) {
            if (head->val != mid->val) {
                return false;
            }
            head = head->next;
            mid = mid->next;
        }
        return true;
    }
private:
    ListNode* findMid(ListNode* head) {
        ListNode* fast = head;
        ListNode* slow = head;
        while (fast) {
            fast = fast->next;
            if (fast) {
                fast = fast->next;
                slow = slow->next;
            }
        }
        return slow;
    }
    ListNode* reverse(ListNode* head) {
        if (not head) return 0;
        if (not head->next) return head;
        ListNode* nn = reverse(head->next);
        head->next->next = head;
        head->next = NULL;
        return nn;
    }
};
