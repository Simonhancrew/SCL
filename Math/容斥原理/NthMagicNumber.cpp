#include <iostream>

// from lc 878

using namespace std;
using LL = long long;

// 容斥原理，一个数能被a和b整除，找到所有的数
// 做一个容斥原理，等价于tar / a + tar / b - tar / lcm(a, b)
// 随后针对所有的数范围做一个二分就可以了，假设a更大的话，最大的n可以取4e4 * 1e9

const int P = 1e9 + 7;
int a, b, n;

int gcd(int, int);

int lcm(int a,int b) {
  return a * b / gcd(a, b);
}

LL get(LL tar, int a, int b) {
  return tar / a + tar / b - tar / lcm(a, b);
}

int gcd(int a,int b) {
  return b ? gcd(b, a % b): a;
}

int main() {
  cin >> n >> a >> b;
  LL l = 0, r = 4e13;
  while(l < r) {
    LL mid = (l + r) >> 1;
    if(get(mid, a, b) >= n) r = mid;
    else l = mid + 1;
  }
  cout << l % P;
  return 0;
}
