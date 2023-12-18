## 二分搜索模板解读

记得二分区间要表达的意义


这种找lower bound的，保证的是l - 1永远不合法，转换过来说就是a[l - 1]永远小于target，a[r]永远大于等于target。

等价翻译过来，不要关心区间内的是什么范围，关心区间外的是怎么样的,区间外都是确定了和target的大小关系的。这样在最后结束二分时，就能够保证区间内的是什么范围了。

优先下取整，把l缩放到最大

这种写法不会超越下标的边界，也就是说如果不存在这个数需要自己去检查一下


```cpp
bool check(int x) {/* ... */} // 检查x是否满足某种性质

// 区间[l, r]被划分成[l, mid]和[mid + 1, r]时使用：
int bsearch_1(int l, int r)
{
    while (l < r)
    {
        int mid = l + r >> 1;
        if (check(mid)) r = mid;    // check()判断mid是否满足性质
        else l = mid + 1;
    }
    return l;
}
```

这种找上边界的，r + 1保证不合法，也就是r + 1的小标永远大于target, l永远大于等于target

优先上取整，把r的大小缩到最小
```cpp
// 区间[l, r]被划分成[l, mid - 1]和[mid, r]时使用：
int bsearch_2(int l, int r)
{
    while (l < r)
    {
        int mid = l + r + 1 >> 1;
        if (check(mid)) l = mid;
        else r = mid - 1;
    }
    return l;
}
```

注意l + r >> 1是下取整的，所以实际更新的时候，如果更新的是l，需要考虑边界的问题，否则就会死循环，比如

```cpp
l = 0,r = 1
l = mid = (l + r) >> 1 
```

此时l还是0，完全死循环了。改成`l + r + 1 >> 1`就没有问题了。

另外还有上下界的判断问题，这里记录一下怎么找上界

```cpp
if(num[mid] <= target) l = mid;
```

这里每次等于的时候边界也会更新，一直到不能更新的时候找到了恰好找到了target的右边界，l == r,更新结束。简而言之就是左边界会一直往右边缩小。

同理，下界就是.满足条件的时候右边界一直往下缩小。

```cpp
if(num[mid] >= target) r = mid
```

另外还有一种写法， 这种保证l-1永远小于target，r + 1永远大于target

因此这种对于不存在的数，会返回一个边界外的坐标n
```cpp
int lower_bound(int a[], int tar) {
  int l = 0,r = n - 1;
  while (l < r) {
    int mid = l + r >> 1;
    if (a[mid] < tar) l = mid + 1;
    else r = mid - 1;
  }
  return l;
}
```

### 二段性的二分

二分只要满足二段性就能够使用，将一个二段性数组区间[l, r]看作蓝色和红色的部分(左侧是红色，也就是小于或者不满足条件的区域)

lower_bound其实实在找两种颜色的分割点

每次的[l, r]也看做一个红色->蓝色的分解数组，对于当前mid，lower_bound找target只要target在红色段就要缩小上界

因此check函数只要判断target是不是在红色区域就行了
