#include <bits/stdc++.h>

#define ll long long
#define uint unsigned

#define debug(...) fprintf(stderr, __VA_ARGS__)

#define SZ(x) ((int)(x).size())
#define pb push_back

#define pii std::pair<int,int>
#define mp std::make_pair
#define fi first
#define se second

template<class T>inline void chkmax(T &x, const T &y) {if(x < y) x = y;}
template<class T>inline void chkmin(T &x, const T &y) {if(y < x) x = y;}

template<class T>
inline void read(T &x) {
	char c;int f = 1;x = 0;
	while(((c = getchar()) < '0' || c > '9') && c != '-');
	if(c == '-') f = -1;else x = c - '0';
	while((c = getchar()) >= '0' && c <= '9') x = x * 10 + c - '0';
	x *= f;
}

const int M = 1e6;
const int MOD = 1000000007;

int fac[2 * M + 9];
int inv[2 * M + 9];
int pw2[2 * M + 9];

int fpm(int a, int b) {
	int ret = 1;
	while(b) {
		if(b & 1) ret = (ll)ret * a % MOD;
		a = (ll)a * a % MOD, b >>= 1;
	}
	return ret;
}

int C(int n, int m) {
	if(0 <= m && m <= n) return (ll)fac[n] * inv[m] % MOD * inv[n - m] % MOD;
	else return 0;
}

int calc(int r, int g, int b) {
	int ret = 0;
	for(int n = r - 1; n <= r; ++n)// 如果r结尾，那么r - 1段，否则r段
		for(int x0 = 0; x0 <= n; ++x0) {// x0表示gb..gb和bg...bg的个数
			if((n + g - b - x0) & 1) continue;
			int x1 = (n + g - b - x0) >> 1, x2 = (n - g + b - x0) >> 1;// 求出x1, x2分别表示形如gb...g和bg...b的串的个数
			if(x1 < 0 || x2 < 0) continue;
			int cur = (ll)fac[n] * inv[x0] % MOD * inv[x1] % MOD * inv[x2] % MOD * pw2[x0] % MOD;// 将x0, x1, x2排列的方案数 * x0每个串都有两种情况
			int gg = g - x0 - x1;
			cur = (ll)cur * C(gg + n - 1, n - 1) % MOD;// 把剩下的数填到段里去的方案数
			(ret += cur) %= MOD;
		}
	return ret;
}

int solve(int r, int g, int b) {
	int ans = calc(r, g, b);// r开头
	(ans += calc(g, b, r)) %= MOD;// g开头
	(ans += calc(b, r, g)) %= MOD;// b开头
	return ans;
}

class LittleElephantAndBoard {
public:
	int getNumber(int m, int R, int G, int B) {
		if((R + G + B) & 1) return 0;// 奇偶性判定
		if(R + G + B != 2 * m) return 0;// 和判定
		fac[0] = 1;
		for(int i = 1; i <= 2 * m; ++i) fac[i] = (ll)fac[i - 1] * i % MOD;// 预处理阶乘
		inv[2 * m] = fpm(fac[2 * m], MOD - 2);
		for(int i = 2 * m - 1; i >= 0; --i) inv[i] = (ll)inv[i + 1] * (i + 1) % MOD;// 预处理阶乘逆元
		pw2[0] = 1;
		for(int i = 1; i <= 2 * m; ++i) pw2[i] = pw2[i - 1] * 2 % MOD;// 预处理2的幂
		int r = (G + B - R) >> 1;// 将列GB变成r
		int g = (R + B - G) >> 1;// 将列RB变成g
		int b = (R + G - B) >> 1;// 将列RG变成b
		return (solve(r, g, b) << 1) % MOD;// 第一个的上下顺序有两种，后面格子的上下顺序都只和第一个有关
	}
};
