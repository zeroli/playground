/*
150. Evaluate Reverse Polish Notation
Medium
https://leetcode.com/problems/evaluate-reverse-polish-notation/

Evaluate the value of an arithmetic expression in Reverse Polish Notation.

Valid operators are +, -, *, /. Each operand may be an integer or another expression.

Note:

Division between two integers should truncate toward zero.
The given RPN expression is always valid. That means the expression would always evaluate to a result and there won't be any divide by zero operation.
Example 1:

Input: ["2", "1", "+", "3", "*"]
Output: 9
Explanation: ((2 + 1) * 3) = 9
Example 2:

Input: ["4", "13", "5", "/", "+"]
Output: 6
Explanation: (4 + (13 / 5)) = 6
Example 3:

Input: ["10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"]
Output: 22
Explanation:
  ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
= ((10 * (6 / (12 * -11))) + 17) + 5
= ((10 * (6 / -132)) + 17) + 5
= ((10 * 0) + 17) + 5
= (0 + 17) + 5
= 17 + 5
= 22
*/
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> stk;
        for (const auto& token : tokens) {
            int op = -1;
            if (isOperator(token, op)) {
                int operand2 = stk.top();
                stk.pop();
                int operand1 = stk.top();
                stk.pop();
                stk.push(calculate(operand1, operand2, op));
            } else {
                stk.push(atoi(token.c_str()));
            }
        }
        return stk.top();
    }
private:
    bool isOperator(const string& token, int& op) {
        op = -1;
        if (token == "+") op = 0;
        else if (token == "-") op = 1;
        else if (token == "*") op = 2;
        else if (token == "/") op = 3;
        return op >= 0;
    }
    int calculate(int a, int b, int op) {
        switch (op) {
            case 0: return a + b;
            case 1: return a - b;
            case 2: return a * b;
            case 3: return a / b;
            default: assert(0);
        }
        return -1;
    }
};
