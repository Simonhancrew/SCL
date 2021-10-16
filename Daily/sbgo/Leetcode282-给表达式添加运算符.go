package sbgo

var path []byte
var res []string

func addOperators(num string, target int) []string {
	path = make([]byte, 100)
	res = []string{}
	dfs(num, 0, 0, 0, 1, target)
	return res
}

func dfs(num string, u, leng, a, b, target int) {
	if u == len(num) {
		if a == target {
			res = append(res, string(path[0:leng-1]))
		}
		return
	}
	c := 0
	for i := u; i < len(num); i++ {
		c = c*10 + (int)(num[i]-'0')
		path[leng] = num[i]
		leng++
		path[leng] = '+'
		dfs(num, i+1, leng+1, a+b*c, 1, target)
		if i+1 < len(num) {
			path[leng] = '-'
			dfs(num, i+1, leng+1, a+b*c, -1, target)
			path[leng] = '*'
			dfs(num, i+1, leng+1, a, b*c, target)
		}
		if num[u] == '0' {
			break
		}
	}
}
