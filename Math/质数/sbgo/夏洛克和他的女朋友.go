package main

import (
	"bufio"
	. "fmt"
	"os"
)

func main() {
	in := bufio.NewReader(os.Stdin)
	out := bufio.NewWriter(os.Stdout)
	defer out.Flush()
	const N = int(1e6 + 10)
	var n, cnt int
	st, primes := make([]bool, N), make([]int, N)
	getPrime := func(n int) {
		for i := 2; i <= n; i++ {
			if !st[i] {
				primes[cnt] = i
				cnt++
			}
			for j := 0; primes[j] <= n/i; j++ {
				st[primes[j]*i] = true
				if i%primes[j] == 0 {
					break
				}
			}
		}
	}
	getPrime(N - 1)
	Fscan(in, &n)
	if n <= 2 {
		Fprintln(out, 1)
	} else {
		Fprintln(out, 2)
	}

	for i := 2; i <= n+1; i++ {
		if st[i] {
			Fprint(out, 2, " ")
		} else {
			Fprint(out, 1, " ")
		}
	}
}
