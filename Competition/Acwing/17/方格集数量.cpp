//最开始用的组合数，没必要，WA了一次，忘记开long long了
#ifdef ORIGIN
#include <iostream>
#include <cstring>
#include <algorithm>


using namespace std;

typedef long long LL;

const int N = 60;

int a[N][N];
int row[N][2];
int col[N][2];
LL C[N][N];

void init(){
    for(int i = 0;i < N;i++){
        for(int j = 0;j <= i;j++){
            if(!j) C[i][j] = 1;
            else C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]);
        }
    }
}

int main()
{
    int n,m;
    cin >> n >> m;
    init();
    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++){
            cin >> a[i][j]; 
            if(a[i][j] == 1){
                row[i][1]++;
                col[j][1]++;
            }else{
                row[i][0]++;
                col[j][0]++;
            }
        }
    }
    LL res = m * n; 
    for(int i = 0;i < n;i++){
        for(int j = 2;j <= row[i][1];j++) res += C[row[i][1]][j];
        for(int j = 2;j <= row[i][0];j++) res += C[row[i][0]][j];
    }
    for(int i = 0;i < m;i++){
        for(int j = 2;j <= col[i][1];j++) res += C[col[i][1]][j];
        for(int j = 2;j <= col[i][0];j++) res += C[col[i][0]][j];
    }
    cout << res  << endl;
}
#endif

