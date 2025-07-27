#include<vector>
using namespace std;

class Solution {
public:
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        auto length1 = nums1.size();
        auto length2 = nums2.size();
        
        // dp[i][j] 表示以 n1[i-1] 和 n2[j-1] 结尾的最大公共子数组
        int dp[length1+1][length2+1];
        for (size_t i = 0; i <= length1; i++) dp[i][0] = 0;
        for (size_t j = 0; j <= length2; j++) dp[0][j] = 0;
        

        int max_dp = 0;
        for (size_t i = 1; i <= length1; i++) {
            int num1 = nums1[i-1];
            for (size_t j = 1; j <= length2; j++) {
                int num2 = nums2[j-1];
                if (num1 == num2) {
                    dp[i][j] = dp[i-1][j-1] + 1;
                    max_dp = max(max_dp, dp[i][j]);
                } else {
                    dp[i][j] = 0;
                }
            }
        }
        return max_dp;
    }
};

#include<cassert>
#include<iostream>

int main() {
    Solution s;
    vector<int> nums1 {1,2,3,2,1};
    vector<int> nums2 {3,2,1,4,7};
    int len = s.findLength(nums1, nums2);
    cout << len << endl;
    assert(len == 3);
}
