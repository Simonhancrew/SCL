#include <iostream>
#include <vector>

using namespace std;
using LL = long long;

vector<int> nums;
int n, l, r;

int main(){
  cin >> n >> l >> r;
  nums.resize(n);
  for(int i = 0;i < n;i++) cin >> nums[i];
  auto calcu = [](int mx) {
    int res = 0;
    for(int i = 0;i < n;i++) {
      if(nums[i] > mx) continue;
      int j = i + 1;
      while(j < n && nums[j] <= mx) j++;
      int dis = j - i;
      res += (LL)dis * (dis + 1) / 2;
      i = j;
    }
    return res;
  };
  cout << calcu(r) - calcu(l - 1) << '\n';
  return 0;
}


