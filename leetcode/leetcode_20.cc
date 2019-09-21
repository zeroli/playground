/*
20. Valid Parentheses
https://leetcode.com/problems/valid-parentheses/
Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

An input string is valid if:

Open brackets must be closed by the same type of brackets.
Open brackets must be closed in the correct order.
Note that an empty string is also considered valid.

Example 1:

Input: "()"
Output: true
Example 2:

Input: "()[]{}"
Output: true
Example 3:

Input: "(]"
Output: false
Example 4:

Input: "([)]"
Output: false
Example 5:

Input: "{[]}"
Output: true
*/
class Solution {
public:
    bool isValid(string s) {
        stack<char> sc;
        for (int i = 0; i < (int)s.size(); i++) {
            char c = s[i];
            if (!sc.empty()) {
                char k = sc.top();
                if ((c == ')' and k == '(') or
                    (c == ']' and k == '[') or
                    (c == '}' and k == '{')) {
                    sc.pop();
                } else {
                    sc.push(c);
                }
            } else {
                sc.push(c);
            }
        }
        return sc.empty();
    }
};
