package main

import (
	"fmt"
	"sort"
)

// from Leetcode1235
// 线性dp + 二分。
// 首先按照结束时间将整体排序,f[i]表示前i个item的最大利润
// 针对i，有选和不选两种可能，分别讨论，选的时候，只要前面的item的右边界
// 是小于当前i的左边界的就可以选择。这里可以用二分找到之前右边界小于等于i左边界的j
// f[i] = max(f[i], f[j] + arr[i].profit),
// 其中i初始化f[i] = max(f[i - 1], arr[i].profit)

func jobScheduling(startTime []int, endTime []int, profit []int) int {
	n, arr := len(startTime), [][]int{}
	for i := 0; i < n; i++ {
		arr = append(arr, []int{startTime[i], endTime[i], profit[i]})
	}
	sort.Slice(arr, func(i, j int) bool {
		return arr[i][1] < arr[j][1]
	})
	max := func(i, j int) int {
		if i < j {
			return j
		}
		return i
	}
	f := make([]int, n)
	f[0] = arr[0][2]
	for i := 1; i < n; i++ {
		f[i] = max(f[i-1], arr[i][2])
		if arr[i][0] >= arr[0][1] {
			l, r := 0, i-1
			for l < r {
				mid := (l + r + 1) >> 1
				if arr[mid][1] <= arr[i][0] {
					l = mid
				} else {
					r = mid - 1
				}
			}
			f[i] = max(f[i], f[r]+arr[i][2])
		}
	}
	return f[n-1]
}

func main() {
	startTime, endTime, profit := []int{1, 2, 3, 3}, []int{3, 4, 5, 6}, []int{50, 10, 40, 70}
	res := jobScheduling(startTime, endTime, profit)
	fmt.Println(res)
}
