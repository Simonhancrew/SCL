#include <algorithm>
#include <cstring>
#include <iostream>

// Created by Simonhancrew on 2022/03/21

using namespace std;

/*
    做一个公式转换
        L | 8.....8 => L | 8 * (9...9) / 9
    =>  L | (pow(10,x) - 1) / 9 * 8
    =>  9 * L | 8 * (pow(10,x) - 1)
    因为gcd(8,9) = 1,所以gcd(L,8) = d
    gcd(L / d,8 / d) = 1,这两个数一定是互质的
    所以9 * L / d一定是pow(10,x) - 1的因子
    9 * L / d | pow(10,x) - 1
    恒等变形
    pow(10,x) = 1 % (9 * L / d)
    很类似一个欧拉定理
    pow(a,phi(m)) = 1 mod m,gcd(a,m) = 1;
    x一定是phi(m)的因子，求出最小的满足要求因子就可以了
*/

typedef long long LL;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f;

LL l;

LL gcd(LL a, LL b) { return b ? gcd(b, a % b) : a; }

// 试除法求欧拉函数
LL get_euler(LL c) {
  LL res = c;
  for (int i = 2; i <= c / i; i++) {
    if (c % i == 0) {
      while (c % i == 0) c /= i;
      res = res / i * (i - 1);
    }
  }
  if (c > 1) res = res / c * (c - 1);
  return res;
}

// a * b爆LL的龟速乘
LL qmul(LL a, LL b, LL p) {
  LL res = 0;
  while (b) {
    if (b & 1) res = (res + a) % p;
    b >>= 1;
    a = (a + a) % p;
  }
  return res;
}

// 快速幂
LL qmi(LL a, LL b, LL p) {
  LL res = 1;
  while (b) {
    if (b & 1) res = qmul(res, a, p);
    b >>= 1;
    a = qmul(a, a, p);
  }
  return res;
}

int main() {
  fast_cin();
  int t = 1;
  while (cin >> l, l) {
    int d = gcd(l, 8);
    // cout << d << ' ';
    LL c = 9 * l / d;
    LL phi = get_euler(c);

    LL res = 2e18;
    // cout << c << ' ' << phi << endl;
    if (c % 2 == 0 || c % 5 == 0)
      res = 0;
    else {
      for (LL i = 1; i <= phi / i; i++) {
        if (phi % i == 0) {
          if (qmi(10, i, c) == 1) res = min(res, i);
          if (qmi(10, phi / i, c) == 1) res = min(res, phi / i);
        }
      }
    }
    cout << "Case " << t << ": " << res << endl;
    ++t;
  }
  return 0;
}

/*
package main

import (
    "os"
    "bufio"
    ."fmt"
)

var l int

func gcd(a,b int) int {
    if b != 0 {
        return gcd(b,a % b)
    }
    return a
}

func get_euler(c int) int {
    res := c
    for i := 2;i <= c / i;i++ {
        if c % i == 0 {
            for c % i == 0 {
                c /= i
            }
            res = res / i * (i - 1)
        }
    }
    if c > 1 {
        res = res / c * (c - 1)
    }
    return res
}
func qmul(a,b,p int) int {
    res := 0
    for b != 0 {
        if b & 1 == 1 {
            res = (res + a) % p
        }
        b >>= 1
        a = (a + a) % p
    }
    return res
}
func qmi(a,b,p int) int {
    res := 1
    for b != 0 {
        if b & 1 == 1 {
            res = qmul(res,a,p)
        }
        b >>= 1
        a = qmul(a,a,p)
    }
    return res
}

func min(a,b int) int {
    if a < b {
        return a
    }
    return b
}

func main(){
    in := bufio.NewReader(os.Stdin)
    out := bufio.NewWriter(os.Stdout)
    defer out.Flush()
    t := 1
    for {
        Fscan(in,&l)
        if l == 0 {
            break
        }
        d := gcd(l,8)
        c := 9 * l / d
        phi,res := get_euler(c),int(2e18)
        // Fprintln(out,d,c,phi)
        if(c % 2 == 0 || c % 5 == 0) {
            res = 0
        }else{
            for i := 1;i <= phi / i;i++ {
                if(phi % i == 0) {
                    // Fprintln(out,i)
                    if(qmi(10,i,c) == 1) { res = min(res,i) }
                    if(qmi(10,phi / i,c) == 1) { res = min(res,phi / i) }
                }
            }
        }
        Fprintf(out,"Case %d: %d\n",t,res)
        t++
    }
}
*/