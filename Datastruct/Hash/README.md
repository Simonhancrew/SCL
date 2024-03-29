# Hash

哈希表，将键映射到值的数据结构。正常的哈希表算法有两种，一种是拉链法，一种是线性探测法。

## 拉链法

拉链法是指将哈希表的每个位置都指向一个链表，当发生哈希冲突时，将冲突的元素加入到链表中。这样做的好处是，不需要考虑哈希表的扩容问题，因为链表可以无限扩容。但是，拉链法的缺点是，当链表过长时，会导致哈希表的查找效率降低。

## 线性探测

线性探测法是指当发生哈希冲突时，将冲突的元素放入到下一个空的位置。这样做的好处是，不会出现链表过长的问题，但是，线性探测法的缺点是，当哈希表的装载因子过大时，会导致哈希表的查找效率降低。

## 字符串哈希

字符串哈希是指将字符串映射到一个整数的过程。字符串哈希的算法有很多种，常用的有BKDRHash、APHash、DJBHash、JSHash、RSHash、SDBMHash、PJWHash、ELFHash、BPHash、FNVHash、DEKHash、BKDRHash、SDBMHash、DJPHASH、OAAT、FNV1A、JAVA、MURMUR2、MURMUR3、SHA1、SHA256、SHA512、CRC32、ADLER32等。

如果单纯为了写代码过题目的话，可以考虑一个简单的做法

1. 将字符串看作一个P进制的数，为了减小冲突，这个P一般选择131或者13331，选择一个素数，这样可以保证P进制的数不会有冲突，因为大概率下这个字符串不会是另一个字符串的倍数

2. 选择一个Q，Q一般选择2^64，这样可以保证不会溢出，为了实现方便，一般都是开uint64_t的数组，这样就可以直接对Q取模

3. 将字符串看作P进制的数，然后对Q取模，这样就可以得到一个整数，这个整数就是字符串的哈希值

4. 如果要算(L, R)范围的一个数的哈希值，那么就是hash[R] - hash[L - 1] * P ^ (R - L + 1), 需要注意的是要把hash[L - 1]提升到和hash[R]一样的位数，这样才能相减

5. 为了计算方便，可以预先算出p的进制数，存在数组里p[i] => p^i

```cpp
ULL get(const std::string &x) {
  ULL res = 1;
  auto n  = x.size();
  for (auto i = 0; i < n; i++) {
    res = res * P + x[i];
  }
  return res;
}

bool is_same(const std::string& a, const std::string& b) {
  return get(a) == get(b);
}
```
