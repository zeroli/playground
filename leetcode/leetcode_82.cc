/*
82. Remove Duplicates from Sorted List II
https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/

Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.

Example 1:

Input: 1->2->3->3->4->4->5
Output: 1->2->5
Example 2:

Input: 1->1->1->2->3
Output: 2->3
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
        ListNode** pp = &head;
        ListNode* p = head;
        ListNode* nn = 0;
        while (p) {
            nn = findFirstDiffNode(p, p->val);
            if (nn != p->next) { // no change to pp
                *pp = nn;
            } else {
                pp = &(p->next);
            }
            p = nn;
        }
        return head;
    }
private:
    ListNode* findFirstDiffNode(ListNode* head, int val) {
        ListNode* p = head;
        while (p) {
            if (p->val != val) {
                break;
            } else {
                head = p->next;
                p = p->next;
            }
        }
        return head;
    }
};
