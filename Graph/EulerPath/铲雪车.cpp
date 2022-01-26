#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

// 首先是双向车道，来回铲两次雪。每个点的入度等于出度，必然存在一个欧拉回路
// 直接计算长度的两倍除以扫雪车的行进速度就可以了

int main(){
    double x1,y1,x2,y2;
    cin >> x1 >> y1;
    double sum = 0;
    while(cin >> x1 >> y1 >> x2 >> y2){
        double dx = x2 - x1;
        double dy = y2 - y1;
        sum += sqrt(dx * dx + dy * dy) * 2;
    }
    // cout << sum << endl;
    int minutes = round(sum / 1000 / 20 * 60);
    int hour = minutes / 60;
    minutes %= 60;
    printf("%d:%02d",hour,minutes);
    return 0;
}