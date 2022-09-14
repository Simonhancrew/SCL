#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

// Created by Simonhancrew on 2022/03/21

using namespace std;

/*
    f = [fib(n),fib(n + 1),sum(n)]
    target = f * pow(A,n - 1)
    A = {
        {0, 1, 0},
        {1, 1, 1},
        {0, 0, 1}
    }
*/

typedef long long LL;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int N = 3;
int n, m;

void mul(int c[], int a[], int b[][N]) {
  int tmp[N] = {0};
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      tmp[i] = (tmp[i] + (LL)a[j] * b[j][i]) % m;
    }
  }
  memcpy(c, tmp, sizeof tmp);
}

void mul(int c[][N], int a[][N], int b[][N]) {
  int tmp[N][N] = {0};
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      for (int k = 0; k < N; k++) {
        tmp[i][j] = (tmp[i][j] + (LL)a[i][k] * b[k][j]) % m;
      }
    }
  }
  memcpy(c, tmp, sizeof tmp);
}

int main() {
  fast_cin();
  cin >> n >> m;
  int f[N] = {1, 1, 1};
  int a[N][N] = {{0, 1, 0}, {1, 1, 1}, {0, 0, 1}};
  --n;
  while (n) {
    if (n & 1) mul(f, f, a);
    mul(a, a, a);
    n >>= 1;
  }
  cout << f[2] << endl;
  return 0;
}

/*
package main

import (
    "os"
    "bufio"
    ."fmt"
)

var m,n int
const N = 3

func mul(a []int,b [][]int) []int {
    tmp := []int{0,0,0}
    for i := 0;i < N;i++ {
        for j := 0;j < N;j++{
            tmp[i] = (tmp[i] + a[j] * b[j][i]) % m
        }
    }
    return tmp
}

func mul2(a,b [][]int) [][]int {
    tmp := make([][]int,N)
    for i := 0;i < N;i++ {
        tmp[i] = make([]int,N)
    }
    for i := 0;i < N;i++ {
        for j := 0;j < N;j++ {
            for k := 0;k < N;k++ {
                tmp[i][j] = (tmp[i][j] + a[i][k] * b[k][j]) % m
            }
        }
    }
    return tmp
}

func main(){
    in := bufio.NewReader(os.Stdin)
    out := bufio.NewWriter(os.Stdout)
    defer out.Flush()
    Fscan(in,&n,&m)
    f := []int{1,1,1}
    a := [][]int {
        {0,1,0},
        {1,1,1},
        {0,0,1},
    }
    n--
    for n != 0 {
        if n & 1 == 1 {
            f = mul(f,a)
        }
        n >>= 1
        a = mul2(a,a)
        // Fprintln(out,a)
    }
    Fprintln(out,f[2])
}
*/