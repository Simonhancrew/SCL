#include <iostream>
#include <algorithm>
#include <cstring>

// Created by Simonhancrew on 2022/03/06

using namespace std;

/*
    直接预处理所有的质数之后做一个遍历就可以了
    其中值得注意的是st数组中所有的合数都被标记过了
*/

typedef long long LL;

#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);                 \
    cout.tie(nullptr)

const int INF = 0x3f3f3f3f, N = 1e6 + 10;

int n, cnt;
int primes[N];
bool st[N];

void get_prime(int n)
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

int main()
{
    fast_cin();
    get_prime(N - 1);
    while (cin >> n, n)
    {
        for (int i = 0;; i++)
        {
            int a = primes[i];
            int b = n - a;
            if (!st[b])
            {
                cout << n << " = " << a << " + " << b << endl;
                break;
            }
        }
    }
    return 0;
}