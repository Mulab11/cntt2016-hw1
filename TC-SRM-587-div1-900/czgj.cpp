/*
	Bipartite graph coloring
	Greedy
	Brute force
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
const int MAXN = 60;
int fa[MAXN], tag[MAXN]; // weighed dsu
int getf(int x){
	if (fa[x] == x) return x;
	int r = getf(fa[x]); tag[x] ^= tag[fa[x]];
	return fa[x] = r; 
}
bool merge(int u, int v, bool w){
	int fu = getf(u), fv = getf(v);
	if (fu == fv) return (tag[u] ^ tag[v]) == w;
	fa[fu] = fv; tag[fu] = tag[u] ^ tag[v] ^ w;
	return 1;
}
bool check(const vector<string> &a){
	int n = a.size(), m = a[0].size();
	rep(i, 0, n - 1) fa[i] = i, tag[i] = 0;
	rep(k, 0, m - 1)
		rep(i, 0, n - 1) if (a[i][k] != '?')
			rep(j, i + 1, n - 1) if (a[j][k] != '?')
				if (!merge(i, j, a[i][k] != a[j][k]))
					return 0;
	return 1;
}
class ThreeColorability {
	public:
	vector <string> lexSmallest(vector <string> cells) {
		if (!check(cells)) return vector<string>();
		rep(i, 0, (int)cells.size() - 1)
			rep(j, 0, (int)cells[0].size() - 1)
				if (cells[i][j] == '?'){ // determine each grid with brute force
					cells[i][j] = 'N';
					if (!check(cells)) cells[i][j] = 'Z';
				}
		return cells;
	}
};

/*
	straight-forward
	brute force
	which one is better?
*/
