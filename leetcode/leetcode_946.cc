/*
946. Validate Stack Sequences
Medium
https://leetcode.com/problems/validate-stack-sequences/

Given two sequences pushed and popped with distinct values, return true if and only if this could have been the result of a sequence of push and pop operations on an initially empty stack.



Example 1:

Input: pushed = [1,2,3,4,5], popped = [4,5,3,2,1]
Output: true
Explanation: We might do the following sequence:
push(1), push(2), push(3), push(4), pop() -> 4,
push(5), pop() -> 5, pop() -> 3, pop() -> 2, pop() -> 1
Example 2:

Input: pushed = [1,2,3,4,5], popped = [4,3,5,1,2]
Output: false
Explanation: 1 cannot be popped before 2.


Note:

0 <= pushed.length == popped.length <= 1000
0 <= pushed[i], popped[i] < 1000
pushed is a permutation of popped.
pushed and popped have distinct values.
*/
class Solution {
public:
    // simulate from push
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        int push_sz = (int)pushed.size();
        stack<int> stk;
        int i = 0;
        for (int j = 0; j < push_sz; j++) {
            stk.push(pushed[j]);
            while (!stk.empty() and stk.top() == popped[i]) {
                stk.pop();
                i++;
            }
        }
        return stk.empty();
    }
    // simulate from pop
    bool validateStackSequences1(vector<int>& pushed, vector<int>& popped) {
        int push_sz = (int)pushed.size();
        int pop_sz = (int)popped.size();
        stack<int> stk;
        int i = -1;
        for (int j = 0; j < pop_sz; j++) {
            int val = popped[j];
            if (stk.empty() or stk.top() != val) {
                while (++i < push_sz) {
                    if (val == pushed[i]) {
                        break;
                    } else {
                        stk.push(pushed[i]);
                    }
                }
                if (i == push_sz) {
                    return false;
                }
            } else {
                stk.pop();
            }
        }
        return true;
    }
};
