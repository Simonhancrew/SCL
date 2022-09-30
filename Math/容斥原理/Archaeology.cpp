#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

// CF,1178E
// 这种构造算法有特殊到一般
// 首先考虑首部的2个char和尾部的两个char，因为整体只有a,b,c三个数，且相邻位置不能
// 是相同的两个数，所以由容斥原理，这个pair对中，必定有相同的数
// 因此，每2位去枚举就行了。为了方便代码，可以从idx为1的开始

string s;

int main() {
  // freopen("input.txt", "r", stdin);
  cin >> s;
  // cout << s << '\n';
  int n = s.size();
  string ans;
  for (int i = 1; i < n / 2; i += 2) {
    if (s[i] == s[n - i] || s[i] == s[n - i - 1]) {
      ans.push_back(s[i]);
    } else {
      ans.push_back(s[i - 1]);
    }
  }
  cout << ans;
  if (n % 4) {
    cout << s[n / 2];
  }
  reverse(ans.begin(), ans.end());
  cout << ans << '\n';
  return 0;
}
