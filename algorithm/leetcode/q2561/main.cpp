#include<vector>
#include<map>
#include<set>
#include<algorithm>
#include<iostream>
using namespace std;

class Solution {
public:
    long long minCost(vector<int>& basket1, vector<int>& basket2) {
        map<int, pair<int, int>> m;
        for (auto &&k : basket1) m[k].first++;
        for (auto &&k : basket2) m[k].second++;
        
        // 判断每个 pair [0]+[1] 是不是偶数，还有差异多少
        // 差异多少记录到 s1 s2
        // 记录一个最小值
        multiset<int> s1, s2;
        int minValue = basket1[0];
        for (auto &&p : m) {
            minValue = min(p.first, minValue);
            auto& counts = p.second;
            if ((counts.first + counts.second) % 2 != 0) return -1;
            int diff = (counts.first - counts.second) / 2;
            while (diff > 0) {
                s1.insert(p.first);
                diff--;
            }
            while (diff < 0) {
                s2.insert(p.first);
                diff++;
            }
        }
        minValue *= 2; // 做中间人，需要两次代价
        long long r = 0;
        // 找出 s1 和 s2 中的最小值，再找另一边的最大值
        while (!s1.empty()) {
            auto s1_min = *s1.cbegin();
            auto s2_min = *s2.cbegin();
            if (s1_min <= s2_min) {
                auto s2_max = (--s2.cend());
                if (minValue < s1_min) r += minValue;
                else r += s1_min;
                s1.erase(s1.cbegin());
                s2.erase(--s2.cend());
            } else {
                auto s1_max = (--s1.cend());
                if (minValue < s2_min) r += minValue;
                else r += s2_min;
                s1.erase(--s1.cend());
                s2.erase(s2.cbegin());
            }
            // cout << r << endl;
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
}