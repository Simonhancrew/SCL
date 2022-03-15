#include <iostream>
#include <algorithm>
#include <cstring>

// Created by Simonhancrew on 2022/03/15

using namespace std;

/*
    第一个思路:
        gcd(a,x) = b
        lcm(c,x) = d
        枚举d的所有约数，然后gcd(a,x) == b的情况计数
    实质上，d的约数在int范围内不会超过1600，但枚举约数
    是一个sqrt(n)的操作，判断很快，但是加上所有数据
    结合给出的时间范围可能会超时
    第二个思路：
        找出d所有的质因子极其幂次，然后爆搜出d所有的约数
        约数最多1600个。然后对着1600个数做gcd和lcm的判断
*/

typedef long long LL;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);                 \
    cout.tie(nullptr)

const int N = 5e4 + 10;

int primes[N], cnt;
bool st[N];
int n, a, b, c, d;
int fcnt, dcnt;
int divisor[1601];
struct Factor
{
    int p, s;
} factor[10];

int gcd(int a, int b)
{
    return b ? gcd(b, a % b) : a;
}

int lcm(int a, int b)
{
    return (LL)a * b / gcd(a, b);
}

void get_primes(int n)
{
    for (int i = 2; i <= n; i++)
    {
        if (!st[i])
            primes[cnt++] = i;
        for (int j = 0; primes[j] <= n / i; j++)
        {
            st[primes[j] * i] = true;
            if (i % primes[j] == 0)
                break;
        }
    }
}

void dfs(int u, int p)
{
    if (u == fcnt)
    {
        divisor[dcnt++] = p;
        return;
    }
    for (int i = 0; i <= factor[u].s; i++)
    {
        dfs(u + 1, p);
        p *= factor[u].p;
    }
}

int main()
{
    fast_cin();
    get_primes(N - 1);
    cin >> n;
    while (n--)
    {
        cin >> a >> b >> c >> d;
        fcnt = 0;
        int t = d, res = 0;
        for (int i = 0; primes[i] <= t / primes[i]; i++)
        {
            int p = primes[i];
            if (t % p)
                continue;
            int s = 0;
            while (t % p == 0)
            {
                s++, t /= p;
            }
            factor[fcnt++] = {p, s};
        }
        if (t > 1)
            factor[fcnt++] = {t, 1};

        dcnt = 0;
        dfs(0, 1);

        for (int i = 0; i < dcnt; i++)
        {
            int x = divisor[i];
            if (gcd(a, x) == b && lcm(c, x) == d)
                res++;
        }
        cout << res << endl;
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

const N = 5e4 + 10

type Factor struct {
    p,s int
}

var factor [11]Factor

var n,fcnt,dcnt int
var cnt int
var divisor [1605]int
var primes [N]int
var st [N]bool

func get_primes(n int) {
    for i := 2;i <= n;i++ {
        if !st[i] {
            primes[cnt] = i
            cnt++
        }
        for j := 0;primes[j] <= n / i;j++ {
            st[primes[j] * i] = true
            if i  % primes[j] == 0 {
                break
            }
        }
    }
}

func gcd(a,b int) int {
    if b == 0 {
        return a
    }
    return gcd(b,a % b)
}

func lcm(a,b int) int {
    return a * b / gcd(a,b)
}

func dfs(u,p int) {
    if u == fcnt {
        divisor[dcnt] = p
        dcnt ++
        return
    }
    for i := 0;i <= factor[u].s;i++ {
        dfs(u + 1,p)
        p *= factor[u].p
    }
}


func main(){
    in := bufio.NewReader(os.Stdin)
    out := bufio.NewWriter(os.Stdout)
    defer out.Flush()
    Fscan(in,&n)
    get_primes(N - 1)
    for n > 0 {
        cnt,fcnt,dcnt = 0,0,0
        var a,b,c,d,res,t int
        Fscan(in,&a,&b,&c,&d)
        t = d
        for i := 0;primes[i] <= t / primes[i];i++ {
            p := primes[i]
            if t % p != 0 { continue }
            s := 0
            for t % p == 0 {
                s++
                t /= p
            }

            factor[fcnt] = Factor{p,s}
            fcnt++
        }

        if t > 1 {
            factor[fcnt] = Factor{t,1}
            fcnt++
        }

        dfs(0,1)

        for i := 0;i < dcnt;i++ {
            x := divisor[i]
            if gcd(a,x) == b && lcm(c,x) == d {
                res++
            }
        }

        Fprintln(out,res)

        n--
    }
}
*/