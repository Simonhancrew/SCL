## quick sort的证明

核心的部分都在sort这个函数里, 利用算导的循环不变量对代码正确性做一个证明

```cpp
void sort(int a[], int l, int r) {
  if (l >= r)
    return;
  // 保证一个循环不变量, 区间[l, i]范围<=tar, 区间[j, r]范围>=tar
  // 初始的时候区间是空的, 满足要求
  int i = l - 1, j = r + 1, tar = a[l + (r - l) / 2];
  while (i < j) {
    do
      i++;
    while (a[i] < tar);
    do
      j--;
    while (a[j] > tar);
    // 此时a[j] <= tar, q[i] >= tar, 让循环不变式继续满足, 交换ij就好
    if (i < j)
      swap(a[i], a[j]);
  }
  sort(a, l, j), sort(a, j + 1, r);
}
```

为了满足循环不变量，按照初始->循环->中止的情况分析，需要证明的情况就是循环结束之后，要求[l, j]完全<=tar, [j + 1, r] >= tar
1. 初始
  构造一个不变式[l, i] <= tar, [j, r] >= tar
  初始的时候空集,满足条件
2. 循环中
  经过增减运算之后, [i]一定是>= tar的, [j]是<=tar的, 循环不会结束跳出, i < j, 交换之后情况依然满足
  此时[l, i] <= tar, [j, r] >= tar
3. 中止
  此时最后一轮, 到if的时候i >= j, 不执行交换, 但是此时a[i] >= tar, a[j] <= tar, 且a[j + 1] > tar
  满足的区间是[l, j], [j + 1, r]