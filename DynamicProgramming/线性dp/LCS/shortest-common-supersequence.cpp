#include <iostream>
#include <string>
#include <vector>

using namespace std;

// from LC 1092, 寻找两个序列s1, s2的最短公共序列s，其中
// s1和s2是s的子序列， 要求s最短
// 不难知道s的结果是s1和s2的最长公共子序列 + 每个序列独自的部分
// 在知道公共子序列的情况下，倒推过去

string s1, s2;

string solve(std::string& str1, std::string& str2) {
  int n = str1.size(), m = str2.size();
  vector<vector<int>> f(n + 1, vector<int> (m + 1));
  str1 = " " + str1;
  str2 = " " + str2;
  for (int i = 1;i <= n;i++) {
    for (int j = 1;j <= m;j++) {
      f[i][j] = max(f[i - 1][j], f[i][j - 1]);
      if (str1[i] == str2[j]) f[i][j] = max(f[i][j], f[i - 1][j - 1] + 1);
    }
  }
  string ans;
  int i = n, j = m;
  while (i > 0 || j > 0) {
    if (i == 0) {
      ans += str2[j];
      j--;
    } else if (j == 0) {
      ans += str1[i];
      i--;
    } else {
      if (str1[i] == str2[j]) {
        ans += str1[i];
        i--;
        j--;
      } else {
        if (f[i][j] == f[i - 1][j]) {
          ans += str1[i];
          i--;
        } else {
          ans += str2[j];
          j--;
        }
      }
    }
  }
  reverse(ans.begin(), ans.end());
  return ans;
}

int main() {
  cin >> s1 >> s2;
  cout << solve(s1, s2) << endl;
  return 0;
}


