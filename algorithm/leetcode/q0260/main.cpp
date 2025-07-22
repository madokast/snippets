#include<vector>
#include<numeric>
#include<iostream>
using namespace std;

class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        // do xor in all number
        int xor_r = accumulate(nums.cbegin(), nums.cend(), 0, bit_xor<int>());
        // cout << "xor_r = " << xor_r << endl;

        // one-bit mask
        int mask = 1;
        while ((mask & xor_r) == 0) mask<<=1;
        // cout << "mask = " << mask << endl;

        // do xor partition by mask
        pair<int, int> result = accumulate(nums.cbegin(), nums.cend(), pair<int,int>{0, 0}, [mask](pair<int, int> p, int b) {
            // cout << "b & mask = " << (b & mask) << endl;
            if ((b & mask) == 0) p.first ^= b;
            else p.second ^= b;
            return p;
        });

        return vector<int> {result.first, result.second};
    }
};


int main() {
    Solution s;
    vector<int> v{1,1,2,3,4,4};
    auto r = s.singleNumber(v);
    cout << "r = " << r[0] << ", " << r[1] << endl;
}
