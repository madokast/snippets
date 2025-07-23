#include<vector>
#include<string>
#include<iostream>
using namespace std;

class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        vector<string> results;
        if (s.size() <= 10) return results;

        vector<bool> flags(1<<20, false);
        vector<bool> output(1<<20, false);

        size_t represent = 0;
        for (size_t i = 0; i < 10; i++) {
            represent <<= 2;
            char c {s[i]};
            if (c == 'A')      represent |= 0x0;
            else if (c == 'C') represent |= 0x1;
            else if (c == 'G') represent |= 0x2;
            else               represent |= 0x3;

            // cout << represent << endl;
        }

    
        flags[represent] = true;
        for (size_t i = 10; i < s.size(); i++) {
            represent <<= 2;
            represent &= (1<<20) - 1;
            char c {s[i]};
            if (c == 'A')      represent |= 0x0;
            else if (c == 'C') represent |= 0x1;
            else if (c == 'G') represent |= 0x2;
            else               represent |= 0x3;
            
            // cout << s.substr(i-10, 10) << "-" << represent << endl;

            if (flags[represent] && !output[represent]) {
                results.push_back(s.substr(i-9, 10));
                output[represent] = true;
            }
            
            flags[represent] = true;
        }
        
        return results;
    }
};


int main() {
    string s {"AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"};
    auto results = Solution().findRepeatedDnaSequences(s);
    for (size_t i = 0; i < results.size(); i++) {
        cout << results[i] << endl;
    }
    
}