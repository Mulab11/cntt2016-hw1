// BEGIN CUT HERE

// END CUT HERE
#line 5 "TPS.cpp"
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
const int INF = 1e9;

int n;
std::vector<int> adj[N + 9];
int f[N + 9][N + 9][2];

int dp(int x, int fa, int t) {// f[x][fa][t]表示以x为根的子树，x的父亲为fa，子树中是否有beacon的最小值
	int &val = f[x][fa][t];
	if(val != -1) return val;
	int c = 0, sum = 0, p;
	// sum表示子树全有beacon的和，p表示x的某个孩子，c表示孩子个数
	for(auto s : adj[x])
		if(s != fa) {
			sum += dp(s, x, 1);
			dp(s, x, 0);
			c++, p = s;
		}
	if(!c) val = t;// 叶子节点
	else if(c == 1) {
		if(t) {// 子树有beacon
			val = 1 + std::min(f[p][x][0], f[p][x][1]);// 选x
			if(fa != n) chkmin(val, f[p][x][1]);// 当x不为根的情况下能够不选x
		}
		else val = f[p][x][0];// 子树没有beacon
	}
	else {
		if(t) {// 有beacon
			int tmp = sum;
			for(auto s : adj[x])
				if(s != fa)
					chkmin(tmp, sum - f[s][x][1] + f[s][x][0]);// 某棵子树可能没有beacon
			val = 1 + tmp;// 选根
			if(fa != n) val = tmp;// 不为根的时候可以不选x
		}
		else val = INF;// 如果多叉且子树没有beacon，那么无解
	}
	return val;
}

struct TPS {
    int minimalBeacons(vector <string> linked) {
		n = SZ(linked);
		if(n == 1) return 0;
		for(int i = 0; i < n; ++i) adj[i].clear();
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				if(linked[i][j] == 'Y')
					adj[i].pb(j);// 构造邻接表
		memset(f, -1, sizeof f);
		// 枚举根dp
		int ans = dp(0, n, 1);
		for(int i = 1; i < n; ++i)
			chkmin(ans, dp(i, n, 1));
		return ans;
    }
};
