/*
23. Merge k Sorted Lists
https://leetcode.com/problems/merge-k-sorted-lists/

Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.

Example:

Input:
[
  1->4->5,
  1->3->4,
  2->6
]
Output: 1->1->2->3->4->4->5->6
*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
typedef ListNode* ListNodePtr;
struct MinHeap {
	MinHeap(int K) : d_capacity(K), d_size(0) {
		d_data = new ListNodePtr[K + 1];
		memset(d_data, 0, (K + 1) * sizeof(ListNodePtr));
	}
	~MinHeap() {
		delete[] d_data;
	}

	bool push(ListNodePtr node) {
		// push to min heap
		if (d_size >= d_capacity) {
			return false; // cannot push more, full
		}
		d_data[++d_size] = node;
		percolateUp(d_size);
		return true;
	}

	ListNodePtr pop() {
		// pop min from top
		ListNodePtr top = peek();
		d_data[1] = d_data[d_size--];
		percolateDown(1);
		return top;
	}

	ListNodePtr peek() {
		// get top min from top, no change to min heap
		if (d_size <= 0) return NULL;
		return d_data[1];
	}
	int size() const {
		return d_size;
	}
	bool empty() const {
		return size() == 0;
	}
private:
	inline int parent(int idx) {
		return idx / 2;
	}
	inline int left(int idx) {
		return idx * 2;
	}
	inline int right(int idx) {
		return idx * 2 + 1;
	}
	void percolateUp(int k) {
		while (k > 1) {
			int pid = parent(k);
			if (d_data[pid]->val <= d_data[k]->val) {
				break;
			}
			swap(d_data[pid], d_data[k]);
			k = pid;
		}
	}
	void percolateDown(int k) {
		while (k <= d_size / 2) {
			int child = left(k);
			if (child < d_size and d_data[child]->val > d_data[child+1]->val) {
				child++;
			}
			if (d_data[child]->val >= d_data[k]->val) {
				break;
			}
			swap(d_data[child], d_data[k]);
			k = child;
		}
	}
private:
	int d_capacity;
	int d_size;
	ListNodePtr* d_data;
};
class Solution {
public:
	ListNode* mergeKLists(vector<ListNode*>& lists) {
		int K = (int)lists.size();
		ListNode* res = 0;
		ListNode** pp = &res;
		MinHeap minh(K);
		// 1st iteration, select at most K nodes, and select the minimum one from them
		for (int i = 0; i < K; i++) {
			ListNode* head = lists[i];
			if (not head) continue;
			minh.push(head);
		}

		while (!minh.empty()) {
			ListNode* nn = minh.pop();
			*pp = nn;
			if (nn->next) {
				minh.push(nn->next);
			}
			pp = &(nn->next);
		}
		return res;
	}
};
