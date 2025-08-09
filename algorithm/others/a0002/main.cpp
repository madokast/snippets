/*对于给定的由大小写字母和数字组成的字符串，请按照 ASCII 码值将其从小到大排序。
 */

#include <iostream>
#include <cstring>
using namespace std;

int buckets[256];

int main() {
    string s;
    while (cin >> s) { // 注意 while 处理多个 case
        memset(buckets, 0, sizeof(int) * 256);
        for (char c : s) buckets[c] += 1;
        for (size_t i = 0; i < 256; i++) {
            for (size_t j = 0; j < buckets[i]; j++) {
                cout << char(i);
            }
        }
        cout << endl;
        s.clear();
    }
}
// 64 位输出请用 printf("%lld")