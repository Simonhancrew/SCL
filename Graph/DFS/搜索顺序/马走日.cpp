#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 11;

int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};
bool st[N][N];
int m,n,ans,T;

void dfs(int x,int y,int cnt) {
    if(cnt == n * m) {
        ans++;
        return;
    }
    st[x][y] = true;
    for(int i = 0;i < 8;i++) {
        int nx = x + dx[i],ny = y + dy[i];
        if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
        if(st[nx][ny]) continue;
        dfs(nx,ny,cnt + 1);
    }
    st[x][y] = false;
}

int main(){
    cin >> T;
    while(T--) {
        int x,y;
        ans = 0;
        cin >> n >> m >> x >> y;
        dfs(x,y,1);
        cout << ans << endl;
    }
    return 0;
}