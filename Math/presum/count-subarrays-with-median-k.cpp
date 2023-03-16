#include <iostream>
#include <unordered_map>

using namespace std;

// 数组有n个不同的数， from 1-n, 找到中位数为k的子数组(连续)的个数
// 因为只有一个k， 所以可以考虑部分和
// 这里的将大于k的数看作1， <=的看作-1
// 对于在k或者k之后的位置j。 需要找到一个区间[i + 1, j], 这段区间的和是0或者是-1
// 前向遍历的过程中用哈希表记录出现的前缀和
// 特殊处理一下前缀和是0的数目， 起始是1

const int N = 1e5 + 10;

int n, k;
int arr[N];

void fast_cin() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
}


int main() {
  fast_cin();
  freopen("input.txt", "r", stdin);
  cin >> n >> k;
  int s = 0;
  bool f = false;
  unordered_map<int, int> mp;
  mp[0] = 1;
  int ans = 0;
  for (int i = 0;i < n;i++) {
    cin >> arr[i];
    s += (arr[i] > k) ? 1 : -1;
    if (arr[i] == k) f = true;
    if (f) ans += mp[s] + mp[s + 1];
    else ++mp[s];
  }
  cout << ans << endl;
  return 0;
}

