#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef pair<int,int> PII;

const int N = 5e5 + 10;

// 最大不相交区间个数的模板，贪心求解

PII a[N];

int n;

int main()
{
    cin >> n;
    for(int i = 0;i < n;i++){
        int l,r;
        cin >> l >> r;
        a[i] = {l,r};
    }
    sort(a,a + n,[](auto lhs,auto rhs) {
        return lhs.second < rhs.second;
    });
    int res = 0,bd = -1e9;
    for(int i = 0;i < n;i++){
        int l = a[i].first,r = a[i].second;
        if(bd < l) res++,bd = r;
    }
    cout << res << endl;
    return 0;
}