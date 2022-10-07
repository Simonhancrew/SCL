package main

import (
	"bufio"
	. "fmt"
	"os"
)

func max(i, j int) int {
	if i < j {
		return j
	}
	return i
}

func main() {
	in := bufio.NewReader(os.Stdin)
	out := bufio.NewWriter(os.Stdout)
	defer out.Flush()
	const N = int(1e6 + 10)
	var l, r int
	primes, st := make([]int, N), make([]bool, N)
	cnt := 0
	get_primes := func(n int) {
		st = make([]bool, N)
		cnt = 0
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
	for {
		get_primes(50000)
		res, _ := Fscan(in, &l, &r)
		if res == 0 {
			break
		}
		st = make([]bool, N)
		for i := 0; i < cnt; i++ {
			p := primes[i]
			for j := max(p*2, (l+p-1)/p*p); j <= r; j += p {
				st[j-l] = true
			}
		}
		cnt = 0
		for i := 0; i <= r-l; i++ {
			if !st[i] && i+l >= 2 {
				primes[cnt] = i + l
				cnt++
			}
		}
		if cnt < 2 {
			Fprintln(out, "There are no adjacent primes.")
		} else {
			minp, maxp := 0, 0
			for i := 0; i+1 < cnt; i++ {
				d := primes[i+1] - primes[i]
				if d < primes[minp+1]-primes[minp] {
					minp = i
				}
				if d > primes[maxp+1]-primes[maxp] {
					maxp = i
				}
			}
			Fprintf(out, "%d,%d are closest, %d,%d are most distant.\n", primes[minp], primes[minp+1], primes[maxp], primes[maxp+1])
		}
	}

}
