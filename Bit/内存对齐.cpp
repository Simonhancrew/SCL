#include <iostream>

using namespace std;

// x 对 a 对齐，先 + ，之后利用低位取0

int align(int x, int a) {
  int add = (x + a - 1);  // 类似于ceiling的操作，(x + a - 1) / a
  int lowzero = ~(a - 1);  // 此时，最低位1之后的为全0，之前的最低位1不变
  return (x + a - 1) & (~(a - 1));
}

int main() {
  int x, a;
  cin >> x >> a;
  cout << align(x, a) << endl;
  return 0;
}