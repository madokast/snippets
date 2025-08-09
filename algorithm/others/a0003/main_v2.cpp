/**
 * 一个 N×M 的由非负整数构成的数字矩阵，你需要在其中取出若干个数字，使得取出的任意两个数字不相邻
 * （若一个数字在另外一个数字相邻 8 个格子中的一个即认为这两个数字相邻），求取出数字和最大是多少。
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int sum_of_row(vector<int>& row, int mask) {
    int sum = 0;
    for (int i = 0; ; i++) {
        if (mask % 2 == 1) sum += row[i];
        mask >>= 1;
        if (mask == 0) break;
    }
    
    return sum;
}

int max_sum_of_unjoined(vector<vector<int>>& m, int row_num, int column_num) {
    vector<vector<int>> dp;
    dp.emplace_back(1 << column_num, 0);
    // 计算第一行结果
    for (int mask = 0; mask < (1 << column_num); mask++) {
        // 判断 mask 是不是合法的，即没有连续的两个 1
        // 即 mask & (mask>>1) 是 0
        if ((mask & (mask>>1)) == 0) {
            dp[0][mask] = sum_of_row(m[0], mask);
        }
    }
    
    // 动态规划
    for (int i = 1; i < row_num; i++) {
        dp.emplace_back(1 << column_num, 0);
        for (int mask = 0; mask < (1 << column_num); mask++) {
            int max_sum = 0;
            // 本身不合法
            if ((mask & (mask>>1)) != 0) continue;
            int row_sum = sum_of_row(m[i], mask);
            for (int pre_mask = 0; pre_mask < (1 << column_num); pre_mask++) {
                // 本身不合法
                if ((pre_mask & (pre_mask>>1)) != 0) continue;
                // 查看交叉是否合法
                // 与结果必须为 0
                if ((mask & pre_mask) != 0) continue;
                // 或结果不能相邻
                int or_ = mask | pre_mask;
                if ((or_ & (or_>>1)) != 0) continue;

                int cur_sum = dp[i-1][pre_mask] + row_sum;
                max_sum = max(max_sum, cur_sum);
            }
            dp[i][mask] = max_sum;
        }
    }
    
    return *max_element(dp[row_num-1].cbegin(), dp[row_num-1].cend());
}

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        int N, M;
        cin >> N >> M;
        vector<vector<int>> m(N);
        for (int j = 0; j < N; j++) {
            m[j] = vector<int>(M);
            for (int k = 0; k < M; k++) {
                cin >> m[j][k];
            }
        }
        int r = max_sum_of_unjoined(m, N, M);
        cout << r << endl;
    }
}
// 64 位输出请用 printf("%lld")