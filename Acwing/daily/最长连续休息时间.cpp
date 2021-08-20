#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

// 处理循环数组问题的解决方式之一，开两倍

const int N = 4e5 + 10;

int a[N];

int main()
{
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        for(int i = 0;i < n;i++) cin >> a[i],a[i + n] = a[i];
        // for(int i = 0;i < 2 * n;i++) cout << a[i] << ' ';
        // puts("");
        int res = 0;
        for(int i = 0;i < 2 * n;i++){
            if(a[i] == 1){
                int j = i;
                while(a[j]) j++;
                res = max(res,j - i);
                i = j - 1;
            }
        }
        cout << res << endl;
    }
}