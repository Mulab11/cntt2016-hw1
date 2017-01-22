/*
	Easy game theory.
	
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
template <typename tn> tn sqr(const tn &t){return t * t;}
const int MAXN = 128;
int hd[MAXN], to[MAXN], nxt[MAXN], sz[MAXN], fa[MAXN], tl;
void ae(int u, int v){++tl; to[tl] = v; nxt[tl] = hd[u]; hd[u] = tl;}
int n;
int sg[MAXN], ssg[MAXN];
set<int> s;
void dfs2(int p, int sum){ // Collect the sg values with brute force
	s.insert(sum);
	for (int i = hd[p]; i; i = nxt[i])
		dfs2(to[i], sum ^ sg[to[i]] ^ ssg[to[i]]);
}
void dfs(int p){
	ssg[p] = 0; // ssg = xor-sum of sg
	for (int i = hd[p]; i; i = nxt[i])
		dfs(to[i]), ssg[p] ^= sg[to[i]];
	s.clear(); dfs2(p, ssg[p]);
	rep(i, 0, n) if (!s.count(i)) {sg[p] = i; break;} // mex
}
class CirclesGame {
	public:
	string whoCanWin(vector <int> x, vector <int> y, vector <int> r) {
		memset(hd, 0, sizeof hd); tl = 0;
		n = x.size();
		rep(i, 0, n - 1){ // build the tree
			int id = -1;
			rep(j, 0, n - 1)
				if (r[j] > r[i] && (id == -1 || r[id] > r[j]) && sqr(x[i] - x[j]) + sqr(y[i] - y[j]) < sqr(r[j] - r[i]))
					id = j;
			fa[i] = id;
			if (id != -1) ae(id, i);
		}
		int s = 0;
		rep(i, 0, n - 1) if (fa[i] == -1) dfs(i), s ^= sg[i];
		return s ? "Alice" : "Bob";
	}
};

/*
	1112345678999
*/
