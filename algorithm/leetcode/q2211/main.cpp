#include<string>
#include<vector>
#include<algorithm>
#include<iostream>
#include<cassert>
using namespace std;

class Solution {
public:
    int countCollisions(string directions) {
        const char L = 'L';
        const char R = 'R';
        const char S = 'S';

        int count = 0;

        vector<char> stack;
        for (const char ch : directions) {
            switch (ch)
            {
            case L:
                if (!stack.empty()) {
                    char pop = *(stack.end()-1);
                    stack.pop_back();
                    switch (pop) {
                    case R:
                        count+=2;
                        count+=stack.size();
                        for_each(stack.cbegin(), stack.cend(), [](char c){assert(c=='R');});
                        stack.clear();
                        break;
                    case S:
                        count+=1;
                        assert(stack.empty());
                        break;
                    default:
                        assert(false);
                        break;
                    }
                    assert(stack.empty());
                    stack.push_back(S);
                }
                
                break;
            case R:
                if (!stack.empty()) {
                    char last = *(stack.end()-1);
                    if (last == S) {
                        assert(stack.size()==1);
                        stack.clear();
                    }
                }
                stack.push_back(R);
                break;
            default: // S
                if (!stack.empty()) {
                    char last = *(stack.end()-1);
                    switch (last) {
                    case R:
                        for_each(stack.cbegin(), stack.cend(), [](char c){assert(c=='R');});
                        count += stack.size();
                        stack.clear();
                        stack.push_back(S);
                        break;
                    case S:
                        assert(stack.size()==1);
                        break;
                    default:
                        assert(false);
                        break;
                    }
                } else {
                    stack.push_back(S);
                }
            }

            // cout << ch << " [" << stack.size() << ":";
            // for_each(stack.cbegin(), stack.cend(), [](char c){cout<<c;});
            // cout << " " << count << endl;
        }
        
        // cout << directions << ':' << count << endl;
        return count;
    }
};



int main() {
    Solution s;
    assert(s.countCollisions("") == 0);
    assert(s.countCollisions("LLL") == 0);
    assert(s.countCollisions("SSS") == 0);
    assert(s.countCollisions("RRR") == 0);
    assert(s.countCollisions("LR") == 0);
    assert(s.countCollisions("LLLSRRRR") == 0);
    assert(s.countCollisions("RS") == 1);
    assert(s.countCollisions("RSS") == 1);
    assert(s.countCollisions("RRSS") == 2);
    assert(s.countCollisions("RRLS") == 3);
    assert(s.countCollisions("LLRR") == 0);
    assert(s.countCollisions("RLRSLL") == 5);
    assert(s.countCollisions("LSSSLLSSSSLRRSLLLSLSLRRLLLLLRSSRSRRSLLLSSS") == 24);

}
