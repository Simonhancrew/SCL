#include <algorithm>
#include <cstring>
#include <iostream>
#include <unordered_map>

using namespace std;

int ans;

/*
    正常搜索需要20 ** 7的复杂度，需要思考优化的方法
    因为最后是要统计奇偶的，只需要记录每个字符的奇偶数各有多少个
    最后在搜索的最终情况下判断是否符合要求
    符合要求的话直接在结果中加入当前组合的情况
*/

unordered_map<char, int> mp[2];
unordered_map<char, int> rec;

string s = "BESIGOM";

#if 0
void dfs(int idx,int cnt) {
    if(idx == 7) {
        if((rec['B'] + rec['I']) % 2 && (rec['G'] + rec['O'] + rec['E'] + rec['S']) % 2 && rec['M'] % 2) return; 
        ans += cnt;
        return;
    }
    char cur = s[idx];
    rec[cur] = 1,dfs(idx + 1,cnt * mp[1][cur]);
    rec[cur] = 0,dfs(idx + 1,cnt * mp[0][cur]);
}
#endif

int main() {
  int n;
  cin >> n;
  while (n--) {
    char ch;
    int nu;
    cin >> ch >> nu;
    mp[abs(nu) % 2][ch]++;
  }
  // dfs(0,1);
  for (int i = 0; i < (1 << 7); i++) {
    for (int j = 0; j < 7; j++) {
      rec[s[j]] = (i >> j) & 1;
    }
    if ((rec['B'] + rec['I']) * (rec['G'] + rec['O'] + rec['E'] + rec['S']) *
            rec['M'] % 2 ==
        0) {
      int sum = 1;
      for (int j = 0; j < 7; j++) {
        sum *= mp[i >> j & 1][s[j]];
      }
      ans += sum;
    }
  }
  cout << ans << endl;
  return 0;
}