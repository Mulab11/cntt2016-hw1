#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

int n, l, r, ans;
int cnt[8], set[8];
vector<int> point[8];
struct Edge{int x, y;};
int e[8];

struct Graph
{
#define IL inline
#define RG register
#define dmin(a, b) ((a) < (b) ? (a) : (b))
	static const int MaxN = 20, MaxM = 40;
	struct Pointer{int to, flow; Pointer *next, *rev;} *fir[MaxN], *cur[MaxN];
	Pointer mem[MaxM << 1], *tot;
	int n, S, T;
	IL void init(RG int _n, RG int _S, RG int _T)
	{
		n = _n, S = _S, T = _T;
		tot = mem;
		memset(fir + 1, 0, n * sizeof fir[0]);
	}
	IL void add(RG int a, RG int b, RG int f)
	{
		*++tot = (Pointer) {b, f, fir[a]}, fir[a] = tot;
		*++tot = (Pointer) {a, 0, fir[b]}, fir[b] = tot;
		fir[a]->rev = fir[b];
		fir[b]->rev = fir[a];
	}
	int dist[MaxN];
	IL bool bfs()
	{
		static int q[MaxN];
		RG int l = 1, r = 0, d;
		RG Pointer *k;
		memset(dist + 1, 0, n << 2);
		dist[q[++r] = T] = 1;
		while(l <= r)
		{
			d = dist[q[l]] + 1;
			for(k = fir[q[l++]]; k; k = k->next)
			{
				if(k->rev->flow && !dist[k->to])
					dist[q[++r] = k->to] = d;
			}
		}
		return dist[S];
	}
	int dfs(RG int i, RG int lim)
	{
		if(i == T || !lim) return lim;
		RG int want = dist[i] - 1;
		RG int used = 0, temp;
		for(RG Pointer* &k = cur[i]; k; k = k->next)
			if(dist[k->to] == want && k->flow)
			{
				temp = dfs(k->to, dmin(lim - used, k->flow));
				used += temp;
				k->flow -= temp;
				k->rev->flow += temp;
				if(used == lim) break;
			}
		return used;
	}
	IL int solve()
	{
		RG int ans = 0;
		while(bfs())
		{
			memcpy(cur + 1, fir + 1, n * sizeof *fir);
			ans += dfs(S, 1 << 30);
		}
		return ans;
	}
} G;

// 判断一组边的划分是否合法（利用网络流）
bool pig(vector<int> _cnt_A, vector<int> _cnt_B, vector< vector<int> > E)
{
	const int A = _cnt_A.size(), B = _cnt_B.size();
	int *cnt_A = _cnt_A.data(), *cnt_B = _cnt_B.data();
	for(int i = 0; i != A; ++i)
	{
		if(E[i].empty()) return 0;
		for(int j = 0; j != (int) E[i].size(); ++j)
		{
			if(!cnt_A[i]--)         return 0;
			if(!cnt_B[E[i][j]]--)   return 0;
		}
	}
	G.init(A + B + 2, A + B + 1, A + B + 2);
	const int mov_A = 0 + 1, mov_B = A + 1;
	int sum = 0;
	for(int i = 0; i != A; ++i) G.add(G.S, mov_A + i, cnt_A[i]), sum += cnt_A[i];
	for(int j = 0; j != B; ++j) G.add(mov_B + j, G.T, cnt_B[j]);
	for(int i = 0; i != A; ++i)
		for(int j = 0; j != (int) E[i].size(); ++j)
			G.add(mov_A + i, mov_B + E[i][j], 1 << 30);
	return G.solve() == sum;
}

// 每相邻两层之间可以选择的边集
vector< vector<Edge> > edge_set[8];

// 求方案数的 DFS
int Count, d[8], pre[1 << 8], path[8], top;
void dfs_calc(RG const int can)
{
	if(!can)
	{
		return (void) ++Count;
	}
	for(RG int S = can, T, next, p, q; S; S -= 1 << p)
	{
		p = pre[S];
		next = can - (1 << p);
		for(T = e[p]; T; T -= 1 << q) if(!--d[q = pre[T]]) next |= 1 << q;
		dfs_calc(next);
		for(T = e[p]; T; T -= 1 << q) ++d[q = pre[T]];
	}
}

// 枚举分层图的 DFS
void dfs_edge(int s)
{
	if(!s)
	{
		// 建图完毕
		Count = 0;
		int can = 0;
		for(int i = 0; i != n; ++i) if(!d[i]) can |= 1 << i;
		dfs_calc(can);
		if(l <= Count && Count <= r) ++ans;
		return;
	}
	for(RG int k = 0; k != (int) edge_set[s].size(); ++k)
	{
		// 清空 s 的出边
		for(int i = 0; i != (int) point[s].size(); ++i)
			e[point[s][i]] = 0;
		// 清空 s - 1 的入度
		for(int i = 0; i != (int) point[s - 1].size(); ++i)
			d[point[s - 1][i]] = 0;
		
		// 加入现在的边
		Edge *edge = edge_set[s][k].data();
		for(int i = 0; i != (int) edge_set[s][k].size(); ++i)
		{
			e[edge[i].x] |= 1 << edge[i].y;
			++d[edge[i].y];
		}
		
		dfs_edge(s - 1);
	}
}

// 枚举划分
void dfs_set(int i, int u)
{
	if(i == n)
	{
		// 划分枚举完毕
		// 枚举排列
		int perm[u], sum[u];
		for(int i = 0; i != u; ++i) perm[i] = i, sum[i] = 0;
		for(int i = 0; i != n; ++i) sum[set[i]] += cnt[i];
		do
		{
			// 先判断可行性
			for(int i = 1; i != u; ++i)
				if(sum[perm[i - 1]] < sum[perm[i]])
					goto skipped;
			for(int i = 0; i != u; ++i)
			{
				point[i].clear();
				for(int j = 0; j != n; ++j)
					if(perm[i] == set[j]) point[i].push_back(j);
			}
			
			// 考虑相邻两层之间，有多少边集是可以选择的
			for(int s = 1; s != u; ++s)
			{
				edge_set[s].clear();
				const int A = point[s].size(), B = point[s - 1].size();
				const int *pa = point[s].data(), *pb = point[s - 1].data();
				vector<int> cnt_A; for(int i = 0; i != A; ++i) cnt_A.push_back(cnt[pa[i]]);
				vector<int> cnt_B; for(int j = 0; j != B; ++j) cnt_B.push_back(cnt[pb[j]]);
				static Edge edge[20];
				int M = 0;
				for(int i = 0; i != A; ++i) for(int j = 0; j != B; ++j)
					edge[M++] = (Edge) {i, j};
				for(int S = 0; S != (1 << M); ++S)
				{
					vector< vector<int> > E(A, vector<int>());
					for(int k = 0; k != M; ++k) if(S & (1 << k)) E[edge[k].x].push_back(edge[k].y);
					if(pig(cnt_A, cnt_B, E))
					{
						vector<Edge> cur;
						for(int k = 0; k != M; ++k) if(S & (1 << k))
							cur.push_back((Edge) {pa[edge[k].x], pb[edge[k].y]});
						edge_set[s].push_back(cur);
					}
				}
				if(edge_set[s].empty()) goto skipped;
			}
			// 枚举每一层取的边
			memset(e, 0, n << 2);
			memset(d, 0, n << 2);
			dfs_edge(u - 1);
		skipped: ;
		}
		while(next_permutation(perm, perm + u));
		return;
	}
	int &k = set[i++];
	for(k = 0; k != u; ++k) dfs_set(i, u);
	dfs_set(i, k + 1);
}

class CosmicBlocks
{
public:
	int getNumOrders(vector<int> _cnt, int _l, int _r)
	{
		n = _cnt.size(), l = _l, r = _r;
		for(int i = 0; i != n; ++i) cnt[i] = _cnt[i];
		for(int i = 1; i != (1 << n); ++i)
			pre[i] = __builtin_ctz(i);
		// 似乎答案不大，可以暴力统计
		// 首先枚举 n 种颜色分层的划分
		dfs_set(0, 0);
		return ans;
	}
}   user;
