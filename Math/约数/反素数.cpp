#include <algorithm>
#include <cstring>
#include <iostream>

// Created by Simonhancrew on 2022/03/14

using namespace std;

/*
    等价于求出前n个数中，约数个数最多的数里的最小数
    反向考虑，乘出这个数。发现能用的质因子其实不多。乘到29就爆int了
    其次，幂次一定递减，不然存在情况更小的数存在相同约数
    幂最大就是30
*/

typedef long long LL;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

int n;
int primes[9] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
int number, maxd;  // 确定答案的数，当且约数个数

// 当前搜索到质数数组的哪一位，前一位的幂次，当前的数，质因子个数
void dfs(int u, int c, int p, int s) {
  if (s > maxd || s == maxd && p < number) {
    number = p;
    maxd = s;
  }
  if (u == 9) return;
  for (int i = 1; i <= c; i++) {
    if ((LL)p * primes[u] > n) break;
    p *= primes[u];
    dfs(u + 1, i, p, s * (i + 1));  // 乘一个pow(x,n)之后的约数变化为
  }
}

int main() {
  fast_cin();
  cin >> n;
  dfs(0, 30, 1, 1);  // 1 << 31 > 2e9
  cout << number << endl;
  return 0;
}

/*
package main

import (
    "os"
    "bufio"
    ."fmt"
)

var n,number,maxd int
var primes = [9]int{2, 3, 5, 7, 11, 13, 17, 19, 23}

func dfs(idx,last,cur,cnt int) {
    if cnt > maxd || cnt == maxd && cur < number {
        number = cur
        maxd = cnt
    }
    if idx >= 9 {
        return
    }
    for i := 1;i <= last;i++ {
        if cur * primes[idx] > n {
            break
        }
        cur *= primes[idx]
        dfs(idx + 1,i,cur,cnt * (i + 1))
    }
}

func main(){
    in := bufio.NewReader(os.Stdin)
    out := bufio.NewWriter(os.Stdout)
    defer out.Flush()
    Fscan(in,&n)
    dfs(0,30,1,1)
    Fprint(out,number)
}
*/