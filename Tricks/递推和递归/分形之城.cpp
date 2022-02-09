#include <iostream>
#include <cmath>

using namespace std;

int t;
using LL = long long;
#define x first
#define y second
using PII = pair<LL,LL>;


/*
    递推，找到具体在那一块，然后找到坐标
*/
PII get(LL n, LL a)
{
    if (n == 0) return {0, 0};
    // n - 1级，每个块中有2 ** （2 * n -  2）个格子，边长是2 ** （n - 1） 
    LL block = 1ll << n * 2 - 2, len = 1ll << n - 1;
    auto p = get(n - 1, a % block);
    LL x = p.x, y = p.y;
    int z = a / block;

    if (z == 0) return {y, x};
    else if (z == 1) return {x, y + len};
    else if (z == 2) return {x + len, y + len};
    return {len * 2 - 1 - y, len - 1 - x};
}

int main(){
    cin >> t;
    while(t--) {
        LL n,a,b;
        cin >> n >> a >> b;
        auto pa = get(n,a - 1),pb = get(n,b - 1); 
        double dx = pa.x - pb.x,dy = pa.y - pb.y;
        printf("%.0lf\n",sqrt(dx * dx + dy * dy) * 10); // 做一个舍入
    }
    return 0;
}