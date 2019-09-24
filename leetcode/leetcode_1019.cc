/*
1019. Next Greater Node In Linked List
https://leetcode.com/problems/next-greater-node-in-linked-list/

We are given a linked list with head as the first node.  Let's number the nodes in the list: node_1, node_2, node_3, ... etc.

Each node may have a next larger value: for node_i, next_larger(node_i) is the node_j.val such that j > i, node_j.val > node_i.val, and j is the smallest possible choice.  If such a j does not exist, the next larger value is 0.

Return an array of integers answer, where answer[i] = next_larger(node_{i+1}).

Note that in the example inputs (not outputs) below, arrays such as [2,1,5] represent the serialization of a linked list with a head node value of 2, second node value of 1, and third node value of 5.



Example 1:

Input: [2,1,5]
Output: [5,5,0]
Example 2:

Input: [2,7,4,3,5]
Output: [7,0,5,5,0]
Example 3:

Input: [1,7,5,1,9,2,5,1]
Output: [7,9,9,9,0,5,0,0]


Note:

1 <= node.val <= 10^9 for each node in the linked list.
The given list has length in the range [0, 10000].
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
    vector<int> nextLargerNodes(ListNode* head) {
        // use stack to keep previous scanned node
        stack<int> st;
        vector<int> res;
        int i = 0;
        while (head) {
            res.push_back(head->val);
            while (!st.empty() and res[st.top()] < head->val) {
                res[st.top()] = head->val;
                st.pop();
            }
            st.push(i);
            i++;
            head = head->next;
        }
        while (!st.empty()) {
            res[st.top()] = 0;
            st.pop();
        }
        return res;
    }
private:
    // reverse list, and iteratively find from end to beginning
	vector<int> nextLargerNodes(ListNode* head) {
		vector<int> larger;
		if (not head) return larger;
		ListNode* rhead = reverse(head);

		ListNode* cur = rhead;
		ListNode* prev = 0;
		ListNode* prev_larger = 0;
		ListNode* cur_larger = 0;
		while (cur) {
			cur_larger = 0;
			if (prev && cur->val < prev->val) {
				cur_larger = prev;
			} else if (prev_larger) {
				if (prev_larger->val > cur->val) {
					cur_larger = prev_larger;
				}
				else { // search from rhead
					ListNode* p = rhead;
					while (p != prev_larger) {
						if (p->val > cur->val) {
							cur_larger = p;
						}
						p = p->next;
					}
				}
			}
			larger.insert(larger.begin(), cur_larger ? cur_larger->val : 0);
			prev_larger = cur_larger;
			prev = cur;
			cur = cur->next;
		}
		return larger;
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
