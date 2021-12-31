#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

int x,y,k,b;

const int N = 35;

int c[N][N];

/*
    看成一个树的形式，每个位分情况讨论选择那种情况，针对题意化作k进制的表示
    然后逐位的分类讨论，确定情况下可以利用组合数计算总体情况
    需要注意提前结束的情况和边界
    数位dp的步骤也比较常态化：
        1. 取到进制下的所有位
        2. 按位讨论，从最高到最低（一般），取1和0的情况分别累加
        3. 最后特判最后情况
*/

void init(){// 组合数的初始
    for(int i = 0;i < N;i++){
        for(int j = 0;j <= i;j++){
            if(!j) c[i][j] = 1;
            else c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
        }
    }
}

int dp(int n){
    if(!n) return 0;
    vector<int> nums;
    while(n) {
        nums.push_back(n % b);
        n /= b;
    }
    int res = 0;
    int last = 0;
    for(int i = nums.size() - 1;i >= 0;i--){
        int x = nums[i];
        if(x){// 只有当前位大于0才有分支情况和1可选
            res += c[i][k - last]; // 考虑当前是0，剩下的情况可以直接用组合数计算出来
            if(x > 1){
                res += c[i][k - last - 1]; // 当前位大于1的时候，因为当前位只能取01两种，直接算出剩下的结束
                break; // 算满所有的情况之后结束
            }else{ // 当前位是1时，且取1，无法完全考虑所有的情况，需要留到后续考虑
                last++; 
                if(last > k) break;
            }
        }
        if(!i && last == k) ++res; // 最右侧的情况
    }
    return res;
}

int main(){
    init();
    cin >> x >> y >> k >> b;
    cout << dp(y) - dp(x - 1) << '\n';
    return 0;
}