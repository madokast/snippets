#include <iostream>
#include <string>
using namespace std;

int main() {
    int n;
    cin >> n;
    for (int index = 0; index < n; index++) {
        string s, p;
        cin >> s >> p;

        int i = 0, j = 0;
        while (i < s.size() && j < p.size()) {
            if (s[i] == p[j]) {
                i++;
                j++;
            } else if (s[i] == '?') {
                s[i] = p[j];
                i++;
                j++;
            } else {
                i++;
            }
        }
        if (j == p.size()) {
            while (i < s.size()) {
                if (s[i] == '?') {
                    s[i] = 'a';
                }
                i++;
            }
            cout << "YES" << endl;
            cout << s << endl;
        }  else {
            cout << "NO" << endl;
        }
    }
}
// 64 位输出请用 printf("%lld")
