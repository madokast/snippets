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

bool v_eq_add_one(vector<int>& v1, vector<int>& v2, int num) {
    if (v1.size() != v2.size()-1) return false;
    if (v1[v1.size()-1] != num) return false;
    for (size_t i = 0; i < v2.size()-1; i++) {
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

unsigned int v_hash_add_one(vector<int>& v, int num) {
    unsigned int h = 0;
    for (int e : v) {
        h += static_cast<unsigned int>(e);
        h *= 33;
    }
    h += static_cast<unsigned int>(num);
    return h;
}

struct VectorSet {
    map<unsigned, vector<vector<int>&>> data;
    pair<bool, unsigned int> exist_v_add_one(vector<int>& v, int num) {
        unsigned int h = v_hash_add_one(v, num);
        auto it = this->data.find(h);
        if (it == this->data.end()) return make_pair(false, h);
        for (auto& e : (*it).second) {
            if (v_eq_add_one(e, v, num)) return make_pair(true, h);
        }
        return make_pair(false, h);
    }
    void put(vector<int>& v, unsigned int h) {
        this->data[h].push_back(v);
    }
};

class Solution {
public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        map<int, vector<vector<int>>> m; // last_num -> vectors
        vector<vector<int>> new_seqs;
        VectorSet vs;
        vector<int> empty;
        for (int num : nums) {
            int new_add_number = 0;
            for (auto &kv : m) {
                if (kv.first > num) break;
                for (auto& v : kv.second) {
                    auto exist = vs.exist_v_add_one(v, num);
                    if (!exist.first) {
                        vector<int> seq{v}; // do copy
                        seq.push_back(num);
                        new_seqs.push_back(move(seq));
                        vs.put(new_seqs[new_seqs.size()-1], exist.second);
                        new_add_number++;
                    }
                }
            }
            auto exist = vs.exist_v_add_one(empty, num);
            if (!exist.first) {
                new_seqs.emplace_back(1, num);
                vs.put(new_seqs[new_seqs.size()-1], exist.second);
                new_add_number++;
            }

            auto it = --new_seqs.end();
            for (int i = 0; i < new_add_number; i++) {
                m[num].push_back(*it);
            }
        }
        
        vector<vector<int>> results;
        for (auto &kv : m) {
            for (auto &v : kv.second) {
                if (v.size() > 1) {
                    results.push_back(move(v));
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