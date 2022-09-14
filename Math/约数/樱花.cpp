#include <algorithm>
#include <cstring>
#include <iostream>

// Created by Simonhancrew on 2022/03/10

using namespace std;

/*
    1 / x + 1 / y = 1 / n!
    用y表示x,固定x是一个正整数的话
    y = (n! * x) / (x - n!)
      = (n! * (x - n! + n!)) / (x - n!)
      = n! + (n! * n!) / (x - n!)
    不难知道x一定要大于n!
    就等于求n! * n!有多少个约数
    可以借助之前的约数个数公式直接求得
    （c1 + 1） * (c2 + 1 ) * (c3 + 1) * ... * (cn + 1)
    cn是质因子的次数
    之前做一个阶乘分解
*/

typedef long long LL;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int P = 1e9 + 7, N = 1e6 + 10;

int n;
int primes[N], st[N], cnt;

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

  int res = 1;
  for (int i = 0; i < cnt; i++) {
    int s = 0, p = primes[i];
    for (int j = n; j; j /= p) {
      s += j / p;
    }
    res = (LL)res * (2 * s + 1) % P;
  }
  cout << res << endl;
  return 0;
}