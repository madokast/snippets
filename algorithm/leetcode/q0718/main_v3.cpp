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

class Solution {
public:
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        auto length1 = nums1.size();
        auto length2 = nums2.size();
        
        
        int* dp = new int[(length2+1)];

        memset(dp, 0, sizeof(int) * (length2+1));
        

        int max_dp = 0;
        for (size_t i = 1; i <= length1; i++) {
            int num1 = nums1[i-1];
            for (size_t j = length2; j >= 1; j--) {
                int num2 = nums2[j-1];
                if (num1 == num2) {
                    dp[j] = dp[j-1] + 1;
                    max_dp = my_max(max_dp, dp[j]);
                } else {
                    dp[j] = 0;
                }
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
