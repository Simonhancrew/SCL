package main

import (
	"bufio"
	. "fmt"
	"os"
)

// go带缓存读写bufio

func main() {
	in := bufio.NewReader(os.Stdin)
	out := bufio.NewWriter(os.Stdout)
	defer out.Flush()

	var m, n int
	var p, s string

	Fscan(in, &n, &p)

	ne := make([]int, n+1)
	p = " " + p

	for i, j := 2, 0; i <= n; i++ {
		for j != 0 && p[i] != p[j+1] {
			j = ne[j]
		}
		if p[i] == p[j+1] {
			j++
		}
		ne[i] = j
	}
	Fscan(in, &m, &s)
	s = " " + s

	for i, j := 1, 0; i <= m; i++ {
		for j != 0 && s[i] != p[j+1] {
			j = ne[j]
		}
		if s[i] == p[j+1] {
			j++
		}
		if j == n {
			Fprint(out, i-j, " ")
			j = ne[j]
		}
	}
}
