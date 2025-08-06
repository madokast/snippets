#include<vector>
#include<unordered_map>
#include<set>
#include<algorithm>
#include<iostream>
using namespace std;

class Solution {
public:
    long long minCost(vector<int>& basket1, vector<int>& basket2) {
        unordered_map<int, pair<int, int>> m;
        int minValue = basket1[0];
        for (auto &&k : basket1) {m[k].first++; minValue = min(minValue, k);}
        for (auto &&k : basket2) {m[k].second++; minValue = min(minValue, k);}
        minValue *= 2; // 做中间人，需要两次代价

        // 判断每个 pair [0]+[1] 是不是偶数，还有差异多少
        // 差异多少记录到 v
        // 记录一个最小值
        // 再记录要交换的次数
        vector<pair<int, int>> v;
        v.reserve(basket1.size() + basket2.size());
        size_t swapNum = 0;
        for (auto &&p : m) {
            auto& counts = p.second;
            if ((counts.first + counts.second) % 2 != 0) return -1;
            int diff = abs((counts.first - counts.second) / 2);
            swapNum += diff;
            v.push_back(make_pair(min(p.first, minValue), diff));
        }
        sort(v.begin(), v.end());
        swapNum /= 2; // 交换次数一半，因为换一次就复位 2 个数
        long long r = 0;
        // 从 s1 s2 中找到最小的 swapNum 个值
        for (auto &&p : v) {
            int num = p.first;
            int cnt = p.second;
            if (num < minValue) {
                if (cnt < swapNum) {
                    r += num * cnt;
                    swapNum -= cnt;
                } else {
                    r += num * swapNum;
                    break;
                }
            } else {
                r += minValue * swapNum;
                break;
            }
        }
        return r;
    }
};

int main() {
    Solution s;
    {
        vector<int> v1{4,2,2,2};
        vector<int> v2{1,4,1,2};
        cout << s.minCost(v1, v2) << endl;
    }
    {
        vector<int> v1{4,4,4,4,3};
        vector<int> v2{5,5,5,5,3};
        cout << s.minCost(v1, v2) << endl;
    }
    {
        vector<int> v1{84,80,43,8,80,88,43,14,100,88};
        vector<int> v2{32,32,42,68,68,100,42,84,14,8};
        cout << s.minCost(v1, v2) << endl;
    }
}