## 双指针

主要适用的算法就是Sliding Windows,此时需要让右边界自增，然后每次检查左边界，做一个放缩。甚至可以基本总结出基础的流程

可以根据具体问题比较灵活的选择是否指针可以重合（就是区间里面可以一个元素都没有）

```cpp
for(int i = 0,j = 0,...;j < n;j++){
    update(state(i,j)); // 更新(i,j)区间中能得出的状态
    while(i < j && length(i,j)){ // 长度满足题目范围
        check(state(i,j)) dosomething; // 状态满足条件更新结论
        update(state(i + 1,j)); // 更新状态
        i++; // 缩减左边
    }
}
```