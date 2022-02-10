#include <iostream>
#include <algorithm>

using namespace std;

const int N = 5010;

#define fast_cin() ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)

int s[N][N];
int n,r;

/*
    炸掉的区域只有[R,R],所以直接看这个区间中的最大值是多少就好了
    拖着这个矩形在整区域上滑动就完了
*/

int main()
{
    fast_cin();
    cin >> n >> r;
    r = min(r,5001); // r最多只能覆盖这个范围
    for(int i = 0;i < n;i++) 
    {
        int x,y,w;
        cin >> x >> y >> w;
        ++x,++y;
        s[x][y] += w; // 有重复点
    }
    for(int i = 1;i <= 5001;i++) {
        for(int j = 1;j <= 5001;j++) {
            s[i][j] += s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
        }
    }
    int res = 0;
    for(int i = r;i <= 5001;i++) {
        for(int j = r;j <= 5001;j++) {
            res = max(res,s[i][j] - s[i - r][j] - s[i][j - r] + s[i - r][j - r]);
        }
    }
    cout << res << endl;
    return 0;
}
