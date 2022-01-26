#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 60,INF = 0x3f3f3f3f,M = 35;

int a[N];


// 此题需要使用高精度，先写出不用高精度的代码之后改
#if 0
int f[N][N];
int main(){
    int n;
    cin >> n;
    for(int i = 1;i <= n;i++) cin >> a[i];
    
    for(int len = 3;len <= n;len++){
        for(int l = 1;l + len - 1 <= n;l++){
            int r = l + len - 1;
            f[l][r] = INF;
            for(int k = l + 1;k < r;k++){
                f[l][r] = min(f[l][r],f[l][k] + f[k][r] + a[l] * a[k] * a[r]);
            }
        }
    }
    cout << f[1][n] << endl;
}
#endif

typedef long long LL;
LL f[N][N][M];

void mul(LL a[],LL b){
    LL c[M];
    memset(c,0,sizeof c);
    LL t = 0;
    for(int i = 0;i < M;i++){
        t += a[i] * b;
        c[i] = t % 10;
        t /= 10;
    }
    memcpy(a,c,sizeof c);
}

void add(LL a[],LL b[]){
    LL c[M];
    memset(c,0,sizeof c);
    LL t = 0;
    for(int i = 0;i < M;i++){
        t += a[i] + b[i];
        c[i] = t % 10;
        t /= 10;
    }
    memcpy(a,c,sizeof c);
}

int cmp(LL a[],LL b[]){
    for(int i = M - 1;i >= 0;i--){
        if(a[i] > b[i]) return 1;
        else if(a[i] < b[i]) return -1;
    }
    return 0;
}

void print(LL a[]){
    int k = M - 1;
    while(k && !a[k]) k--;
    while(k >= 0) cout << a[k--];
    cout <<endl;
}


int main(){
    int n;
    cin >> n;
    for(int i = 1;i <= n;i++) cin >> a[i];
    LL tmp[M];
    for(int len = 3;len <= n;len++){
        for(int l = 1;l + len - 1 <= n;l++){
            int r = l + len - 1;
            f[l][r][M - 1] = 1;
            for(int k= l + 1;k < r;k++){
                memset(tmp,0,sizeof tmp);
                tmp[0] = a[l];
                mul(tmp,a[k]);
                mul(tmp,a[r]);
                add(tmp,f[l][k]);
                add(tmp,f[k][r]);
                if(cmp(f[l][r],tmp) > 0){
                    memcpy(f[l][r],tmp,sizeof tmp);
                }
            }
        }
    }
    print(f[1][n]);
    return 0;
}
