# 快速幂

```cpp
LL qmi(int a, int b, int mod) {
  LL res = 1;
  while (b) {
    if (b & 1) {
      res = (res * a) % mod;
    }
    a = (static_cast<LL>(a) * a) % mod;
    b >>= 1;
  }
  return res;
}
```

化指数为二进制，然后根据二进制位数，每次乘以当前的底数，然后底数平方，指数右移一位。

比如求 $a^b$, $b = 13$, $a = 2$, 则 $b = 1101$, $a^b = a^{2^3} \times a^{2^2} \times a^{2^0}$
