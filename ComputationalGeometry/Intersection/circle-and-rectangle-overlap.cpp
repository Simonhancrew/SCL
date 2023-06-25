#include <array>
#include <iostream>
#include <vector>

// Created by Simonhancrew on 2023/06/25

using namespace std;

using LL  = long long;
using PII = pair<int, int>;
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);                 \
  cout.tie(nullptr)

const int INF = 0x3f3f3f3f;

namespace detail {

int radius, x1, y1, x2, y2;
int x_center, y_center;

}  // namespace detail

bool CheckIntersection(int radius, int x_center, int y_center, int x1, int x2,
                       int y1, int y2) {
  array<double, 2> rec_core = {(x1 + x2) / 2.0, (y1 + y2) / 2.0};
  // 矩形中心->圆形中心的向量，将这个向量平移到第一象限，做一次std::abs就可以了
  array<double, 2> dis_p = {std::abs(rec_core[0] - x_center),
                            std::abs(rec_core[1] - y_center)};
  // 矩形中心->(x2, y2)的向量
  array<double, 2> dis_q = {x2 - rec_core[0], y2 - rec_core[1]};
  // (x2, y2)->圆形中心的向量
  array<double, 2> dis_sub = {
      dis_p[0] - dis_q[0] < 0 ? 0 : dis_p[0] - dis_q[0],
      dis_p[1] - dis_q[1] < 0 ? 0 : dis_p[1] - dis_q[1]};
  // 看看距离是不是比半径小
  return dis_sub[0] * dis_sub[0] + dis_sub[1] * dis_sub[1] <= radius * radius;
}

int main() {
  // freopen("input.txt","r",stdin);
  // freopen("output.txt","w",stdout);
  fast_cin();
  using namespace detail;
  cin >> radius >> x_center >> y_center >> x1 >> detail::y1 >> x2 >> y2;
  if (CheckIntersection(radius, x_center, y_center, x1, x2, detail::y1, y2)) {
    cout << "yes" << endl;
    return 0;
  }
  cout << "no" << endl;
  return 0;
}
