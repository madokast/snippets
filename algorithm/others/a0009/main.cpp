#include <iostream>
#include <vector>
using namespace std;


void stack_pop(vector<int>& s1, vector<int>& s2, vector<vector<int>>& result) {
    vector<vector<int>> set1;
    size_t max_size = 0;
    if (s1.size() > 0) {// f(n-1, m)
        int pop = s1.back();
        s1.pop_back();
        if (result.size() > 0) {
            for (auto v : result) {
                v.push_back(pop);
                set1.push_back(move(v));
            }
        } else {
            set1.push_back(move(vector<int> {pop}));
        }
        stack_pop(s1, s2, set1);
        s1.push_back(pop);

        for (auto &v : set1) {
            max_size = max(max_size, v.size());
        }
        
    }

    if (s2.size() > 0) { // f(n+1, m-1)
        int pop = s2.back();
        s2.pop_back();
        s1.push_back(pop);
        stack_pop(s1, s2, result);
        s1.pop_back();
        s2.push_back(pop);
    }

    for (auto &&v : result) {
        max_size = max(max_size, v.size());
        set1.push_back(move(v));
    }

    result.clear();
    for (auto &&v : set1) {
        if (v.size() == max_size) result.push_back(move(v));
    }
    
}


int main() {
    int number;
    cin >> number;
    vector<int> trains(number);
    for (int i = 0; i < number; i++) {
        cin >> trains[number-i-1];
    }
    vector<vector<int>> indexes_list;
    vector<int> stack;
    stack_pop(stack, trains, indexes_list);
    for (auto &indexes : indexes_list) {
        for (auto &index : indexes) {
            cout << index << " ";
        }
        cout << endl;
    }
}
// 64 位输出请用 printf("%lld")

