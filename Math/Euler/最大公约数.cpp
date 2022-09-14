#include <algorithm>
#include <cstring>
#include <iostream>

// Created by Simonhancrew on 2022/03/17

using namespace std;

/*
    等价变化一下：
        gcd(x,y) = pirme
        gcd(x / prime,y / prime) = 1
        求在[1,n / primes]的范围内有多少互质的数对
        其中n / primes下取整
*/

typedef long long LL;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int N = 1e7 + 10;

int n;
int primes[N], cnt;
bool st[N];
int phi[N];
LL s[N];

void get_primes(int n) {
  phi[1] = 0;
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
      phi[i * primes[j]] = phi[i] * (primes[j] - 1);
    }
  }
  for (int i = 1; i <= n; i++) s[i] = s[i - 1] + phi[i];
}

int main() {
  fast_cin();
  cin >> n;
  get_primes(n);
  LL res = 0;
  for (int i = 0; i < cnt; i++) {
    int p = primes[i];
    res += s[n / p] * 2 + 1;
  }
  cout << res << endl;
  return 0;
}

/*
package main

import(
    "os"
    "bufio"
    ."fmt"
)
const N = 1e7 + 10
var n,cnt int
var primes,phi,s [N]int
var st [N]bool

func get_primes(n int) {
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
    for i := 1;i <= n;i++ {
        s[i] = s[i - 1] + phi[i]
    }
}

func main(){
    in := bufio.NewReader(os.Stdin)
    out := bufio.NewWriter(os.Stdout)
    defer out.Flush()
    Fscan(in,&n)
    get_primes(n)
    res := 0
    for i := 0;i < cnt;i++ {
        p := primes[i]
        res += s[n / p] * 2 + 1
    }
    Fprintln(out,res)
}
*/