#include <algorithm>
#include <cstring>
#include <iostream>

// Created by Simonhancrew on 2022/03/16

using namespace std;

/*
    怎么样才成为第一个点？
        y = kx,k = y0 / x0
        这个y0和x0一定是互质的，这样才能成为第一个点
    等价于找数对，互质。有一个对称性
        不难考虑到欧拉函数之后做累加
*/

typedef long long LL;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int N = 1e3 + 10;

int t, n;
int primes[N], phi[N], cnt;
bool st[N];

void get_primes(int n) {
  phi[1] = 1;
  for (int i = 2; i <= n; i++) {
    if (!st[i]) {
      primes[cnt++] = i;
      phi[i] = i - 1;
    }
    for (int j = 0; primes[j] <= n / i; j++) {
      st[primes[j] * i] = true;
      if (i % primes[j] == 0) {
        phi[i * primes[j]] = phi[i] * primes[j];
        break;
      }
      phi[primes[j] * i] = phi[i] * (primes[j] - 1);
    }
  }
}

int main() {
  fast_cin();
  cin >> t;
  get_primes(N - 1);
  for (int idx = 1; idx <= t; idx++) {
    cin >> n;
    int res = 1;
    for (int i = 1; i <= n; i++) res += phi[i] * 2;
    cout << idx << ' ' << n << ' ' << res << endl;
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

const N = 1e3 + 10
var st [N]bool
var primes,phi [N]int
var cnt,t,n int

func get_primes(n int) {
    phi[1] = 1
    for i := 2;i <= n;i++ {
        if !st[i] {
            primes[cnt] = i
            cnt++
            phi[i] = i - 1
        }
        for j := 0;primes[j] <= n / i;j++ {
            st[primes[j] * i] = true
            if i % primes[j] == 0 {
                phi[i * primes[j]] = phi[i] * primes[j]
                break
            }
            phi[i * primes[j]] = phi[i] * (primes[j] - 1)
        }
    }
}

func main(){
    in := bufio.NewReader(os.Stdin)
    out := bufio.NewWriter(os.Stdout)
    defer out.Flush()

    get_primes(N - 1)
    Fscan(in,&t)
    for idx := 1;idx <= t;idx++ {
        Fscan(in,&n)
        res := 1
        for i := 1;i <= n;i++ {
            res += phi[i] * 2
        }
        Fprintln(out,idx,n,res)
    }
}
*/