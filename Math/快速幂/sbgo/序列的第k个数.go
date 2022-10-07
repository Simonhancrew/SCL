package main

import (
	"bufio"
	. "fmt"
	"os"
)

const P = 200907

func qpow(a, b int) int {
	res := 1
	for b != 0 {
		if b&1 == 1 {
			res = res * a % P
		}
		a = a * a % P
		b >>= 1
	}
	return res
}

func main() {
	in := bufio.NewReader(os.Stdin)
	out := bufio.NewWriter(os.Stdout)
	defer out.Flush()
	var t int
	Fscan(in, &t)
	for t != 0 {
		a, b, c, k := 0, 0, 0, 0
		Fscan(in, &a, &b, &c, &k)
		if a+c == 2*b {
			Fprintln(out, (a+(b-a)*(k-1))%P)
		} else {
			Fprintln(out, a*qpow(b/a, k-1)%P)
		}
		t--
	}
}
