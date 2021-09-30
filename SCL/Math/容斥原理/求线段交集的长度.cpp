#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int main(){
    int l1,r1,l2,r2;
    cin >> l1 >> r1 >> l2 >> r2;
    // 给出端点求区间长度，相不相交都可以做
    cout << max(0,min(r1,r2) - max(l1,l2)) << endl;
    return 0;
}