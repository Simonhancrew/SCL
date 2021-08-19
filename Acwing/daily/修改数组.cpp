#include <iostream>
#include <cstring>
#include <algorithm>

// 数据量足够小，直接遍历就可以了

using namespace std;

const int N = 1e3 + 10;

int a[N];

int main()
{
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        for(int i = 0;i < n;i++) cin >> a[i];
        int cost = 1e9,ans = -1;
        for(int t = 1;t <= 100;t++){
            int cur = 0;
            for(int i = 0;i < n;i++){
                if(a[i] > t + 1) cur += (a[i] - t - 1);
                else if(a[i] < t - 1) cur += (t - 1 - a[i]);
            }
            if(cur < cost){
                cost = cur;
                ans = t;
            }
        }
        cout << ans << ' ' << cost << endl;
    }
    return 0;
}
