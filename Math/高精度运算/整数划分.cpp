#include <iostream>
#include <vector>

/*
    n >= 10，一个结论是尽可能凑3
*/

using namespace std;

int n;
vector<int> ans;

void mul(int x) {
  int add = 0;
  for (int i = 0; i < ans.size(); i++) {
    int t = ans[i] * x + add;
    ans[i] = t % 10, add = t / 10;
  }
  if (add) ans.push_back(add);
}

void solve() {
  ans.push_back(1);
  if (n % 3 == 0) {
    for (int i = 0; i < n / 3; i++) mul(3);
  } else if (n % 3 == 1) {
    mul(4);
    for (int i = 0; i < n / 3 - 1; i++) {
      mul(3);
    }
  } else if (n % 3 == 2) {
    mul(2);
    for (int i = 0; i < n / 3; i++) mul(3);
  }
}

int main() {
  cin >> n;
  solve();
  cout << ans.size() << endl;
  if (ans.size() <= 100) {
    for (int i = ans.size() - 1; i >= 0; i--) cout << ans[i];
  } else {
    for (int i = ans.size() - 1; i >= ans.size() - 100; i--) cout << ans[i];
  }
}