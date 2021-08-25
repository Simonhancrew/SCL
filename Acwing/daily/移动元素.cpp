#include <iostream>
#include <cstring>
#include <algorithm>
#include <unordered_set>

using namespace std;

// 1. 能不用放数走就能直接得到S / 2
// 2. 需要放走一个数，考虑是从那边放走的，正方做一次前缀和+hash判断有没有出现。

const int N = 1e5 + 10;

typedef long long LL;

int a[N],b[N];
LL s[N];

int n;

bool check(int w[]){
    for(int i = 1;i <= n;i++){
        s[i] = s[i - 1] + w[i];
    }
    if(s[n] & 1) return false;
    unordered_set<int> mp;
    mp.insert(0);
    for(int i = 1;i <= n;i++){
        mp.insert(w[i]);
        if(mp.count(s[i] - s[n] / 2)) return true;
    }
    return false;
}

int main()
{
    int t;
    cin >> t;
    while(t--){
        cin >> n;
        for(int i = 1,j = n;i <= n;i++,j--) {
            cin >> a[i];
            b[j] = a[i];
        }
        if(check(a) || check(b)) puts("YES");
        else puts("NO");
    }
    return 0;
}