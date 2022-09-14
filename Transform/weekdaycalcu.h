//给定一个日期，求这是星期几
// 1 计算这个日期与今天的距离X，今天星期y，过去给定的日期就是(（y-X）%7+7)%7+1
//未来的日期就是（y+X）%7+1
// 2 利用蔡乐公式1752年9月3日之前之后不同
//输出为星期ans+1
int whatday(int d, int m, int y) {
  int ans;
  if (m == 1 || m == 2) {
    m += 12, y--;
  }
  if (y < 1752 || (y == 1752 && m < 9) || (y == 1752 && m == 9 && d < 3)) {
    ans = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 + 5) % 7;
  } else {
    ans = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) % 7;
  }
  return ans;
}