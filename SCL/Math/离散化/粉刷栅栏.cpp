#include <iostream>
#include <map>

using namespace std;

#define fast_cin() ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)

/*
    完整区间是1e9的，太大，差分一次再前缀和之后会超时
    但是用的到游走次数只有1e5，可以在这部分区间做一个离散，然后针对这部分区间做差分求和
*/

int n,len;
char op;
map<int,int> mp;

int main(){
    fast_cin();
    cin >> n;
    int lhs = 0;
    while(n--){
        cin >> len >> op;
        if(op == 'R') mp[lhs]++,mp[lhs + len]--,lhs += len;
        else mp[lhs - len]++,mp[lhs]--,lhs -= len;
    }
    int ans = 0,sum = 0,last;
    for(auto &[k,v] : mp){
        if(sum >= 2) ans += k - last;
        last = k,sum += v;
    }
    cout << ans << endl;
    return 0;
}