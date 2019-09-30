/*
137. Single Number II
https://leetcode.com/problems/single-number-ii/

Given a non-empty array of integers, every element appears three times except for one, which appears exactly once. Find that single one.

Note:

Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?

Example 1:

Input: [2,2,3,2]
Output: 3
Example 2:

Input: [0,1,0,1,0,1,99]
Output: 99
*/
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int onceSeen = 0, twiceSeen = 0;
        for (int i = 0; i < (int)nums.size(); i++) {
            onceSeen = (onceSeen ^ nums[i]) & (~twiceSeen);
            twiceSeen = (twiceSeen ^ nums[i]) & (~onceSeen);
        }
        return onceSeen;
    }
};

/*
Let the number appearing once be x. Let S(x) be the positions whose values equal to 1 for the binary representation of x. For example, when x=3, S(x)={0,1}.
For all the numbers, at the positions other than S(x), the number of 1s appearing is 3k, i.e., a multiple of 3; at the positions of S(x), the number of 1s is 3k+1. So if we record the number of 1s appearing for each position, then use the positions where 1s appear 3k+1 to reconstruct x.
For each position, 1s could appear 3k,3k+1,3k+2 times. To represent 3 statuses, we at least need 2 bits for each position (that is why we need m1,m2 and no need for m3).
For each position, we check manipulate as follows: if the previous status is (0,0) for (m1,m2), when there is 1, we change the status into (1,0); if the previous status is (1,0), when there is 1, we change the status into (0,1).. etc.
The manipulation of each bit can be simplified into a whole integer xor and land.

class Solution {
public:
    /**
    times   m1  m2
    0   0   0
    1   1   0
    2   0   1
    3   0   0
    4   1   0
    5   0   1

    int singleNumber(vector<int>& nums) {
        int m1 = 0, m2 = 0;
        for (auto n : nums) {
            m1 = (m1 ^ n) & (~m2);
            m2 = (m2 ^ n) & (~m1);
        }
        return m1;
    }
};
*/
/*
class Solution {
    /*
     *                           (c,a) init ->  (0,0)
     *   first  n = 1 -->  c |= a & n =0, a = 1  (0,1)
     *   second n = 1 -->  c |= a & n =1, a = 0  (1,0)
     *   thrid  n = 1 -->  c |= a & n =1, a = 1  (1,1)
     *                                   and form11to00 = 1
     *                                   so a^=form11to00 = 0 ;c ^= form11to00 =0;


    public int singleNumber(int[] nums) {
        if(nums.length == 0) return 0;
        int a = 0, c = 0;
        for (int n : nums){
            c |= a & n;             // 0->0->1->1
            a ^= n;                 // 0->1->0->1
            int form11to00 = c&a;   //    0->0->1 act like a trigger when c&a = 1.
            a ^= form11to00;                                            // a->0 c->0
            c ^= form11to00;
        }
        return a;
    }
}
*/

/*
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int bits[32];
        for (int i = 0; i < 32; i++)
            bits[i] = 0;

        for (int num : nums){
            for (int i = 0; i < 32; i++){
                if ((num >> i) & 1 == 1)
                    bits[i]++;
            }
        }

        int res = 0;
        for (int i = 0; i < 32; i++){
            if (bits[i] != 0 && (bits[i] % 3) != 0)
                res |= 1 << i;
        }

        return res;
    }
};
*/
