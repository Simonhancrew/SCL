#include <algorithm>
#include <cstring>
#include <iostream>

// Created by Simonhancrew on 2022/03/07

using namespace std;

/*
    比较经典的枚举方式，正着想很难就倒着想试试
    先枚举质因子，之后看看这个质因子的次数
    针对质因子的次数
    [1,n]中，
    p的倍数： n / p
    p ** 2 的倍数： n / (p ** 2)
    最后做一个累加就可以了
*/

typedef long long LL;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 1e6 + 10;

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
  cin >> n;
  get_prime(n);
  for (int i = 0; i < cnt; i++) {
    int p = primes[i];
    int s = 0;
    for (int j = n; j; j /= p) s += j / p;
    cout << p << ' ' << s << endl;
  }
  return 0;
}