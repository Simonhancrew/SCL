package main

import (
	"bufio"
	. "fmt"
	"os"
)

const N = 1e6 + 10
const P = 1e9 + 7

var cnt, n int
var st [N]bool
var primes [N]int

func get_prime(n int) {
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

func main() {
	in := bufio.NewReader(os.Stdin)
	out := bufio.NewWriter(os.Stdout)
	defer out.Flush()
	Fscan(in, &n)
	get_prime(n)
	res := 1
	for i := 0; i < cnt; i++ {
		s, p := 0, primes[i]
		for j := n; j > 0; j /= p {
			s += j / p
		}
		res = res * (2*s + 1) % P
	}
	Fprintln(out, res)
}
