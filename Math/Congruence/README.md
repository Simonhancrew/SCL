## 同余方程

形如 $  ax \equiv c\pmod{b} $的方程称为**线性同余方程**(Congruence Equation)

有两种方法可以求出同余方程的解

1. $ax + b = c$与$ ax \equiv c\pmod{b} $ 等价，有正数解的充要条件是$ gcd(a,b) | c$

扩展gcd的推导：
$$ 
ax + by = gcd(a,b) \\
如果b = 0,x = 1,y = 0 \\
$$

针对更一般的情况 
$$
ax + by = gcd(a,b) = gcd(b,a \% b) \\ 
bx^{\prime} + a \% b \times y^{\prime} = gcd(b,a \% b) \\
bx^{\prime} + (a - \lfloor\frac{a}{b}\rfloor \times b)y^{\prime} =  gcd(b,a \% b) \\
ay^{\prime} + b(x^{\prime} - \lfloor\frac{a}{b}\rfloor \times y^{\prime}) = gcd(b,a \% b) = gcd(a,b)\\
$$
所以不难得到
$$
    x = y^{\prime} \quad y = x^{\prime} - \lfloor\frac{a}{b}\rfloor \times y^{\prime}
$$
可以采用一个递归的方法算出下一层的$x^{\prime}$和$y^{\prime}$
```cpp
int exgcd(int a, int b, int &x, int &y){//返回gcd(a,b) 并求出解(引用带回)
    if(b==0){
        x = 1, y = 0;
        return a;
    }
    int x1,y1,gcd;
    gcd = exgcd(b, a%b, x1, y1);
    x = y1, y = x1 - a/b*y1;
    return gcd; 
}
```
同时针对更普通的情况$ax + by = c$有解等价于`gcd(a,b) | c`。可以得到一个更一般的解其中的$x^{\prime}$是针对之前同余方程的解
$$
x = x^{\prime} + k \times \frac{b}{d} \quad
y = y^{\prime} + k \times \frac{a}{d}
$$

## gcd的理解

假设现在有161和63两个数，求取这两个数的最大公因数。gcd的原理就是不端拆解，首先161拆成63 + 98, 其中，63和161都要能被公因数x整除，所以不难知道要找的公因子其实在98里，继续找98和63的公因子就行了。代码实现的trick，参数是a和b，有0直接结束，假如判断的是a，就把a换到b，b % a换到a。

```
int gcd(int a, int b) {
    return a ? gcd(b % a, a) : b;
}
```