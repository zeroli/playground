/*
232. Implement Queue using Stacks
Easy
https://leetcode.com/problems/implement-queue-using-stacks/

Implement the following operations of a queue using stacks.

push(x) -- Push element x to the back of queue.
pop() -- Removes the element from in front of queue.
peek() -- Get the front element.
empty() -- Return whether the queue is empty.
Example:

MyQueue queue = new MyQueue();

queue.push(1);
queue.push(2);
queue.peek();  // returns 1
queue.pop();   // returns 1
queue.empty(); // returns false
Notes:

You must use only standard operations of a stack -- which means only push to top, peek/pop from top, size, and is empty operations are valid.
Depending on your language, stack may not be supported natively. You may simulate a stack by using a list or deque (double-ended queue), as long as you use only standard operations of a stack.
You may assume that all operations are valid (for example, no pop or peek operations will be called on an empty queue).
*/
class MyQueue {
public:
    /** Initialize your data structure here. */
    MyQueue() {

    }

    /** Push element x to the back of queue. */
    void push(int x) {
        d_stk1.push(x);
    }

    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        if (d_stk2.empty()) {
            while (!d_stk1.empty()) {
                d_stk2.push(d_stk1.top());
                d_stk1.pop();
            }
        }
        int ret = d_stk2.top();
        d_stk2.pop();
        return ret;
    }

    /** Get the front element. */
    int peek() {
        if (d_stk2.empty()) {
            while (!d_stk1.empty()) {
                d_stk2.push(d_stk1.top());
                d_stk1.pop();
            }
        }
        return d_stk2.top();
    }

    /** Returns whether the queue is empty. */
    bool empty() {
        return (d_stk1.empty() and d_stk2.empty());
    }
private:
    stack<int> d_stk1;
    stack<int> d_stk2;
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */
