package main

import (
	"bufio"
	. "fmt"
	"os"
)

const P = 100003

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
	var m, n int
	Fscan(in, &m, &n)
	Fprintln(out, (qpow(m, n)-m*qpow(m-1, n-1)%P+P)%P)
}
