#include<vector>
#include<unordered_set>
using namespace std;

class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        k += 1;
        unordered_set<int> s(k*2+1);
        for (size_t i = 0; i < min(size_t(k), nums.size()); i++)
        {
            auto p = s.insert(nums[i]);
            if (!p.second) return true;
        }

        for (size_t i = k; i < nums.size(); i++)
        {
            s.erase(nums[i-k]);
            auto p = s.insert(nums[i]);
            if (!p.second) return true;
        }
        return false;
    }
};