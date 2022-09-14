#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>

using namespace std;
#define x first
#define y second

typedef pair<int, string> PIS;

/*
    最小堆中存当前点到终点的股价距离 + 到该店的最小距离
    保证估价距离是小于等于当前点到终点的真实距离的

    直到遇到终点才停止搜索，（只有遇到终点出队的时候才能保证距离肯定正确）
   A*要保证题目有解才能进行

    八数码问题的有解，逆序对要满足偶数
    因为一次变换保证只能改变0个或者2个逆序对状态，最后状态的逆序对是0个

    剩下的就是BFS的问题了，注意更新状态的时候，不必类似Dij那种出队判重，或者像之前最短路的时候，入队判重
    这里因为除了终点的每个点不确定是不是最优解，每次都需要判断能不能更新一次距离的最优解
*/

int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
unordered_map<string, int> dist;
unordered_map<string, pair<char, string>> pre;
priority_queue<PIS, vector<PIS>, greater<PIS>> heap;

// 启发函数算当前点到当前点应处位置的曼哈顿距离
int f(string state) {
  int res = 0;
  for (int i = 0; i < 9; i++) {
    if (state[i] != 'x') {
      int t = state[i] - '1';
      res += abs(i / 3 - t / 3) + abs(i % 3 - t % 3);
    }
  }
  return res;
}

string bfs(string &start) {
  string end = "12345678x";
  char op[] = "urdl";
  dist[start] = 0;
  heap.push({f(start), start});
  string source = start;
  while (heap.size()) {
    auto t = heap.top();
    heap.pop();
    string state = t.y;

    if (state == end) break;
    int x, y;

    for (int i = 0; i < 9; i++) {
      if (state[i] == 'x') {
        x = i / 3, y = i % 3;
        break;
      }
    }

    string source = state;
    for (int i = 0; i < 4; i++) {
      int nx = x + dx[i], ny = y + dy[i];
      if (nx < 0 || nx >= 3 || ny < 0 || ny >= 3) continue;
      swap(state[x * 3 + y], state[nx * 3 + ny]);
      // 不同于dij，每次都要更新，不必判重
      if (!dist.count(state) || dist[state] > dist[source] + 1) {
        dist[state] = dist[source] + 1;
        pre[state] = {op[i], source};
        heap.push({f(state) + dist[state], state});
      }
      swap(state[x * 3 + y], state[nx * 3 + ny]);
    }
  }

  string res;
  while (start != end) {
    res += pre[end].x;
    end = pre[end].y;
  }
  reverse(res.begin(), res.end());
  return res;
}

int main() {
  string start, seq;
  char ch;
  while (cin >> ch) {
    start += ch;
    if (ch != 'x') seq += ch;
  }
  int cnt = 0;
  for (int i = 0; i < 8; i++) {
    for (int j = i; j < 9; j++) {
      if (seq[i] > seq[j]) cnt++;
    }
  }
  if (cnt & 1)
    cout << "unsolvable" << endl;
  else
    cout << bfs(start) << endl;
  return 0;
}