# 单调栈

单调栈一般用来求取数组中一个数左边(右边)第一个比他大(小)的数的相关信息

常见的描述: 找到一个数下一个(上一个)比他更大(小)的数

常见的技巧:
  
  1. 单调栈里不仅能放值， 也能放下标
  
  2. 如果思考`当前的数的下一个更X的数`思路不是很好实现的话， 可以逆向思考， 比如`当前的数可以作为哪些数的下一个更X的数`答案，后者实现单调栈的模式不同， 遍历的值需要做一个defer更新

## 对于每一个数，找下一个比他更大的数

### 方法1，从右往左遍历，维护一个单调递减的栈

此时从右向左遍历数组arr， 因此还未遍历的区间[0, x]， 假设右边的区间[x + 1, z], x具备知道[x + 1, z]所有信息的能力， 但是不是所有的信息都会是有用的(因为我们只需要知道下一个更大的数)

假设此时[x + 1, z]中， 存在比arr[x]还要小的数， 是[x + 1, k], 在继续往左遍历的时候， 这部分数已经没有用了(因为针对[0, x - 1]的数， 如果找下一个更大的元素不是arr[x]的话， 一定也不会是[x + 1, k]里的数， 因为这里面的数更小)， 所以在针对arr[x]找数的时候需要及时处理掉过期的信息

因此需要维护一个数据结构， 这个数据结构需要有序， 且自底向上是大->小的， 这样才能第一时间找到符合要求的数， 且不符合要求的时候直接弹出过期的信息

### 方法2，从左往右遍历，维护一个单调递减的栈

从左往右遍历，如果当前的数比栈顶的数还要大，说明当前栈顶的数的下一个更大元素是当前遍历到的值，随后弹出栈顶，继续比较栈顶和当前值。
