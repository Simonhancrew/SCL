# 二分搜索模板解读

记得二分区间要表达的意义

这种找lower bound的，保证的是l - 1永远不合法，转换过来说就是a[l - 1]永远小于target，a[r]永远大于等于target。

等价翻译过来，不要关心区间内的是什么范围，关心区间外的是怎么样的,区间外都是确定了和target的大小关系的。这样在最后结束二分时，就能够保证区间内的是什么范围了。

优先下取整，把l缩放到最大

写开区间的，(l, r), l<=的位置永远小于target，>= r的位置永远大于等于target

此时，如果没有合法解答，r会位于数组右外侧。需要额外判断段一下

```cpp
void lower_bound(int target) {
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
