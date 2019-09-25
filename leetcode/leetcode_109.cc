/*
109. Convert Sorted List to Binary Search Tree
https://leetcode.com/problems/convert-sorted-list-to-binary-search-tree/

Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.

For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees of every node never differ by more than 1.

Example:

Given the sorted linked list: [-10,-3,0,5,9],

One possible answer is: [0,-3,9,-10,null,5], which represents the following height balanced BST:

      0
     / \
   -3   9
   /   /
 -10  5
 */
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        if (not head) return 0;
        if (not head->next) return new TreeNode(head->val);

        ListNode* prev_mid = 0;
        ListNode* mid = findMid(head, &prev_mid);
        // head ==> prev_mid will be left tree, mid will be root, mid->next will be right tree
        prev_mid->next = 0;

        TreeNode* root = new TreeNode(mid->val);
        root->left = sortedListToBST(head);
        root->right = sortedListToBST(mid->next);
        return root;
    }
private:
    ListNode* findMid(ListNode* head, ListNode** pmid) {
        ListNode* fast = head;
        ListNode* slow = head;
        *pmid = slow;
        while (fast) {
            fast = fast->next;
            if (fast) {
                fast = fast->next;
                *pmid = slow;
                slow = slow->next;
            }
        }
        return slow;
    }
};
