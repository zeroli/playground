/*
155. Min Stack
https://leetcode.com/problems/min-stack/

Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

push(x) -- Push element x onto stack.
pop() -- Removes the element on top of the stack.
top() -- Get the top element.
getMin() -- Retrieve the minimum element in the stack.


Example:

MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin();   --> Returns -3.
minStack.pop();
minStack.top();      --> Returns 0.
minStack.getMin();   --> Returns -2.
*/
class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {

    }

    void push(int x) {
        d_data.push_back(x);
        if (d_mindata.empty() or d_mindata.back() > x) {
            d_mindata.push_back(x);
        } else {
            d_mindata.push_back(d_mindata.back());
        }
    }

    void pop() {
        if (d_data.empty()) return;
        d_data.pop_back();
        d_mindata.pop_back();
    }

    int top() {
        return d_data.back();
    }

    int getMin() {
        return d_mindata.back();
    }
private:
    std::vector<int> d_mindata;
    std::vector<int> d_data;
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
