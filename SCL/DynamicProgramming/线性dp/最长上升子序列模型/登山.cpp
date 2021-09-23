#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e3 + 10;

int n,a[N];
int ldp[N],rdp[N];

// 极度类似怪盗基德那道题，两边各一次之后相加减一,找一个山峰的问题

int main()
{
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
    int res = 0;
    for(int i = 1;i <= n;i++){
        res = max(res,ldp[i] + rdp[i] - 1);
    }
    cout << res << endl;
    return 0;
}