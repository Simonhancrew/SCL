#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

// 基本还是双向LIS，记录一下连绵山形多长

const int N = 110;
int a[N];
int ldp[N],rdp[N];

int main()
{
    int n;
    cin >> n;
    for(int i = 1;i <= n;i++) cin >> a[i];
    for(int i = 1;i <= n;i++){
        ldp[i] = 1;
        for(int j = 1;j < i;j++){
            if(a[i] > a[j]) ldp[i] = max(ldp[i],ldp[j] + 1);
        }
    }
    for(int i = n;i;i--){
        rdp[i] = 1;
        for(int j = n;j > i;j--){
            if(a[i] > a[j]) rdp[i] = max(rdp[i],rdp[j] + 1);
        }
    }
    int rec = 1e9;
    for(int i = 1;i <= n;i++){
        int t = ldp[i] + rdp[i] - 1;
        rec = min(rec,n - t);
    }
#if 0
    int rec = 0;
    for(int i = 1;i <= n;i++){
        int t = ldp[i] + rdp[i] - 1;
        rec = max(rec,t);
    }
#endif
    cout << rec << endl;
}