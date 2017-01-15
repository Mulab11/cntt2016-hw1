// BEGIN CUT HERE

// END CUT HERE
#line 5 "Orienteering.cpp"
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

const int R = 50, C = 50;
const int N = 300;
const int M = 2500;
const int d[][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

int n, m;// n表示检查点的个数，m表示非障碍点的个数
int id[R + 9][C + 9];// id[i][j] 表示第i行第j列的点的标号
bool ischk[M + 9];// ischk[i] = true 表示第i个非障碍点是检查点
vector<int> chk, adj[M + 9];// chk 存储了所有检查点的标号，adj[i] 存储了所有与i相邻的非障碍点的编号

int fa[M + 9], subchk[M + 9];// fa[i] 表示以0号非障碍点为根的树中i的父亲，subchk[i] 表示以i为根的子树内检查点的个数

double f1[N + 9], f2[N + 9];// f1[i] = C(i, K) / C(n, K), f2[i] = C(i, K - 2) / C(n - 2, K - 2) 其中K为题目中给定的要选出K个点

int dis[M + 9][M + 9];// dis[i][j] 表示第i个非障碍点到第j个非障碍点的距离
int g[N + 9][N + 9];// g[i][j] 表示第i个检查点到第j个检查点的距离

void dfs(int x, int fa) {// 求出subchk, fa
	subchk[x] = ischk[x], ::fa[x] = fa;
	for(int i = 0; i < SZ(adj[x]); ++i)
		if(adj[x][i] != fa) {
			dfs(adj[x][i], x);
			subchk[x] += subchk[adj[x][i]];
		}
}

void getdis(int x, int fa, int rt) {// 求出dis
	for(int i = 0; i < SZ(adj[x]); ++i)
		if(adj[x][i] != fa) {
			dis[rt][adj[x][i]] = dis[rt][x] + 1;
			getdis(adj[x][i], x, rt);
		}
}

double solve(int K) {
	dfs(0, -1);
	
	double edge = 0, diam = 0;// edge 表示树边个数的期望，diam 表示直径长度的期望

	f1[n] = 1;
	for(int i = n - 1; i >= 0; --i)
		f1[i] = f1[i + 1] / (i + 1) * (i + 1 - K);
	// f1[i] 表示从n个点中选出的K个点全部在i个点内的概率
	
	for(int i = 0; i < m; ++i)
		if(fa[i] != -1) {// 枚举每条边，计算出现在树中的概率
			int p1 = subchk[i], p2 = n - subchk[i];
			edge += 1 - f1[p1] - f1[p2];// 一条边出现在树中等价于这条边的两侧均有检查点，因此概率就是1 - 检查点分别全部在两侧的概率
		}

	f2[n - 2] = 1;
	for(int i = n - 3; i >= 0; --i)
		f2[i] = f2[i + 1] / (i + 1) * (i + 1 - K + 2);
	// f2[i] 表示从n - 2个点中选出的K - 2个点全在i个点内的概率

	for(int i = 0; i < m; ++i) {
		dis[i][i] = 0;
		getdis(i, -1, i);
	}
	// 求出所有点对之间的距离

	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			g[i][j] = dis[chk[i]][chk[j]];
	// 求出所有检查点之间的距离

	for(int i = 0; i < n; ++i)
		for(int j = i + 1; j < n; ++j) {// 枚举直径的两端
			int cnt = 0;
			for(int k = 0; k < n; ++k)
				if(k != i && k != j) {// 判断可以选择的点集
					if(g[i][k] > g[i][j] || (g[i][k] == g[i][j] && k < j)) continue;
					if(g[k][j] > g[i][j] || (g[k][j] == g[i][j] && k < i)) continue;
					// 每棵树我们将其计算在其字典序最小的直径上
					cnt++;
				}
			diam += g[i][j] * f2[cnt];// 因为固定了两个点，因此剩下K - 2个点只能在cnt中选择，概率就是f2[cnt]
		}

	diam *= (K * (K - 1.0)) / (n * (n - 1.0));// 之前计算的时候并没有考虑固定的两个点被选的概率，因此要乘上 C(n - 2, K - 2) / C(n, K)

	return edge * 2 - diam;// 对于一棵树最小的距离就是所有边 * 2 - 直径的长度
}

struct Orienteering {
    double expectedLength(vector <string> field, int K) {
		// 初始化
		chk.clear(), n = m = 0;
		memset(id, -1, sizeof id);
		memset(ischk, false, sizeof ischk);

		// 找出所有的非障碍点并且给每个点一个编号
		// 同时找出所有的检查点(check point)并标记
		int r = SZ(field), c = SZ(field[0]);
		for(int i = 0; i < r; ++i)
			for(int j = 0; j < c; ++j)
				if(field[i][j] != '#') {
					id[i][j] = m++;
					if(field[i][j] == '*') chk.pb(id[i][j]), n++, ischk[id[i][j]] = true;
				}

		// 相邻的非障碍点之间连边
		for(int i = 0; i < m; ++i) adj[i].clear();
		for(int i = 0; i < r; ++i)
			for(int j = 0; j < c; ++j)
				if(field[i][j] != '#')
					for(int k = 0; k < 4; ++k) {
						int ti = i + d[k][0], tj = j + d[k][1];
						if(ti >= 0 && ti < r && tj >= 0 && tj < c && field[ti][tj] != '#')
							adj[id[i][j]].pb(id[ti][tj]);
					}
		
		return solve(K);
    }
};
