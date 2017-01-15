// BEGIN CUT HERE

// END CUT HERE
#line 5 "PenguinEmperor.cpp"
#include <bits/stdc++.h>

using namespace std;

#define SZ(x) (int)(x).size()
#define pb push_back
#define mp make_pair
#define fi first
#define se second

typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<double> VD;
typedef long long ll;
typedef pair<int,int> pii;

template<class T>inline void chkmax(T &x, const T &y) {if(x < y) x = y;}
template<class T>inline void chkmin(T &x, const T &y) {if(x > y) x = y;}

const int N = 350;
const int MOD = 1000000007;

int n;
ll d;
int f[N + 9][N + 9];// f[i][j] 表示第i天到j的方案数
int g[N + 9], p[N + 9];

void op(int *p, int *q) {// 将两种方案数卷积起来
	int h[N + 9] = {0};
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			(h[(i + j) % n] += (ll)p[i] * q[j] % MOD) %= MOD;
	std::copy(h, h + n, p);
}

struct PenguinEmperor {
    int countJourneys(int _n, long long _d) {
		memset(f, 0, sizeof f), memset(p, 0, sizeof p);
		n = _n, d = _d;
		// dp 出 f 的值
		f[0][0] = 1;
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				if(f[i][j]) {
					(f[i + 1][(j + (i + 1)) % n] += f[i][j]) %= MOD;
					if((j + (i + 1)) % n != (j - (i + 1) + n) % n)// 如果顺或逆走到同一个点，算同一个方案
						(f[i + 1][(j - (i + 1) + n) % n] += f[i][j]) %= MOD;
				}
		for(int i = 0; i < n; ++i) g[i] = f[n][i];
		ll x = d / n, y = d % n;
		// 每n个一个周期，因此可以快速幂
		p[0] = 1;
		while(x) {
			if(x & 1) op(p, g);
			op(g, g), x >>= 1;
		}
		op(p, f[y]);// 加上余数的贡献
		return p[0];
    }
};
