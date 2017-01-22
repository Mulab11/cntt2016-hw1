/*
	spanning arborescence
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
struct edge{int fr, v;};
bool operator <(edge a, edge b){return a.v < b.v;}
const int MAXN = 100;
vector<edge> E[MAXN];
edge pre[MAXN];
int vis[MAXN], fa[MAXN];
int rt, n;
void init(int n, const vector<string> &ss){
	string st = " ";
	rep(i, 0, n * 10) E[i].clear();
	rep(i, 0, (int)ss.size() - 1) st += ss[i];
	int m = st.size() / 12;
	rep(i, 0, m - 1){
		char p1, p2; int lv1, lv2, cost;
		sscanf(st.c_str() + i * 12, " %c%d->%c%d:%04d", &p1, &lv1, &p2, &lv2, &cost);
		if (p1 != p2 || lv1 != lv2) E[(p2 - 'A') * 10 + lv2].push_back(edge{(p1 - 'A') * 10 + lv1, cost});
	}
	rep(i, 0, n - 1) rep(j, 0, 8) E[i * 10 + j].push_back(edge{i * 10 + j + 1, 0});
	rt = n * 10; rep(i, 0, n - 1) E[i * 10].push_back(edge{rt, 0});
	rep(i, 0, rt) fa[i] = i;
}
int getf(int x){ // dsu
	return fa[x] == x ? x : fa[x] = getf(fa[x]);
}
int ZhuLiu(){
	int ret = 0, sum = 0, tot = 0; bool cycle = 0;
	rep(i, 0, rt - 1) if (fa[i] == i){
		if (E[i].empty()) return -1; // not connected, failed
		ret += (pre[i] = *min_element(E[i].begin(), E[i].end())).v;
	}
	memset(vis, 0, sizeof vis);
	rep(i, 0, rt - 1) if (fa[i] == i && !vis[i]){ // contract cycles when found
		int p; vector<int> a; ++tot;
		for (p = i; !vis[p] && p != rt; p = getf(pre[p].fr))
			vis[p] = tot, a.push_back(p);
		if (vis[p] == tot){
			a.erase(a.begin(), find(a.begin(), a.end(), p)); // now A contains all the nodes in the circle
			vector<edge> te;
			for (int u : a) fa[u] = p, sum += pre[u].v; // contract A to p
			for (int u : a) for (edge e : E[u]) if (getf(e.fr) != p)
				te.push_back(edge{e.fr, e.v - pre[u].v}); // make new edges, avoid self loops
			E[p] = te; cycle = 1;
		}
	}
	if (!cycle) return ret;
	int t = ZhuLiu();
	return t == -1 ? -1 : t + sum;
}
class FoxTheLinguist {
	public:
	int minimalHours(int n, vector <string> courseInfo) {
		init(n, courseInfo);
		return ZhuLiu();
	}
};

/*
	.....Unfortunately no model for this.
*/
