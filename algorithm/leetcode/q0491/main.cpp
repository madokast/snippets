#include<vector>
#include<map>
using namespace std;

bool v_eq(vector<int>& v1, vector<int>& v2) {
    if (v1.size() != v2.size()) return false;
    for (size_t i = 0; i < v1.size(); i++) {
        if (v1[i] != v2[i]) return false;
    }
    return true;
}

unsigned int v_hash(vector<int>& v) {
    unsigned int h = 0;
    for (int e : v) {
        h += static_cast<unsigned int>(e);
        h *= 33;
    }
    return h;
}

class Solution {
public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        map<int, vector<pair<unsigned int, vector<int>>>> m;
        for (int num : nums) {
            vector<vector<int>> new_seqs;
            for (auto &kv : m) {
                if (kv.first > num) break;
                for (auto& p : kv.second) {
                    auto seq = p.second; // do copy
                    seq.push_back(num);
                    new_seqs.push_back(move(seq));
                }
            }
            new_seqs.emplace_back(1, num);

            for (vector<int>& seq : new_seqs) {
                auto h = v_hash(seq);
                bool has_same = false;
                for (auto &p : m[num]) {
                    if (p.first == h && v_eq(seq, p.second)) {
                        has_same = true;
                        break;
                    }
                }
                if (!has_same) {
                    m[num].push_back(make_pair(h, move(seq)));
                }
            }
        }
        
        vector<vector<int>> results;
        for (auto &kv : m) {
            for (auto &p : kv.second) {
                auto& seq = p.second;
                if (seq.size() > 1) {
                    results.push_back(move(seq));
                }
            }
        }
        
        return results;
    }
};

#include<iostream>

template <typename T>
void printVector(const vector<T>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        if (i > 0) cout << ", ";  // 非第一个元素前加逗号
        cout << v[i];
    }
    cout << "]" << endl;
}

int main() {
    Solution s;
    vector<int> v = {4, 6, 7, 7};
    auto vv = s.findSubsequences(v);
    for (auto &&i : vv) {
        printVector(i);
    }
    
}