#include <iostream>
#include <vector>
using namespace std;

void backtrack(vector<int>& inputs, vector<int>& stack, vector<int>& current, vector<vector<int>>& results) {
    if (inputs.empty() && stack.empty()) {
        results.push_back(current); // copy
        return;
    }

    if (!inputs.empty()) { // stack push
        int input = inputs.back();
        inputs.pop_back();
        stack.push_back(input);
        backtrack(inputs, stack, current, results);
        stack.pop_back();
        inputs.push_back(input);
    }

    if (!stack.empty()) { // output
        int pop = stack.back();
        stack.pop_back();
        current.push_back(pop);
        backtrack(inputs, stack, current, results);
        current.pop_back();
        stack.push_back(pop);
    }
}

int main() {
    int number;
    cin >> number;
    vector<int> trains(number);
    for (int i = 0; i < number; i++) {
        cin >> trains[number-i-1];
    }
    vector<vector<int>> results;
    vector<int> stack, current;
    backtrack(trains, stack, current, results);
    for (int i = results.size() - 1; i >= 0; i--) {
        for (auto &e : results[i]) {
            cout << e << " ";
        }
        cout << endl;
    }
}
// 64 位输出请用 printf("%lld")

