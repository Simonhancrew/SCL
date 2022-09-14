#include <algorithm>
#include <iostream>

using namespace std;
using LL = long long;
//欧拉函数的证明用到了容斥原理
// 1 给数分解质因数，然后拿到所有的质因子
// 2 利用公式算结果

#if 0
int main(){
    int n;
    cin >> n;
    while(n--){
        int a;
        cin >> a;
        int res = a;
        for(int i = 2;i <= a / i;i++){
            if(a % i == 0){
                res = res / i *(i - 1);
                while(a % i == 0) a /= i;
            }
        }
        if(a > 1) res = res / a * (a - 1);
        cout << res << endl;
    }
    return 0;
}
#endif

// 先找到所有的约数，然后用公式算，加入res,再把这个数除完
LL phi(LL x) {
  LL res = x;
  for (LL i = 2; i <= x / i; i++) {
    if (x % i == 0) {
      // 先除再乘可以避免一定的爆int的问题，如果数据范围是2e9范围内的话
      res = res / i * (i - 1);
      while (x % i == 0) x /= i;
    }
  }
  if (x > 1) res = res / x * (x - 1);
  return res;
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    LL a;
    cin >> a;
    cout << phi(a) << endl;
  }
}