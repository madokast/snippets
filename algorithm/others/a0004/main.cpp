// 画展不和谐度最小化问题：
// 已知展厅有 N 幅画作，每幅画的艺术价值为整数 A₁到 Aₙ
// 需要从这些画作中选出 M 幅，并按一定顺序排列成序列 B₁到 Bₘ
// 定义不和谐度 L 为：序列中相邻两幅画价值平方差的绝对值之和
// 即 L = |B₂² - B₁²| + |B₃² - B₂²| + ... + |Bₘ² - Bₘ₋₁²|
// 目标是找到一种选法和排列方式，使不和谐度 L 的值最小，并输出这个最小值

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  int a, b;
  cin >> a >> b;
  vector<int> v;
  v.reserve(a);
  for (int i = 0; i < a; i++) {
    int temp;
    cin >> temp;
    v.push_back(temp);
  }
  sort(v.begin(), v.end());
  long long int result = 
    static_cast<long long int>(v[v.size() - 1]) * v[v.size() - 1];
  for (int i = b - 1; i < a; i++) {
    long long int first = v[i - b + 1];
    long long int end = v[i];
    long long int value = end * end - first * first;
    result = min(result, value);
  }
  cout << result << endl;
}
