#include<vector>
#include<array>
using namespace std;

constexpr size_t N = sizeof(int) * 8;
using Cnt = char; // max length is 10^4
using RNum = unsigned int;

void accumulate_bit_number(array<Cnt, N> &cs, RNum number) {
    for (size_t i = 0;; i++) {
        // cs[i] += number % 2;
        cs[i] = (cs[i] + number % 2) % 3;
        number /= 2;
        if (number == 0) return;
    }
}

class Solution
{
public:
    int singleNumber(vector<int> &nums) {
        array<Cnt, N> a {0};
        for (const int& n : nums) {
            accumulate_bit_number(a, static_cast<RNum>(n));
        }
        RNum result = 0;
        for (size_t i = N-1; i < N; i--) {
            result *= 2;
            result += a[i] % 3;
        }
        return static_cast<int>(result);
    }
};

#include<cassert>

int main() {
    Solution m;
    vector<int> v {2,2,2,-10};
    assert(m.singleNumber(v)==-10);
}