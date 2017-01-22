/*
	Tree dp.
	be careful with checking if it is a perfect binary tree.
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN = 128;
bool ok[MAXN];
int hd[MAXN], to[MAXN], nxt[MAXN], sz[MAXN], tl;
void ae(int u, int v){++tl; to[tl] = v; nxt[tl] = hd[u]; hd[u] = tl;}
int n;
LL dfs(int p, int fa = 0){
	sz[p] = 1; vector<int> r, s;
	for (int i = hd[p]; i; i = nxt[i])
		if (to[i] != fa){
			r.push_back(dfs(to[i], p));
			s.push_back(sz[to[i]]);
			sz[p] += sz[to[i]];
		}
	if (r.size() == 0) return 1; // Leaf, 1
	if (r.size() == 1) return s[0] == 1; // only one child, that must be a leaf
	if (r.size() > 2 || !r[0] || !r[1]) return 0; // more than two children, invalid
	if (s[0] < s[1]) swap(s[0], s[1]);
	return s[0] == s[1] ? ok[s[0]] * r[0] * r[1] * 2 : // full
		((ok[s[1]] || ok[s[0]]) && s[0] < (s[1] + 1) * 2) * r[0] * r[1]; // perfect
}
class HatRack {
	public:
	long long countWays(vector <int> knob1, vector <int> knob2) {
		memset(hd, 0, sizeof hd); tl = 0;
		// mark 2^i-1, which can be a size of a full binary tree
		for (int i = 1; i <= 6; ++i) ok[(1 << i) - 1] = 1;
		n = knob1.size() + 1;
		for (int i = 0; i < n - 1; ++i) ae(knob1[i], knob2[i]), ae(knob2[i], knob1[i]);
		LL ret = 0;
		for (int i = 1; i <= n; ++i) ret += dfs(i); // Let i be the root
		return ret;
	}
};

/*
	INOCHI WO MOYASHI TSUKUSE
		- Inferno
*/
