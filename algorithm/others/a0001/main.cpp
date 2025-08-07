#include<vector>
#include<iostream>
#include<algorithm>

int max1_length_flip0(std::vector<bool>& v, int flip_num) {
    if (flip_num < 0) return 0;

    int i = 0, j = 0, cnt0 = 0; // cnt0 = count 0 in v[i:j]
    int max1 = 0; // max1 = max j-i
    for (;;) {
        // 0 达到上限继续扩大，只到超出限制或者到末尾
        while (cnt0 <= flip_num && j < v.size()) {
            max1 = std::max(max1, j-i);
            cnt0 += int(!v[j++]);
        }
        // 窗口到末尾，退出前再更新一次 max1
        if (j == v.size()) {
            if (cnt0 <= flip_num) max1 = std::max(max1, j-i);
            return max1;
        }

        // 下面是缩小窗口，缩到满足即可
        // 因为 flip_num 不是负数，而 cnt0 可以正常减少到 0，所以不担心 i 超过 j
        while (cnt0 > flip_num) {
            cnt0 -= int(!v[i++]);
        }
    }
}

int solve(int size, std::vector<int>& indexes0, int flip_num) {
    std::vector<bool> bv(size, 1);
    for (auto &&i : indexes0) bv[i-1] = 0;
    return max1_length_flip0(bv, flip_num);
}

int solve_with_cin() {
    int size;
    std::cin >> size;
    std::vector<bool> bv(size, 1);

    size_t size0;
    std::cin >> size0;
    for (size_t i = 0; i < size0; i++) {
        int index0;
        std::cin >> index0;
        bv[index0-1] = 0;
    }
    int flip_num;
    std::cin >> flip_num;

    return max1_length_flip0(bv, flip_num);
}

int main() {
    {
        std::vector<bool> v{1, 0, 1, 1, 0};
        std::cout << max1_length_flip0(v, 1) << std::endl;
    }
    {
        std::vector<bool> v{1, 0, 1, 0, 1};
        std::cout << max1_length_flip0(v, 1) << std::endl;
    }
    {
        std::vector<int> v{2, 4};
        std::cout << solve(5, v, 1) << std::endl;
    }
    {
        std::vector<int> v{2, 4, 7};
        std::cout << solve(10, v, 1) << std::endl;
    }
    {
        std::vector<int> v{2, 4, 7}; // 0f2f45f789
        std::cout << solve(10, v, 0) << std::endl;
    }
    // cin
    // std::cout << solve_with_cin() << std::endl;
}

