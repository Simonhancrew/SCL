# 质数

素数的定义比较简单，正数p != 0,+-1，且除了p和1之外没有任何约数，这个数就是素数。

针对素数问题，第一个要关注的点就是筛法

关于质数筛选，主要有两种筛法，第一种是埃氏筛，第二种是线性筛。

其中，埃氏筛种合数不是被唯一最大公约数筛出的，更好的方法是使用线性筛

埃氏筛

```cpp
bool st[N];
int primes[N];
cnt = 0;

void get_prime(int n){
    for(int i = 2;i <= n;i++){
        if(st[i]) continue;
        primes[cnt++] = i;
        for(int j = i;j <= n;j += i) {
            st[j] = true;
        }
    }
}
```

线性筛种，就是利用每个合数的最大公因数去唯一的筛出这些合数

当i是质数，就筛掉i与primes中所有质数的乘积；i是非质数，就筛掉i与primes中所有<= (i的最小质因子) 的乘积, 前提是都不超过最大要筛的上限

```cpp
bool st[N];
int primes[N];

void get_prime(int n){
    for(int i = 2;i <= n;i++) {
        if(!st[i]) primes[cnt++] = i;
        for(int j = 0;primes[j] <= n / i;j++) {
            st[primes[j] * i] = true;
            if(i % primes[j] == 0) break;
        }
    }
}
```

另外在质数类问题中，常常可以做一个sqrt(n)的范围缩减，然后用小区间的质数去标记更大区间的合数。可以参考的题目是[质数距离](./%E8%B4%A8%E6%95%B0%E8%B7%9D%E7%A6%BB.cpp)