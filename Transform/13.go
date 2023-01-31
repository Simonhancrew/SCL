package main

import(
  "os"
  "bufio"
  ."fmt"
)

// 记录当前每个月第一天到1900年第一天的间隔， 13号是周几就是days % 7
// 对每一年枚举每个月，不断往前推就可以了

var month [13]int =  [13]int{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
var weekdays [7]int
var n int

func main() {
  in := bufio.NewReader(os.Stdin)
  out := bufio.NewWriter(os.Stdout)
  defer out.Flush()
  
  Fscan(in, &n)
  years, days := 1900, 0
  for i := 0;i < n;i++ {
    for j := 1;j <= 12;j++ {
      weekdays[(days + 12) % 7]++;
      days += month[j]
      if j == 2 {
        if years % 4 == 0 && years % 100 != 0 || years % 400 == 0 {
          days++
        }
      }
    }    
    years++
  }
  for i, j := 5, 0;j < 7;i, j = i + 1, j + 1 {
    Fprintf(out, "%d ", weekdays[i % 7])
  }
}

