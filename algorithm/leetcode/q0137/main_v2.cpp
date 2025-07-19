#include<vector>
using namespace std;

class Solution {
public:
    int singleNumber(vector<int> &nums) {
        int result = 0, carry = 0, temp;
        for (int n : nums) {
            carry ^= result & n; // 记录进位
            result ^= n; // 无进位加法
            // carry 和 result 同时为 1 时，表示 b11，即 3，视为 0
            // 即 carry 和 result 都置为 0
            temp = ~(carry & result);
            carry &= temp; // 111000 
            result &= temp;
        }
        return result;
    }
};

#include<cassert>

int main() {
    Solution m;
    vector<int> v {2,2,2,-10};
    assert(m.singleNumber(v)==-10);
}