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

const int N = 36;
const int K = 1300;
const int MOD = 1000000007;

int n;
int f[K + 9], g[K + 9];
int C[K + 9][K + 9];

int get(const std::vector<int> &c, int k) {// 将牌按大小顺序任意放进去的方案数
	int ret = 1;
	for(auto i : c)
		ret = (ll)ret * C[k][i] % MOD;
	return ret;
}

class LISNumber {
public:
	int count(std::vector<int> c, int k) {
		n = SZ(c);
		for(auto i : c)
			if(i > k) return 0;// 每个c[i]都要 <= k, 否则不够放
		//预处理组合数
		for(int i = 0; i <= K; ++i) {
			C[i][0] = 1;
			for(int j = 1; j <= i; ++j)
				C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
		}
		int sum = std::accumulate(c.begin(), c.end(), 0);// 总共的card数
		if(sum < k) return 0;
		for(int i = 1; i <= k; ++i) {
			f[i] = get(c, i);
			for(int j = 1; j < i; ++j)// 去掉大小为0的块
				(f[i] += MOD - (ll)f[i - j] * C[i][j] % MOD) %= MOD;
			g[i] = f[i];
			for(int j = 1; j < i; ++j)// 去掉实际块数 < i的方案数
				(g[i] += MOD - (ll)g[j] * C[sum - j][i - j] % MOD) %= MOD;
		}
		return g[k];
	}
};
