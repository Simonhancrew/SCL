## xor运算的技巧

1. 数组中除target外出现偶数次，target出现奇数次。这类题目直接异或整体就可以得到target

2. 数组中x，y出现一次，其余的数出现偶数次。这类问题直接xor整体，然后lowbit算出x和y的二进制表示中第一个不一样的位，随后针对这个不一样的位，在整体中再xor一次。具体的，如果num & lowbit != 0, 则放入组x，否则放入组y

3. 上述题目可以有变种，即别的数都出现一次，但是告诉了数的范围，在数组后面补数，构造偶数次,随后做法同上。
