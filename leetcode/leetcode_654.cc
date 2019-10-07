/*
654. Maximum Binary Tree
Medium
https://leetcode.com/problems/maximum-binary-tree/

Given an integer array with no duplicates. A maximum tree building on this array is defined as follow:

The root is the maximum number in the array.
The left subtree is the maximum tree constructed from left part subarray divided by the maximum number.
The right subtree is the maximum tree constructed from right part subarray divided by the maximum number.
Construct the maximum tree by the given array and output the root node of this tree.

Example 1:
Input: [3,2,1,6,0,5]
Output: return the tree root node representing the following tree:

      6
    /   \
   3     5
    \    /
     2  0
       \
        1
Note:
The size of the given array will be in the range [1,1000].
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
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        int l = 0, r = (int)nums.size()-1;
        return constructMaximumBinaryTree(nums, l, r);
    }
private:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums, int l, int r) {
        if (l > r) return 0;
        int maxi = findMax(nums, l, r);
        TreeNode* root = new TreeNode(nums[maxi]);
        root->left = constructMaximumBinaryTree(nums, l, maxi-1);
        root->right = constructMaximumBinaryTree(nums, maxi+1, r);
        return root;
    }
    // find maximum value's index
    int findMax(vector<int>& nums, int l, int r) {
        if (l > r) return -1;
        int res = l;
        while (l <= r) {
            if (nums[l] > nums[res]) {
                res = l;
            }
            l++;
        }
        return res;
    }
};
