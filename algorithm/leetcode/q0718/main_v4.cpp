#include<vector>
#include<algorithm>
#include<cstring>
using namespace std;

inline int my_abs(int a) {
    int sign = a >> 31;        // sign = 0 if a >= 0; -1 if a < 0
    return (a ^ sign) - sign;  // 如果负数，就取反加 1（即取绝对值）
}

inline int my_max(int a, int b) {
    return (a + b + my_abs(a - b)) / 2;
}

// return 1 if a==b else 0
inline int eq_1(int a, int b) {
    return a == b;
}

class Solution {
public:
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        // auto length1 = nums1.size();
        auto length2 = nums2.size();

        int temp = length2+1;
        int* dp = new int[temp];

        memset(dp, 0, sizeof(int) * temp);
        
        temp = length2-1;
        int* dp_last = dp + length2;
        int* dp_last2 = dp + temp;

        int max_dp = 0;
        for (int num1: nums1) {
            auto nums_it = nums2.end()-1;
            int* dpj = dp_last; 
            int* dpj1 = dp_last2;
            for (int j = temp; j >= 0; j--) {
                int num2 = *(nums_it--);
                int eq1 = int(num1 == num2);

                int dpj_v = (*dpj1) * eq1 + eq1;
                max_dp = my_max(max_dp, dpj_v);
                *dpj = dpj_v;
                dpj--;
                dpj1--;
            }
        }

        delete[] dp;

        return max_dp;
    }
};

#include<cassert>
#include<iostream>

int main() {
    Solution s;
    {
        vector<int> nums1 {1,2,3,2,1};
        vector<int> nums2 {3,2,1,4,7};
        int len = s.findLength(nums1, nums2);
        cout << len << endl;
        assert(len == 3);
    }

    {
        vector<int> nums1 {69,51,94,52,72,74,65,65,99,1};
        vector<int> nums2 {65,99,82,27,43,95,9,20,13,99};
        int len = s.findLength(nums1, nums2);
        cout << len << endl;
        assert(len == 2);
    }
}
