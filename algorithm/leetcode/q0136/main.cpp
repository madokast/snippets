#include<vector>
#include<numeric> // accumulate
#include<functional> // bit_xor

using namespace std;

class Solution {
    public:
    int singleNumber(vector<int>& nums) {
        return accumulate(nums.cbegin(), nums.cend(), 0, bit_xor<int>{});
    }
};

#include<cassert>

int main() {
    Solution s{};
    vector<int> nums{2,2,1};
    assert(s.singleNumber(nums) == 1);
}
