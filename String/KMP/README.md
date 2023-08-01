## KMP

首先明确一个概念，kmp是在拿pattern串去匹配src串，这也就意味着src的长度大于pattern。

### 信息冗余

在拿pattern去匹配src中串的过程中，假如遇到不匹配的下一位，那么就要从头开始匹配，这就意味着之前匹配的信息就白白浪费了。但实质上，我不必回到pattern串的开头，重新匹配

```
s[i] != p[j]
此时，j回到p的开头，重新匹配
```

考虑这样一种情况

```
p[0, j]中，存在一个前缀p[0, k]和一个后缀p[j - k, j]相等，此时，我没必要回到p的开头，重新匹配，而是可以直接从p[k + 1]开始匹配。当p[k + 1]依然不等于s[i]的时候，我就可以继续使用这个方法，直到k = -1，此时，我就可以从p[0]开始匹配了。
```

因此我需要开始对pattern做一次处理，留下一个数组告诉我，每一位应该跳到之前的哪一位。

**此时，不难想到，我要做的就是拿pattern的前缀去匹配自己的后缀。**

等价地说，就是前缀p[0, x]，去想办法匹配s[1, y]

这里推荐的写法就是下标从1开始，这样可以少处理一下边界的情况。否则就要让ne[0] = -1

```
#include <iostream>

using namespace std;

const int N = 1e5 + 10,M = 1e6 + 10;

int n,m;
char p[N],s[M];
int ne[N];

int main(){
    cin >> n >> p + 1 >> m >> s + 1;
    for (int i = 2,j = 0;i <= n;i++){
        while(j && p[i] != p[j + 1]) j = ne[j];
        if(p[i] == p[j + 1]) j++;
        ne[i] = j;
    }
    for(int i = 1,j = 0;i <= m;i++){
        while(j && s[i] != p[j + 1]) j = ne[j];
        if (s[i] == p[j + 1]) j++;
        if (j == n){
            cout << i - j << ' ';
            j = ne[j];
        }
    }
    return 0;
}
```

