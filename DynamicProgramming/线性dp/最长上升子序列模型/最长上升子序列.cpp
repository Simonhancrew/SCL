#include <iostream>
#include <algorithm>

//还是考虑最后一步，拿不拿，拿的话，他之前的那个状态是哪一个？一定是比当前小的，我们求的是当前位置作为结尾的最长序列
//所以需要去前面遍历一下比他下的元素，然后每个状态+1看谁是最大的
//不同于之前的dp，此处我们要遍历一下每个位置结尾的最大值才能拿到最大的上升序列

using namespace std;

const int N = 1e3 + 10;
int dp[N];
int a[N];


int main(){
    int n;
    cin >> n;
    for(int i = 1;i <= n;i++) cin >> a[i];
    
    
    for(int i = 1;i <= n;i++){
        dp[i] = 1;
        for(int j = 1;j < i;j++){
            if(a[j] < a[i]){
                dp[i] = max(dp[i],dp[j] + 1);
            }
        }
    }
    int res = 0;
    for(int i = 1;i <+ n;i++) res = max(dp[i],res);
    cout << res << endl;
    return 0;
}


// 贪心解能处理更大的数据，我们用数组q存储这个序列，遍历全部的数组n，如果当前遍历到的数字是比当前数组存储的结尾的数字还要大的话
// 长度+1，当前遍历到的数字放在末尾
// 如果当前的数字不大于末尾的数字的话，找到这个数字的lower_bound,替换掉。
// 直觉上是比较容易感知到这个算法的正确性的
// 证明可以采用和微调法，首先有贪心解和最优解，贪心解的长度是小于等于最优解的
// 之后，由于贪心解的每一个数字都是比之前的大的，那么一定可以在最优解中，找到一段末尾的部分接上，因为贪心解的每个结尾都最小了，只能考虑最优解的末尾有更大的部分

#ifdef E5
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;


const int N = 1e5 + 10;

int a[N],q[N];

int main(){
    int n;
    cin >> n;
    for(int i = 0;i < n;i++) cin >> a[i];
    int len = 0;
    for(int i = 0;i < n;i++){
        if(len == 0) q[len++] = a[i];
        else{
            if(a[i] > q[len - 1]) q[len++] = a[i];
            else{
                auto it = lower_bound(q,q + len,a[i]);
                q[it - q] = a[i];
            }
        }
    }
    cout << len << endl;
}
#endif