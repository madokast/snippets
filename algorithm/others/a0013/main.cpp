/**
 * 三角形取数
 */

#include <iostream>
#include <vector>
using namespace std;

int max3(long long int a, long long int b, long long int c) {
    return max(a, max(b, c));
}

long long int slove(const vector<vector<int>>& triangle, int delte) {
    if (delte == 0) {
        long long int sum = 0;
        for (int r = 0; r < triangle.size(); r++) {
            sum += triangle[r][r];
        }
        return sum;
    }

    vector<vector<long long int>> dp(triangle.size());
    for (int r = triangle.size() - 1; r >= 0; r--) {
        int number = 2 * r + 1;
        dp[r].resize(number, -100000000000000L);
        int middle = r;
        int left_max = middle - delte;
        int right_max = middle + delte;
        if (left_max < 0) left_max = 0;
        if (right_max > number - 1) right_max = number - 1;
        if (r == triangle.size() - 1) {
            for (int i = left_max; i <= right_max; i++) {
                dp[r][i] = triangle[r][i];
            }
        } else {
            int middle_next = r + 1;
            int left_max_next = middle_next - delte;
            int right_max_next = middle_next + delte;
            if (left_max_next < 0) left_max_next = 0;
            if (right_max_next > dp[r + 1].size() - 1) right_max_next = dp[r + 1].size() - 1;

            for (int i = left_max; i <= right_max; i++) {
                int i_in_next = i + 1;
                int left_index = i_in_next - 1;
                int right_index = i_in_next + 1;
                int middle_index = i_in_next;

                long long int left = -100000000000000L, mid = -100000000000000L, right = -100000000000000L;
                
                if (left_index >= 0 && left_index < dp[r + 1].size() && left_index >= left_max_next && left_index <= right_max_next) {
                    left = dp[r + 1][left_index];
                }
                if (middle_index >= 0 && middle_index < dp[r + 1].size() && middle_index >= left_max_next && middle_index <= right_max_next) {
                    mid = dp[r + 1][middle_index];
                }
                if (right_index >= 0 && right_index < dp[r + 1].size() && right_index >= left_max_next && right_index <= right_max_next) {
                    right = dp[r + 1][right_index];
                }


                dp[r][i] = triangle[r][i] + max3(left, mid, right);
            }
        }
    }

    return dp[0][0];
}

int main() {
    /**
     * 输入例子：
        3 1
        1
        2 3 4
        5 6 7 8 9
     * 
     */
    int row, delta;
    cin >> row >> delta;
    vector<vector<int>> triangle(row);
    for (int i = 0; i < row; i++) {
        int number = 2 * i + 1;
        vector<int> tmp(number);
        for (int j = 0; j < number; j++) {
            cin >> tmp[j];
        }
        triangle[i] = move(tmp);
    }
    cout << slove(triangle, delta) << endl;
    return 0;
}
// 64 位输出请用 printf("%lld")

