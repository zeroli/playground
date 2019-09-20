/*
977. Squares of a Sorted Array
Given an array of integers A sorted in non-decreasing order, return an array of the squares of each number, also in sorted non-decreasing order.



Example 1:

Input: [-4,-1,0,3,10]
Output: [0,1,9,16,100]
Example 2:

Input: [-7,-3,2,3,11]
Output: [4,9,9,49,121]


Note:

1 <= A.length <= 10000
-10000 <= A[i] <= 10000
A is sorted in non-decreasing order.
*/
class Solution {
public:
    vector<int> sortedSquares(vector<int>& A) {
        size_t sz = A.size();
        vector<int> res(sz, 0);
        int pos1 = 0;
        int pos2 = sz - 1;
        int k = sz - 1;
        while (pos1 <= pos2) {
            int s1 = A[pos1] * A[pos1];
            int s2 = A[pos2] * A[pos2];
            if (s1 > s2) {
                res[k--] = s1;
                pos1++;
            } else {
                res[k--] = s2;
                pos2--;
            }
        }
        return res;
    }
private:
    vector<int> _sortedSquares3(vector<int>& A) {
        size_t sz = A.size();
        vector<int> res;
        res.reserve(sz);
        int mid = findFirstPositive(A);
        if (mid < 0) { // all numbers are negative
            for (size_t i = 0; i < sz; i++) {
                res.push_back(A[sz - i - 1]);
                res[i] *= res[i];
            }
        } else {
            merge2SortedArray(A, mid, res);
        }
        return res;
    }
    int findFirstPositive(const vector<int>& A) {
        size_t sz = A.size();
        size_t l = 0, r = sz - 1;
        size_t mid = 0;
        while (l < r) {
            mid = l + (r - l) / 2;
            if (A[mid] == 0) {
                return (int)mid;
            } else if (A[mid] < 0) {
                l = mid + 1;
            } else { // > 0
                r = mid; // keep this mid > 0
            }
        }
        if (A[l] >= 0) { return l; }
        else { return -1; }
    }
    void merge2SortedArray(const vector<int>& A, int mid, vector<int>& res) {
        size_t sz = A.size();
        int pos1 = mid - 1;
        int pos2 = mid;
        while (pos1 >= 0 and pos2 < sz) {
            int s1 = A[pos1] * A[pos1];
            int s2 = A[pos2] * A[pos2];
            if (s1 < s2) {
                res.push_back(s1);
                pos1--;
            } else {
                res.push_back(s2);
                pos2++;
            }
        }
        while (pos1 >= 0) {
            int s1 = A[pos1] * A[pos1];
            res.push_back(s1);
            pos1--;
        }
        while (pos2 < sz) {
            int s2 = A[pos2] * A[pos2];
            res.push_back(s2);
            pos2++;
        }
    }
private:
    // solution 2
    vector<int> _sortedSquares2(vector<int>& A) {
        size_t sz = A.size();
        vector<int> res(A);
        for (size_t i = 0; i < sz; i++) {
            res[i] = res[i] < 0 ? -res[i] : res[i];
        }
        sort(res.begin(), res.end());
        for (size_t i = 0; i < sz; i++) {
            res[i] *= res[i];
        }
        return res;
    }
    // solution 1
    vector<int> _sortedSquares1(vector<int>& A) {
        size_t sz = A.size();
        vector<int> res(sz, 0);
        for (size_t i = 0; i < sz; i++) {
            int s = A[i] * A[i];
            insertSorted(res, i, s);
        }
        return res;
    }
    void insertSorted(vector<int>& v, int j, int a) {
        v[j] = a;
        int i = j - 1;
        while (i >= 0 and v[i] > a) {
            v[i+1] = v[i];
            i--;
        }
        v[i+1] = a;
    }
};
