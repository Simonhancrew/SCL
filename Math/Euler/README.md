## 欧拉函数和证明

$ \phi(n) $表示从[1,n - 1]中和n互质的数的个数

$$
    \phi(n) = n \times (1 - \frac{1}{p_1}) \times \dots \times (1 - \frac{1}{p_x})
$$
其中p是n的质因子

证明的方法用到了容斥原理，简述就是先从n个数中除去$ p_1, \dots p_n $的倍数。随后因为会误去两个质数乘积的倍数，所以需要加回来，随之多加回来了三个质数乘积的倍数，继续减去。

最后得到的公式就如原公式所示

显然有
$$
    \phi(1) = 1  \\
    \phi(n) = n - 1 \quad 其中n是质数\\
    如果gcd(a,b) = 1 \qquad   \phi(a \times b) = \phi(a) \times \phi(b)
$$

常用的求欧拉公式的方法，直接求的就分解质因数，然后套公式

还可以考虑用线性筛在求解质数的过程中把$\phi(n)$顺便求了

```cpp
int primes[N],phi[N],cnt;
bool st[N];

void get_primes(int n) 
{
    phi[1] = 1;
    for(int i = 2;i <= n;i++) 
    {
        if(!st[i]) 
        {
            primes[cnt++] = i;
            phi[i] = i - 1;
        }
        for(int j = 0;primes[j] <= n / i;j++) 
        {
            st[primes[j] * i] = true;
            if(i % primes[j] == 0) 
            {
                phi[i * primes[j]] = phi[i] * primes[j];
                break;
            }
            phi[primes[j] * i] = phi[i] * (primes[j] - 1);
        }
    }
```