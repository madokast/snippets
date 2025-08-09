#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

void occupy(pair<int, int> local, map<pair<int, int>, int>& occupied, bool reverse) {
    int x = local.first;
    int y = local.second;
    if (reverse) {
        occupied[local] -= 1;
        occupied[make_pair(x+1, y)] -= 1;
        occupied[make_pair(x-1, y)] -= 1;
        occupied[make_pair(x+1, y+1)] -= 1;
        occupied[make_pair(x-1, y+1)] -= 1;
        occupied[make_pair(x+1, y-1)] -= 1;
        occupied[make_pair(x-1, y-1)] -= 1;

        occupied[make_pair(x, y+1)] -= 1;
        occupied[make_pair(x, y-1)] -= 1;
    } else {
        occupied[local] += 1;
        occupied[make_pair(x+1, y)] += 1;
        occupied[make_pair(x-1, y)] += 1;
        occupied[make_pair(x+1, y+1)] += 1;
        occupied[make_pair(x-1, y+1)] += 1;
        occupied[make_pair(x+1, y-1)] += 1;
        occupied[make_pair(x-1, y-1)] += 1;

        occupied[make_pair(x, y+1)] += 1;
        occupied[make_pair(x, y-1)] += 1;
    }
}

int max_sum_of_unjoined0(vector<pair<int, pair<int, int>>>& value_loc, 
        map<pair<int, int>, int>& occupied, int current_sum) {
    int max_sum = current_sum;
    for (auto &vl : value_loc) {
        if (occupied[vl.second] == 0) {
            occupy(vl.second, occupied, true);
            int sum = max_sum_of_unjoined0(value_loc, occupied, current_sum + vl.first);
            max_sum = max(max_sum, sum);
            occupy(vl.second, occupied, false);
        }
    }
    return max_sum;
}

int max_sum_of_unjoined(vector<vector<int>>& m, int row_num, int column_num) {
    vector<pair<int, pair<int, int>>> value_loc;
    value_loc.reserve(row_num * column_num);
    for (size_t i = 0; i < row_num; i++) {
        for (size_t j = 0; j < column_num; j++)
        {
            value_loc.push_back(make_pair(m[i][j], make_pair(i, j)));
        }
    }
    sort(value_loc.begin(), value_loc.end(), [](pair<int, pair<int, int>>& a, pair<int, pair<int, int>>& b) {
        return a < b;
    });

    map<pair<int, int>, int> occupied;
    
    return max_sum_of_unjoined0(value_loc, occupied, 0);
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