#include<vector>
#include<set>
#include<cmath>
using namespace std;


class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int indexDiff, int valueDiff) {
        if (nums.size() == 0) return false;
        indexDiff += 1;
        set<int> s{};
        s.insert(nums[0]);
        for (size_t i = 1; i < indexDiff; i++)
        {
            int num = nums[i];
            auto p = s.insert(num);
            if (!p.second) return true;
            if (p.first != s.begin()) {
                int pre = *(--p.first);
                if (abs(num - pre) <= valueDiff) return true;
                ++p.first;
            }
            if ((++p.first) != s.end()) {
                int next = *p.first;
                if (abs(num - next) <= valueDiff) return true;
            }
        }

        for (size_t i = indexDiff; i < nums.size(); i++)
        {
            s.erase(nums[i-indexDiff]);
            int num = nums[i];
            auto p = s.insert(num);
            if (!p.second) return true;
            if (p.first != s.begin()) {
                int pre = *(--p.first);
                if (abs(num - pre) <= valueDiff) return true;
                ++p.first;
            }
            if ((++p.first) != s.end()) {
                int next = *p.first;
                if (abs(num - next) <= valueDiff) return true;
            }
        }
        
        
        return false;
    }
};

int main() {
    vector<int> v {1,5,9,1,5,9};
    Solution().containsNearbyAlmostDuplicate(v, 2, 3);
}