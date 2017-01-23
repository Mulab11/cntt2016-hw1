#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 15, MAXM = 55, INF = 0x3f3f3f3f;

struct Dinic{
	struct Edge{
		int n, p, r;
		void var(int a, int b, int c){
			n = a, p = b, r = c;
		}
	}edges[MAXM << 1];
	int g[MAXN], cur[MAXN], d[MAXN], s, t, edgeSize;
	queue <int> q;
	void init(int s_, int t_){
		memset(g, 0, sizeof(g));
		edgeSize = 1, s = s_, t = t_;
	}
	void addEdge(int u, int v, int c){
		edges[++ edgeSize].var(v, g[u], c);
		g[u] = edgeSize;
		edges[++ edgeSize].var(u, g[v], 0);
		g[v] = edgeSize;
	}
	bool bfs(){
		int now, p;
		memset(d, 0, sizeof(d));
		q.push(s); d[s] = 1;
		while(!q.empty()){
			now = q.front(); q.pop();
			for(p = cur[now] = g[now]; p; p = edges[p].p)
				if(!d[edges[p].n] && edges[p].r){
					d[edges[p].n] = d[now] + 1;
					q.push(edges[p].n);
				}
		} return d[t];
	}
	int dfs(int x, int a){
		if(x == t || !a) return a;
		int f, flow = 0;
		for(int &p = cur[x]; p; p = edges[p].p)
			if(d[edges[p].n] == d[x] + 1 && (f = dfs(edges[p].n, min(a, edges[p].r)))){
				flow += f, edges[p ^ 1].r += f;
				edges[p].r -= f; if(!(a -= f)) break;
			}
		return flow;
	}
	int solve(){
		int ret = 0;
		while(bfs()) ret += dfs(s, INF);
		return ret;
	}
}maxFlow;
class CosmicBlocks{
	public:
		int n, m, ans, mn, mx, id[MAXN], od[MAXN], dp[(1 << 6) + 1], g[MAXN], level[MAXN], p[MAXN];
		vector <int> cnt, col[MAXN];
		int calc(int status){
			if(dp[status] != -1) return dp[status];
			int &cur = dp[status], i;
			for(i = 0; i < n; ++ i)
				if(((status & (1 << i)) == 0) && ((status & g[i]) == g[i]))
					cur += calc(status | (1 << i));
			return ++ cur;
		}
		int buildGraph(){
			int i, j, tot = 0;
			memset(od, 0, sizeof(od));
			memset(id, 0, sizeof(id));
			maxFlow.init(2 * n + 1, 2 * n + 2);
			for(i = 0; i <= n; ++ i)
				for(j = 0; j < n; ++ j)
					if(g[i] & (1 << j)){
						maxFlow.addEdge(j, i + n, INF);
						++ id[i], ++ od[j];
					}
			for(i = 0; i < n; ++ i){
				if(cnt[i] < od[i]) return -1;
				maxFlow.addEdge(2 * n + 1, i, cnt[i] - od[i]);
				tot += cnt[i] - od[i];
			}
			for(i = 0; i < n; ++ i){
				if(cnt[i] < id[i]) return -1;
				maxFlow.addEdge(n + i, 2 * n + 2, cnt[i] - id[i]);
			} maxFlow.addEdge(2 * n, 2 * n + 2, INF);
			return tot;
		}
		void dfs2(int dep){
			if(dep == 1)
				for(int i = 0; i < int(col[1].size()); ++ i)
					g[n] |= 1 << col[1][i];
			if(dep == m){
				int tmp = buildGraph();
				if(tmp != -1 && maxFlow.solve() == tmp){
					memset(dp, -1, sizeof(dp));
					dp[(1 << n) - 1] = 1, tmp = calc(0);
					if(tmp >= mn && tmp <= mx) ++ ans;
				} return;
			} int i, j, k, g_[MAXN];
			memcpy(g_, g, sizeof(g));
			for(i = 0; i < (1 << (col[dep].size() * col[dep + 1].size())); ++ i){
				memcpy(g, g_, sizeof(g));
				for(j = 0; j < int(col[dep].size()); ++ j)
					for(k = 0; k < int(col[dep + 1].size()); ++ k)
						if(i & (1 << (j * col[dep + 1].size() + k)))
							g[col[dep][j]] |= 1 << col[dep + 1][k];
				dfs2(dep + 1);
			}
		}
		void solve(){
			for(int i = 1; i <= m; ++ i)
				col[i].clear();
			for(int i = 0; i < n; ++ i)
				col[p[level[i]]].push_back(i);
			memset(g, 0, sizeof(g));
			dfs2(1);
		}
		void dfs(int dep, int lv){
			if(dep == n){
				for(int i = 1; i <= lv; ++ i) p[i] = i;
				m = lv;
				do solve();
				while(next_permutation(p + 1, p + 1 + lv));
				return;
			}
			for(int i = 1; i <= lv + 1; ++ i)
				level[dep] = i, dfs(dep + 1, max(i, lv));
		}
		int getNumOrders(vector <int> cnt, int mn, int mx){
			n = cnt.size();
			this -> cnt = cnt;
			this -> mn = mn;
			this -> mx = mx;
			dfs(0, 0);
			return ans;
		}
};
