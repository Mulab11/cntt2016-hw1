// BEGIN CUT HERE

// END CUT HERE
#line 5 "TravellingPurchasingMan.cpp"
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

const int N = 50, M = 16, T = 604800, INF = 0x3f3f3f3f;

int g[N + 9][N + 9];// g[i][j] 表示i到j的最短路
int l[M + 9], r[M + 9], d[M + 9];
int f[1 << M][M];// f[i][j] 表示已经买过的状态为i，上一个买的是j的最短时间

std::vector<int> get(std::string s) {
	s += ' ';
	std::vector<int> ret;
	for(int i = 0; i < SZ(s); ++i) {
		int j = i, num = s[i] - '0';
		while(j < SZ(s) - 1 && s[j + 1] != ' ') num = num * 10 + s[++j] - '0';
		ret.pb(num);
		i = j + 1;
	}
	return ret;
}

struct TravellingPurchasingMan {
    int maxStores(int n, vector <string> info1, vector <string> info2) {
		int m = SZ(info1);
		for(int i = 0; i < m; ++i) {
			std::vector<int> p = get(info1[i]);
			l[i] = p[0], r[i] = p[1], d[i] = p[2];
		}
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < i; ++j)
				g[i][j] = g[j][i] = INF;
		for(int i = 0; i < SZ(info2); ++i) {
			std::vector<int> p = get(info2[i]);
			g[p[0]][p[1]] = g[p[1]][p[0]] = p[2];
		}
		// floyd 求最短路
		for(int k = 0; k < n; ++k)
			for(int i = 0; i < n; ++i)
				for(int j = 0; j < n; ++j)
					chkmin(g[i][j], g[i][k] + g[k][j]);
		memset(f, INF, sizeof f);
		// 初始化
		for(int i = 0; i < m; ++i)
			if(g[n - 1][i] <= r[i]) f[1 << i][i] = std::max(l[i], g[n - 1][i]) + d[i];
		int ans = 0;
		for(int i = 0; i < (1 << m); ++i) {
			int c = __builtin_popcount(i);
			for(int j = 0; j < m; ++j)
				if((i >> j & 1) && f[i][j] != INF) {
					chkmax(ans, c);// 更新答案
					for(int k = 0; k < m; ++k)
						if(!(i >> k & 1) && f[i][j] + g[j][k] <= r[k])
							chkmin(f[i | 1 << k][k], std::max(l[k], f[i][j] + g[j][k]) + d[k]);// 转移
				}
		}
		return ans;
    }
};
