/*
# 智能代码编辑器的光标删除操作问题

在一款智能代码编辑器中，光标用字符 `I` 表示。初始时给出一个只包含字符 `(`、`)`、`I` 的括号串，其中恰好出现一次 `I` 作为光标位置。编辑器支持下列两种删除操作：

1. **backspace**：
   - 若光标左侧字符为 `(`，且光标右侧紧跟字符为 `)`，编辑器会一次性删除这对括号；
   - 否则，若光标左侧仍有字符，则仅删除光标左侧一个字符；若左侧为空则无效果。

2. **delete**：
   - 若光标右侧存在字符，则删除光标右侧第一个字符；否则无效果。

给定初始括号串以及 `k` 次操作序列（每次为 backspace 或 delete），请输出全部操作执行完毕后的最终字符串。


## 输入描述
- 第一行输入两个整数 n,k（1 <= k <= n <= 2e5）——初始字符串长度及操作次数。
- 第二行输入长度为 n 的字符串 s，仅包含 `(`, `)` 与 `I`，其中 `I` 恰好出现一次。
- 接下来 k 行，每行输入一个操作类型：`backspace` 或 `delete`。


## 输出描述
输出一行字符串，表示所有操作结束后的括号串。


## 补充说明

### 示例1
**输入例子：**
```
10 3
((()(I))((
backspace
backspace
delete
```

**输出例子：**
```
(((I((
```


### 示例2
**输入例子：**
```
5 3
((I))
backspace
backspace
delete
```

**输出例子：**
```
I
```

**例子说明：** 显然括号都被删除完了。
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<char> s;
    s.reserve(n);
    int left, right;
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        if (c == 'I') {
            left = i-1;
            right = i+1;
        }
        s.push_back(c);
    }
    string op;
    for (int i = 0; i < k; i++) {
        cin >> op;
        if (op[0] == 'b') {
            if (left >= 0) {
                if (s[left] == '(' && right < n && s[right] == ')') {
                    left--;
                    right++;
                } else {
                    left--;
                }
            }
        } else {
            if (right < n) {
                right++;
            }
        }
        op.clear();
    }
    
    if (left >= 0) cout.write(&s[0], left+1);
    cout << 'I';
    if (right < n) cout.write(&s[right], n-right);
    cout << endl;
}
// 64 位输出请用 printf("%lld")