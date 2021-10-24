#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10,INF=1e9;

// dp[i][0/1]，前i个中拿，1表示拿第i个，0表示不拿第i个。思考的时候考虑最后一个拿不拿

int t,n;

#if 0
int f[N][2];
int a[N];

int main(){
    cin >> t;
    while(t--){
        cin >> n;
        for(int i = 1;i <= n;i++) cin >> a[i];
        for(int i = 1;i <= n;i++){
            f[i][0] = max(f[i - 1][0],f[i - 1][1]);
            f[i][1] = f[i - 1][0] + a[i];
        }
        cout << max(f[n][0],f[n][1]) << endl;
    }
    return 0;
}
#endif

int f[2][2];

int main(){
    cin >> t;
    while(t--){
        cin >> n;
        int old = 0,now = 0;
        memset(f,0,sizeof f);
        f[0][1] = -INF;
        for(int i = 1;i <= n;i++){
            int a;
            cin >> a;
            old = now,now = 1 - now;
            f[now][0] = max(f[old][0],f[old][1]);
            f[now][1] = f[old][0] + a;
        }
        cout << max(f[now][0],f[now][1]) << endl;
    }
    return 0;
}