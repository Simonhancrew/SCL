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
	st, primes := make([]bool, N), make([]int, N)
	cnt := 0
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
	n := -1
	for n != 0 {
		Fscan(in, &n)
		for i := 0; primes[i] < n; i++ {
			a := primes[i]
			b := n - a
			if !st[b] {
				Fprintf(out, "%d = %d + %d\n", n, a, b)
				break
			}
		}
	}
}
