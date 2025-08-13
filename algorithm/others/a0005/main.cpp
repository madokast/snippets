/** 
 * 给一个正整数数组，将其分割为 3 个**非空**的部分 `[0:i) [i:j) [j:)`，
 * 要求三部分的元素分别求和后，中间部分最大。问解的数目是多少。
 * 
 * 例子 `[1,2,3,4,5]` 解数目 2。
 * 
 * 数组长度最大 `1e-5`，说明平方复杂度的算法会超时。
 */

#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    vector<int> v;
    v.reserve(n);
    long long int sum = 0;
    for (int i = 0; i < n; i++) {
        int t;
        cin >> t;
        sum += t;
        v.push_back(t);
    }
    
    int i = 1, j = n-1;
    long long int left = v[0], right = v[n-1];
    long long int middle = sum - left - right;

    // 寻找 i=1 时，最小的 j
    for(;;) {
        if (middle > left && middle > right) {
            j--;
            right += v[j];
            middle -= v[j];
            if (!(i<j)) break;
        } else break;
    }
    
    // 找到的 j 已经是不满足的了，大于的就是解
    long long int result = n-j-1;

    // 如果 result 是 0 不用往下找了
    if (result == 0) goto exit;

    // 现在增大 i，让 j 也增大到有解
    for(;;) {
        left += v[i];
        middle -= v[i];
        i++;
        while(!(middle > left && middle > right)) {
            right -= v[j];
            middle += v[j];
            j++;
            if (j == n) goto exit;
        }
        // 现在 j 是合法的，找到解数目
        result += n-j;
    }

    exit:
    cout << result << endl;
    return 0;
}
