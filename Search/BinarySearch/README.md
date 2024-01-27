# 二分搜索模板解读

记得二分区间要表达的意义

这种找lower bound的，保证的是l永远不合法，转换过来说就是a[l]永远小于target，a[r]永远大于等于target, 要的结果就是l + 1, 如果r == n, 说明没有合法的解

如果要找upper bound(等于target的最右边，不是`std::upper_bound`), 那么就是a[l]永远小于等于target，a[r]永远大于target，l从-1开始，如果l结束了还是-1，没有合法解

等价翻译过来，不要关心区间内的是什么范围，关心区间外的是怎么样的,区间外都是确定了和target的大小关系的。这样在最后结束二分时，就能够保证区间内的是什么范围了。

写开区间的，(l, r), l<=的位置永远小于target，>= r的位置永远大于等于target（注意，等于只能在一边取到）

此时，如果没有合法解答，r会位于数组右外侧。需要额外判断段一下

```cpp
int lower_bound(int target) {
  int l = -1, r = n;
  while (l + 1 < r) {
    int mid = (l + r) >> 1;
    if (check(mid)) {
        r = mid;
    } else {
        l = mid;
    }
  }
  return r;
}

// 这里的bound是=target的右界，std::upper_bound在这个后一位，如果有的话
int upper_bound(int target) {
  int l = -1, r = n;
  while (l + 1 < n) {
    int mid = l + r >> 1;
    if (check(mid)) {
      l = mid;
    } else {
      r = mid;
    }
  }
  return l;
} 

```

找上界的话，稍微修改一下lower bound

```cpp
return lower_bound(target + 1) - 1;
```

## 二段性的二分

二分只要满足二段性就能够使用，将一个二段性数组区间[l, r]看作蓝色和红色的部分(左侧是红色，也就是小于或者不满足条件的区域)

lower_bound其实实在找两种颜色的分割点

每次的[l, r]也看做一个红色->蓝色的分解数组，对于当前mid，lower_bound找target只要target在红色段就要缩小上界

因此check函数只要判断target是不是在红色区域就行了
