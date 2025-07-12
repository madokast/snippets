#include<vector>
using namespace std;

class Solution {
public:
    int missingNumber(vector<int>& nums) {
        auto n = static_cast<int>(nums.size());
        while (true) {
            auto exchaned = false;
            for (auto i=0; i<n; i++) {
                auto i_holder = nums[i];
                while (i_holder != i && i_holder != n) {
                    exchaned = true;
                    auto temp = nums[i_holder];
                    nums[i_holder] = i_holder;
                    i_holder = temp;
                }
                nums[i] = i_holder;
            }
            if (!exchaned) {
                for (auto i=0; i<n; i++) {
                    if (i!=nums[i]) {
                        return i;
                    }
                }
                return n;
            }
        }
    }
};

#include<cassert>

int main() {
    auto s = Solution();
    auto nums = vector<int> {0, 1};
    assert(s.missingNumber(nums) == 2);
}