#include<vector>
#include<unordered_set>
using namespace std;


class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> s(nums.size());
        for (size_t i = 0; i < nums.size(); i++)
        {
            int num = nums[i];
            auto inserted = s.insert(num);
            if (!inserted.second) return true;
        }
        return false;
         
    }
};

int main() {
    
}
