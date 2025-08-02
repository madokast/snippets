#include<vector>
#include<map>
#include<unordered_map>
using namespace std;

// bool v_eq(vector<int>& v1, vector<int>& v2) {
//     if (v1.size() != v2.size()) return false;
//     for (size_t i = 0; i < v1.size(); i++) {
//         if (v1[i] != v2[i]) return false;
//     }
//     return true;
// }

// v1 == v2+[num]
bool v_eq_add_one(vector<int>& v1, vector<int>& v2, int num) {
    if (v1.size() != v2.size()+1) return false;
    if (v1[v1.size()-1] != num) return false;
    for (size_t i = 0; i < v2.size(); i++) {
        if (v1[i] != v2[i]) return false;
    }
    return true;
}

using hashed = unsigned int;

// hashed v_hash(vector<int>& v) {
//     if (v.empty()) return 0;
//     hashed h = 1;
//     for (int e : v) {
//         h = 31 * h + static_cast<hashed>(e);
//     }
//     return h;
// }

// hashed v_hash_add_one(vector<int>& v, int num) {
//     hashed h = 1;
//     for (int e : v) {
//         h = 31 * h + static_cast<hashed>(e);
//     }
//     h = 31 * h + static_cast<hashed>(num);
//     return h;
// }

hashed v_hashed_add_one(hashed h, int num) {
    return 31 * h + static_cast<hashed>(num);
}

void try_put_one_num(unordered_map<hashed, vector<vector<int>>>& hash_vs, int num) {
    hashed h = 1;
    h = 31 * h + static_cast<hashed>(num);

    auto& vvs = hash_vs[h];
    for (auto &vs : vvs) {
        if (vs.size() == 1) return;
    }
    vvs.emplace_back(1, num);
}

bool exist(unordered_map<hashed, vector<vector<int>>>& hash_vs, vector<int>& v, int num, hashed h) {
    auto it = hash_vs.find(h);
    if (it == hash_vs.end()) return false;
    for (auto &hv : (*it).second) {
        if (v_eq_add_one(hv, v, num)) return true;
    }
    return false;
}


class Solution {
public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        map<int, unordered_map<hashed, vector<vector<int>>>> m; // end number -> hash -> vectors
        for (int num : nums) {
            auto& num_end_map = m[num];
            vector<pair<hashed, vector<int>>> new_seqs;
            new_seqs.reserve(64);
            for (auto &end_map : m) {
                if (end_map.first > num) break;
                for (auto& hash_vs : end_map.second) {
                    for (auto &v : hash_vs.second) {
                        // hashed new_hash = v_hash_add_one(v, num);
                        hashed new_hash = v_hashed_add_one(hash_vs.first, num);
                        if (!exist(num_end_map, v, num, new_hash)) {
                            vector<int> new_seq = v;
                            new_seq.push_back(num);
                            new_seqs.push_back(move(make_pair(new_hash, move(new_seq))));
                        }
                    }
                }
            }
            
            try_put_one_num(num_end_map, num);            
            for (auto &&h_vs : new_seqs) {
                num_end_map[h_vs.first].push_back(move(h_vs.second));   
            }
            
        }
        
        vector<vector<int>> results;
        for (auto &&end_map : m) {
            for (auto &&hash_vs : end_map.second) {
                    for (auto &&v : hash_vs.second) {
                        if (v.size() > 1) {
                        results.push_back(move(v));
                    }
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

void printMap(unordered_map<hashed, vector<vector<int>>>& m) {
    for (auto &&kv : m)
    {
        cout << kv.first << "->" << kv.second.size() << ":";
        for (auto &&v : kv.second) {
            printVector(v);
        }
    }
    cout << "map" << endl;
}

int main() {
    Solution s;
    vector<int> v = {4, 6, 7, 7};
    auto vv = s.findSubsequences(v);
    for (auto &&i : vv) {
        printVector(i);
    }
    
}