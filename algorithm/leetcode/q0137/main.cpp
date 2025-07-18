#include<vector>
#include<array>
using namespace std;

constexpr size_t N = sizeof(int) * 8;

void accumulate_bit_number(array<int, N> &r, int number) {
    for (size_t i = 0; i < N; i++) {
        if (number % 2 == 1) r[i] += 1;
        number /= 2;
        if (number == 0) break;
    }
}

class Main
{
public:
    int singleNumber(vector<int> &nums) {
        array<int, N> a {0};
        for (const int& n : nums) {
            accumulate_bit_number(a, n);
        }
        int result = 0;
        for (size_t i = N-1; i < N; i--) {
            result *= 2;
            if (a[i] % 3 == 1) result += 1;
        }
        return result;
    }
};

#include<cassert>

int main() {
    Main m;
    vector<int> v {2,2,2,1};
    assert(m.singleNumber(v)==1);
}