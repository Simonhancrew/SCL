#include <iostream>
#include <algorithm>
#include <cstring>

// Created by Simonhancrew on 2022/03/20

using namespace std;

/*
    ax = 1 mod b
    等价于求
        ax + by = 1
    先求出
        ax + by = gcd(a,b)
    的解x^1和y^1
    x = x^1 + k * b / d
    此时有d = 1,则x = x^1 + k * b
    找一个最小解就行了
*/

typedef long long LL;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);                 \
    cout.tie(nullptr)

const int INF = 0x3f3f3f3f;

int a, b, x, y;

int ex_gcd(int a, int b, int &x, int &y)
{
    if (b == 0)
    {
        x = 1, y = 0;
        return a;
    }
    int x1, y1;
    int gcd = ex_gcd(b, a % b, x1, y1);
    x = y1, y = x1 - a / b * y1;
    return gcd;
}

int main()
{
    fast_cin();
    cin >> a >> b;
    int res = ex_gcd(a, b, x, y);
    cout << (x + b) % b << endl;
    return 0;
}

/*
package main

import(
    "os"
    "bufio"
    ."fmt"
)

var a,b int

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
    Fscan(in,&a,&b)

    _,x,_ := ex_gcd(a,b,&x,&y)

    Fprintln(out,(x % b + b) % b)
}
*/