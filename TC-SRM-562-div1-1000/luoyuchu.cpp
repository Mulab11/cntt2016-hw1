#include <bits/stdc++.h>
using namespace std;

#define dig(...) fprintf(stderr, __VA_ARGS__)

template <class TAT>
void Ckmin(TAT &a, const TAT &b)
{
	if (a > b) a = b;
}
template <class TAT>

void Ckmax(TAT &a, const TAT &b)
{
	if (a < b) a = b;
}

typedef long long LL;

using namespace std;

const int maxn = 45;
const int mod = 1e9+9;

int n, K;
int C[maxn][maxn], jc[maxn];
bool mat[maxn][maxn];
struct edge
{
	int to, next;
	edge() {}
	edge(int _t, int _n):to(_t), next(_n) {}
}e[maxn * 2];
int head[maxn], et = -1;
int fa[maxn], size[maxn], dfn[maxn], rak[maxn], Index;
int g[maxn];
int f[maxn][maxn][maxn];

void Prepare()//预处理组合数及排列数
{
	for (int i = 0; i < maxn; ++i) {
		C[i][0] = 1;
		for (int j = 1; j <= i; ++j) {
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
		}
	}
	jc[0] = 1;
	for (int i = 1; i < maxn; ++i) jc[i] = (LL)jc[i - 1] * i % mod;
}

void Dfs1(int p)//Dfs1求g[i],g[i]表示以i为根的子树，如果分配给他标号为1~size[i]的标号，有多少中方法使得孩子的标号总比父亲大
{
	size[p] = 1;
	dfn[p] = ++Index;
	for (int i = head[p]; i != -1; i = e[i].next) {
		if (fa[p] != e[i].to) {
			fa[e[i].to] = p;
			Dfs1(e[i].to);
			size[p] += size[e[i].to];
		}
	}
	int res = size[p] - 1;
	g[p] = 1;
	for (int i = head[p]; i != -1; i = e[i].next) {
		if (fa[p] != e[i].to) {
			g[p] = (LL)g[p] * C[res][size[e[i].to]] % mod * g[e[i].to] % mod;
			res -= size[e[i].to];
		}
	}
}

LL Dp1()
{
	int need = n - K;
	memset(f, 0, sizeof(f));
	f[1][0][0] = 1;//f[i][j][k]表示当前到了dfs序为i的点，1~k的标号分配了j个，n-k+1~n分配了k个的方案数
	for (int i = 1; i <= n; ++i) rak[dfn[i]] = i;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j <= need; ++j) {
			for (int k = 0; k <= need; ++k) {
				if (f[i][j][k] > 0) {//转移是枚举但前为根的子树是分配给谁或者不分配
					f[i + 1][j][k] = (f[i + 1][j][k] + f[i][j][k]) % mod;
					f[i + size[rak[i]]][j + size[rak[i]]][k] = (f[i + size[rak[i]]][j + size[rak[i]]][k] + (LL)f[i][j][k] * g[rak[i]] % mod * C[need - j][size[rak[i]]] % mod) % mod;
					f[i + size[rak[i]]][j][k + size[rak[i]]] = (f[i + size[rak[i]]][j][k + size[rak[i]]] + (LL)f[i][j][k] * g[rak[i]] % mod * C[need - k][size[rak[i]]] % mod) % mod;
				}
			}
		}
	}
	return f[n + 1][need][need];
}	

int Work1(int Root)
{
	memset(fa, 0, sizeof(fa));
	Index = 0;
	Dfs1(Root);//Dfs1为求g[i],g[i]表示以i为根的子树，如果分配给他标号为1~size[i]的标号，有多少中方法使得孩子的标号总比父亲大
	return (LL)Dp1() * jc[K * 2 - n - 1] % mod;//乘以固定点的排列
}

int Work2(int Root)//对于一条链，枚举中间链的一端，找出这条链，直接将两边的标号分配给两个子树
{
	static vector<int> son[maxn];
	int down[maxn], need, ans = 0;
	memset(fa, 0, sizeof(fa));
	Index = 0;
	Dfs1(Root);
	for (int i = 1; i <= n; ++i) son[i].clear();
	for (int i = 1; i <= n; ++i) {
		if (i != Root) {
			son[fa[i]].push_back(i);
		}
	}
	if (son[Root].size() != 2) return 0;
	need = n - K * 2;
	for (int T = 0; T < 2; ++T) {
		down[T] = son[Root][T];
		for (int i = 1; i < need; ++i) {
			if (son[down[T]].size() != 1) {
				down[T] = -1;
				break;
			}
			down[T] = son[down[T]][0];
		}
		if (down[T] != -1 && size[down[T]] == K) {
			ans = (ans + (LL)g[down[T]] * g[son[Root][T ^ 1]] % mod) % mod;;
		}
	}
	return ans;
}

int Solve()
{
	int Ans = 0;
	if (K == 1) {//如果K为1,则答案为n!
		Ans = jc[n];
	}
	else if (K * 2 > n) {//如果K*2>n则有固定点
		for (int i = 1; i <= n; ++i) {
			(Ans += Work1(i)) %= mod;
		}
	}
	else if (K * 2 == n) {//如果K*2==n则正好两颗大小为n/2的子树
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				if (i != j && mat[i][j] == 1) {
					fa[i] = j;
					fa[j] = i;
					Dfs1(i); Dfs1(j);
					if (size[i] == size[j]) {
						Ans = (Ans + (LL)g[i] * g[j] % mod) % mod;
					}
				}
			}
		}
	}
	else {//否则，中间一条链链接
		for (int i = 1; i <= n; ++i) {
			(Ans += Work2(i)) %= mod;
		}
	}
	return Ans;
}

class InducedSubgraphs {
    public:
    int getCount(vector<int> edge1, vector<int> edge2, int k) {
		n = edge1.size() + 1;
		K = k;
		memset(head, -1, sizeof(head));
		et = -1;
		memset(mat, 0, sizeof(mat));
		for (int i = 0; i < n - 1; ++i) {//建边
			e[++et] = edge(edge1[i] + 1, head[edge2[i] + 1]), head[edge2[i] + 1] = et;
			e[++et] = edge(edge2[i] + 1, head[edge1[i] + 1]), head[edge1[i] + 1] = et;
			mat[edge1[i] + 1][edge2[i] + 1] = 1;
			mat[edge2[i] + 1][edge1[i] + 1] = 1;
		}
		Prepare();//预处理组合数
		return Solve();//分类解决问题
    }
};

