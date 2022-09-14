#include <algorithm>
#include <cstring>
#include <iostream>

// Created by Simonhancrew on 2022/03/06

using namespace std;

/*
    具有一定的特殊性，初看是一个二分图的问题，但是实际分析
    其实就是一个素数集合连向合数集合，所以看看n什么时候结果是2
    什么时候结果是1就行了
    然后预处理一遍质数，随后分别将质数和合数的部分标记成不同颜色
*/

typedef long long LL;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 1e5 + 10;

int n;
int primes[N], cnt;
bool st[N];

void get_prime(int n) {
  for (int i = 2; i <= n; i++) {
    if (!st[i]) primes[cnt++] = i;
    for (int j = 0; primes[j] <= n / i; j++) {
      st[primes[j] * i] = true;
      if (i % primes[j] == 0) break;
    }
  }
}

int main() {
  fast_cin();
  get_prime(N - 1);
  cin >> n;
  if (n <= 2)
    cout << 1 << endl;
  else
    cout << 2 << endl;

  for (int i = 2; i <= n + 1; i++) {
    if (!st[i])
      cout << 1 << ' ';
    else
      cout << 2 << ' ';
  }
  return 0;
}