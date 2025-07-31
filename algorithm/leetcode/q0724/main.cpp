#include<vector>
#include<numeric>
using namespace std;

class Solution {
public:
    int pivotIndex(vector<int>& nums) {
        int sum = accumulate(nums.cbegin(), nums.cend(), 0);
        int left_sum = 0;
        for (size_t i = 0; i < nums.size(); i++) {
            int right_sum = sum - left_sum - nums[i];
            if (left_sum == right_sum) return i;
            left_sum += nums[i];
        }
        return -1;
    }
};

int main() {

}