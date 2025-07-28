#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        if (text1.size() < text2.size()) swap(text1, text2);

        size_t length1Add = text1.size() + 1;
        size_t length2Add = text2.size() + 1;

        // cout << length1Add << " " << length2Add << endl;

        int* base = new int[length2Add * 2];
        memset(base, 0, sizeof(int) * (length2Add + 1));
        int* dp0 = base;
        int* dp1 = base + length2Add;
        
        int longest = 0;
        
        for (char c1:text1) {
            for (size_t j = 1; j < length2Add; j++) {
                char c2 = text2[j-1];
                if (c1 == c2) {
                    // dp(i, j) = dp(i-1, j-1) + 1;
                    dp1[j] = dp0[j-1] + 1;
                } else {
                    // dp(i, j) = max dp(i, j-1) dp(i-1, j);
                    dp1[j] = max(dp1[j-1], dp0[j]);
                }
                // cout << c1 << c2 << dp1[j] << " " << dp1[j-1] <<  " " << dp0[j] << endl;
                longest = max(longest, dp1[j]);
            }
            swap(dp0, dp1);
            // memset(dp1, 0, sizeof(int) * (length2Add));
            // dp1[0] = 0;
        }

        // for_each(base, base+(length2Add * 2), [](int a) {cout << a << " ";});
        // cout << endl;

        delete[] base;
        return longest;
    }
};


#include<cassert>

int main() {
    Solution s;
    {
        int length = s.longestCommonSubsequence("abcde", "ace");
        cout << length << endl;
        assert(length == 3);
    }
    {
        int length = s.longestCommonSubsequence("hofubmnylkra", "pghgxgdofcvmr");
        cout << length << endl;
        assert(length == 5);
    }
}

