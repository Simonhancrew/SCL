#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
using LL = long long;

// 组合数，脑筋急转弯 

const int mod = 1e9 + 7;
const int N = 1e4 + 10;
int fact[N],infact[N];

int qmi(int a, int k, int p)  // 求a^k mod p
{
    int res = 1 % p;
    while (k)
    {
        if (k & 1) res = (LL)res * a % p;
        a = (LL)a * a % p;
        k >>= 1;
    }
    return res;
}


int main(){
    int n,m;
    cin >> n >> m;
    int a = 2 * m + n - 1,b = n - 1;
    fact[0] = 1,infact[0] = 1;
    for(int i = 1;i < N;i++){
        fact[i] = (LL)fact[i - 1] * i % mod;
        infact[i] = (LL)infact[i - 1] * qmi(i,mod - 2,mod) % mod;
    }
    auto f = [](int a,int b) {
        return (LL)fact[a] * infact[b] % mod * infact[a - b] % mod;
    };
    cout << f(a,b) << endl;
}