def comb(n, m):
	ret = 1
	for i in xrange(m):	ret *= n - i
	for i in xrange(m):	ret /= i + 1
	return ret

def calc(k, t, x, N):
	n = min(x, k + 2)
	f = [0]
	for i in xrange(n):
		f.append(f[i] + comb(N - (i + 1) * t + k, k))
	if x <= n:	return f[x]
	A = 0
	B = 1
	for i in xrange(1, n + 1):
		C = f[i]
		D = 1
		for j in xrange(1, n + 1):
			if i != j:
				C *= x - j
				D *= i - j
		A = A * D + B * C
		B *= D
	return A / B

def solve(p, n, m):
	ans = 0
	k = p
	while k <= n:
		ans += calc(m, k, n / k, n)
		k *= p
	return ans

class MegaFactorial:
	def countTrailingZeros(self, n, m, k):
		m -= 1
		mod = 10 ** 9 + 9
		if k == 2:	return solve(2, n, m)  % mod
		if k == 4:	return solve(2, n, m) / 2  % mod
		if k == 8:	return solve(2, n, m) / 3  % mod
		if k == 3 or k == 6:	return solve(3, n, m)  % mod
		if k == 9:	return solve(3, n, m) / 2  % mod
		if k == 5 or k == 10:	return solve(5, n, m)  % mod
		if k == 7:	return solve(7, n, m)  % mod
