#include <algorithm>
#include <cstring>
#include <functional>
#include <iostream>
#include <string>

// Created by Simonhancrew on 2022/11/05

using namespace std;

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f;

std::string s;

// dfs: base -> for -> dfs
bool parse(string &s) {
  int i = 0;
  // 这种表达式解析问题其实就是stack模拟
  // dfs实现，先找到最底层的base case
  // 然后模拟遍历，遇到了能求值的部分继续dfs
  function<bool()> dfs = [&]() {
    if (s[i] == 't') {
      i++;
      return true;
    }
    if (s[i] == 'f') {
      i++;
      return false;
    }
    char op = s[i];
    i += 2;
    bool res = true;
    if (op == '|')
      res = false;
    while (i < s.size() && s[i] != ')') {
      if (s[i] == ',')
        i++;
      bool t = dfs();
      if (op == '|')
        res |= t;
      else
        res &= t;
    }
    i++;
    if (op == '!')
      res = !res;
    return res;
  };
  return dfs();
}

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  cin >> s;
  cout << parse(s) << endl;
  return 0;
}
