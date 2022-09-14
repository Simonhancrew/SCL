#include <algorithm>
#include <cstring>
#include <iostream>

// Created by Simonhancrew on 2022/03/20

using namespace std;

/*
    青蛙A从a出发跳m，B从b出发跳n，环形总长L,可以有一个追赶公式：
        (b - a) + L * y = (m - n) * x
        (m - n) x + L(-y) = (b - a)
    出现了一个一般求解同余方程
*/

typedef long long LL;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

LL a, b, m, n, L;

LL ex_gcd(LL a, LL b, LL &x, LL &y) {
  if (b == 0) {
    x = 1, y = 0;
    return a;
  }
  LL d = ex_gcd(b, a % b, y, x);
  y -= a / b * x;
  return d;
}

int main() {
  fast_cin();
  cin >> a >> b >> m >> n >> L;
  LL x, y;
  LL d = ex_gcd(m - n, L, x, y);
  if ((b - a) % d)
    cout << "Impossible" << endl;
  else {
    x *= (b - a) / d;
    LL t = abs(L / d);
    cout << (x % t + t) % t << endl;
  }
  return 0;
}

/*
package main

import(
    "os"
    "bufio"
    ."fmt"
)

var m,n,a,b,L int

func ex_gcd(a,b int) (gcd,x,y int) {
    if b == 0 {
        return a,1,0
    }
    gcd,y,x = ex_gcd(b,a % b)
    y -= a / b * x
    return
}

func main(){
    in := bufio.NewReader(os.Stdin)
    out := bufio.NewWriter(os.Stdout)
    defer out.Flush()

    Fscan(in,&a,&b,&m,&n,&L)
    d,x,_ := ex_gcd(m - n,L)
    if (b - a) % d != 0 {
        Fprintln(out,"Impossible")
    }else{
        x *= (b - a) / d
        t := L / d
        if t < 0 {
            t = -t
        }
        Fprintln(out,(x % t + t) % t)
    }
}
*/