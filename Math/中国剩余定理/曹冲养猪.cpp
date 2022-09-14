#include <algorithm>
#include <cstring>
#include <iostream>

// Created by Simonhancrew on 2022/03/21

/*
    中国剩余定理的裸题
    x = a[i] % m[i]
    M = m[i] * ... * m[i]
    M[i] = M / m[i]
    (M[i] * t[i]) % m[i] = 1 % m[i]
    x = sum(a[i] * M[i] * t[i])
*/

using namespace std;

typedef long long LL;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int N = 11;

int a[N], m[N];
int n;

void ex_gcd(LL a, LL b, LL &x, LL &y) {
  if (!b) {
    x = 1, y = 0;
    return;
  } else {
    ex_gcd(b, a % b, y, x);
    y -= a / b * x;
  }
}

int main() {
  fast_cin();
  cin >> n;
  LL M = 1;
  for (int i = 0; i < n; i++) {
    cin >> m[i] >> a[i];
    M *= m[i];
  }
  LL res = 0;
  for (int i = 0; i < n; i++) {
    LL Mi = M / m[i];
    LL ti, t;
    ex_gcd(Mi, m[i], ti, t);
    res += Mi * ti * a[i];
  }
  cout << (res % M + M) % M << endl;
  return 0;
}

/*
package main

import (
    "os"
    "bufio"
    ."fmt"
)

const N = 11
var n int
var m,a [N]int

func ex_gcd(a,b int) (ans,x,y int) {
    if b == 0 {
        return a,1,0
    }
    ans,y,x = ex_gcd(b,a % b)
    y -= a / b * x
    return ans,x,y
}

func main(){
    in := bufio.NewReader(os.Stdin)
    out := bufio.NewWriter(os.Stdout)
    defer out.Flush()
    Fscan(in,&n)
    M := 1
    for i := 0;i < n;i++ {
        Fscan(in,&m[i],&a[i])
        M *= m[i]
    }

    res := 0
    for i := 0; i < n;i++ {
        Mi := M / m[i]
        _,ti,_ := ex_gcd(Mi,m[i])
        res += a[i] * Mi * ti
    }
    Fprintln(out,(res % M + M) % M)
}

*/