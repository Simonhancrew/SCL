#include <iostream>
using namespace std;

const int N = 1e5 + 10;

int a[N], r[N];

/*
    枚举区间右端点,对于每一个右端点去找他的最左端点
    Sliding Window应用题
*/
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }
  int ans = 1;
  for (int i = 0, j = 0; i < n; ++i) {
    //前一个区间结束时没有重复的数的
    //新加一个数a[i]进来如果有重复的一定是a[i]
    r[a[i]]++;
    while (r[a[i]] > 1) {
      r[a[j]]--;
      j++;
    }
    ans = max(ans, i - j + 1);
  }
  cout << ans;
  return 0;
}

/*
    一个可以参考的模板
    for(int i = 0,j = 0,...;j < n;j++){
        update(state(i,j)); // 更新(i,j)区间中能得出的状态
        while(i < j && length(i,j)){ // 长度满足题目范围
            check(state(i,j)) dosomething; // 状态满足条件更新结论
            update(state(i + 1,j)); // 更新状态
            i++; // 缩减左边
        }
    }
*/