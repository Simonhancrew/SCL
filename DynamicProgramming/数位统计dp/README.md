## 数位dp

数位dp是指把一个数字按照个、十、百、千等等一位一位地拆开，关注它每一位上的数字。

比较普遍的形式就是统计满足一些要求的数的数量，且数位dp在区间之内的统计有比较通俗的解法：

ans[l,r] = ans[0,r] - ans[0,l - 1];

统计答案的时候可以选择记忆化搜索，值得关注的是，记忆化要记住的状态要求是可复用的。如果要用f记忆化数组记录某个值得话

例如f[i][state]，这个状态记得表示不贴上界，且无前导零

对于一个固定的[i,state],在有限制的条件下，递归只会出现一次，没有必要记忆

在有无约束的情况下，[i,state]可能大量出现，这个时候只在无约束的时候这个量才有有效。

无约束下，不贴上界比较好理解。

无前导0，计算[0, n]中，有多少个x满足: 统计x的每个数位，要求0-9的出现次数都是偶数，如果把前导0也算进去的话，就会和x的0混在一起，没法判断x的0是否出现了偶数次

关于前导零，主要看前导零对求值的结果有没有影响(或者说看影不影响for loop里取值)，有影响的情况下，不考虑前导零会导致下一个值无法正常的选取

推荐写dfs的解，要直白很多

```cpp
int dfs(int pos, int pre, bool lead, bool limit) { // 不同题目的
    if (!pos) {
        边界条件
    }
    if (!limit && !lead && f[pos][pre] != -1) return f[pos][pre]; // 不贴上，无前导零
    int res = 0, up = limit ? a[pos] : 无限制位;
    for (int i = 0; i <= up; i ++) {
        if (不合法条件) continue;
        res += dfs(pos - 1, 未定参数, lead && !i, limit && i == up);
    }
    return limit ? res : (lead ? res : f[pos][sum] = res); // 记得更新f
}
int cal(int x) {
    memset(f, -1, sizeof f); // 记忆化数组
    len = 0;
    while (x) a[++ len] = x % 进制, x /= 进制;
    return dfs(len, 未定参数, 1, 1);
}
int main() {
    cin >> l >> r;
    cout << cal(r) - cal(l - 1) << endl;
}
```