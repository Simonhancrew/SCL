#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 2e5 + 10;

typedef pair<int, int> PII;

PII r[N];
vector<int> mp[N];
int res[N];
int b[N];

int main(){
    int n,k;
    cin >> n >> k;
    for(int i = 1;i <= n;i++){
        cin >> r[i].second;
        b[i] = r[i].second;
        r[i].first = i;
    }
    sort(r + 1,r + n + 1,[](auto lhs,auto rhs) {
        return lhs.second < rhs.second;
    });
    while(k--){
        int x,y;
        cin >> x >> y;
        mp[x].push_back(y);
        mp[y].push_back(x);
    }
    int lst = 0;
    for(int i = 1;i <= n;i++){
        int ans = lst;
        int cur = r[i].first;
        for(auto q : mp[cur]) {
            if(b[q] < r[i].second) ans--;
        }
        if(r[i].second != r[i + 1].second) lst = i;
        res[cur] = ans;
    }
    for(int i = 1;i <= n;i++) cout << res[i] << ' ';
    puts("");
}