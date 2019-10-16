/*
925. Long Pressed Name
Easy
https://leetcode.com/problems/long-pressed-name/

Your friend is typing his name into a keyboard.  Sometimes, when typing a character c, the key might get long pressed, and the character will be typed 1 or more times.

You examine the typed characters of the keyboard.  Return True if it is possible that it was your friends name, with some characters (possibly none) being long pressed.



Example 1:

Input: name = "alex", typed = "aaleex"
Output: true
Explanation: 'a' and 'e' in 'alex' were long pressed.
Example 2:

Input: name = "saeed", typed = "ssaaedd"
Output: false
Explanation: 'e' must have been pressed twice, but it wasn't in the typed output.
Example 3:

Input: name = "leelee", typed = "lleeelee"
Output: true
Example 4:

Input: name = "laiden", typed = "laiden"
Output: true
Explanation: It's not necessary to long press any character.


Note:

name.length <= 1000
typed.length <= 1000
The characters of name and typed are lowercase letters.
*/
class Solution {
public:
    bool isLongPressedName(string name, string typed) {
        int sz_name = (int)name.size();
        int sz_typed = (int)typed.size();
        int i = -1, j = -1;
        for (int k = 0; k < sz_name; k++) {
            char c = name[k];
            j = i + 1;
            while (j < sz_typed) {
                if (typed[j] != c) {
                    if (i < 0 or typed[j] != typed[i])
                        return false;
                    j++;
                } else {
                    i = j;
                    break;
                }
            }
            if (j == sz_typed) return false;
        }
        j = i + 1;
        while (j < sz_typed) {
            if (typed[j] != typed[i]) return false;
            j++;
        }
        return true;
    }
};
