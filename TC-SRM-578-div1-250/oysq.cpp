// BEGIN CUT HERE

// END CUT HERE
#line 5 "GooseInZooDivOne.cpp"
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

const int N = 50;
const int V = N * N;
const int MOD = 1000000007;

std::vector<pii> bird;
int fa[V + 9], sz[V + 9];
std::vector<int> w;
int f[V + 9][2];

int find(int x) {// 并查集找祖先
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}

struct GooseInZooDivOne {
    int count(vector <string> field, int dist) {
		bird.clear();
		int n = SZ(field), m = SZ(field[0]);
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
				if(field[i][j] == 'v')
					bird.pb(mp(i, j));
		// 将所有曼哈顿距离在dist以内的点缩起来
		for(int i = 0; i < SZ(bird); ++i) fa[i] = i, sz[i] = 1;
		for(int i = 0; i < SZ(bird); ++i)
			for(int j = 0; j < i; ++j)
				if(abs(bird[i].fi - bird[j].fi) + abs(bird[i].se - bird[j].se) <= dist) {
					int u = find(i), v = find(j);
					if(u != v) fa[u] = v, sz[v] += sz[u];
				}
		// 每个缩起来的点的种类必须相同，因此把每个缩起来的大点的大小弄出来
		w.clear();
		for(int i = 0; i < SZ(bird); ++i)
			if(find(i) == i) w.pb(sz[i]);
		// dp出goose数量为偶数的方案数
		f[0][0] = 1;
		for(int i = 1; i <= SZ(w); ++i) {
			int t = w[i - 1] & 1;
			f[i][0] = (f[i - 1][0 ^ t] + f[i - 1][0]) % MOD;
			f[i][1] = (f[i - 1][1 ^ t] + f[i - 1][1]) % MOD;
		}
		return (f[SZ(w)][0] + MOD - 1) % MOD;
    }
};
