## 二进制常用的几个tricks

### 二进制子集枚举

```cpp
// 遍历 u 的非空子集
for (int s = u; s; s = (s - 1) & u) {
  // s 是 u 的一个非空子集
}
```

### 判断一个数是不是2的幂次

```
a & (a - 1) == 0
```

