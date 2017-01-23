#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
const int MAXN = 55;

class HatRack{
public:
	int g[MAXN], nxt[MAXN << 1], to[MAXN << 1], edgeSize;
	int size[MAXN], n;
	int solveComp(int x, int f, int dep){ //Calculate the number of legal ordering when id of x is fixed as 1, and subtree x is a complete binary tree
		if(!x) return dep == 0;
		if(dep == 1) return size[x] == 1;
		int p, l = 0, r = 0;
		for(p = g[x]; p; p = nxt[p]){
			if(to[p] == f) continue;
			if(!l) l = to[p];
			else if(!r) r = to[p];
			else return 0;
		} if(size[l] < size[r]) swap(l, r);
		if(size[l] == (1 << (dep - 1)) - 1){ //Case 1: left subtree is a perfect bin. tree of depth dep-1, so the right one is a complete bin. tree of depth dep-1
			if(size[r] == (1 << (dep - 2)) - 1)
				return solveFull(l, x, dep - 1) * solveFull(r, x, dep - 2); //Subcase of case 1: the right subtree degenerates to be a perfect bin. tree of depth dep-2
			return solveFull(l, x, dep - 1) * solveComp(r, x, dep - 1);
		}
		if(size[r] != (1 << (dep - 2)) - 1) return 0;
		return solveComp(l, x, dep - 1) * solveFull(r, x, dep - 2); //Case 2: left subtree is not a perfect bin. tree
	}
	int solveFull(int x, int f, int dep){ //Calculate the number of legal ordering when id of x is fixed as 1, and subtree x is a perfect binary tree
		if(!x) return dep == 0;
		if(dep == 1) return size[x] == 1;
		int p, l = 0, r = 0;
		for(p = g[x]; p; p = nxt[p]){
			if(to[p] == f) continue;
			if(!l) l = to[p];
			else if(!r) r = to[p];
			else return 0;
		} if(size[l] != size[r]) return 0;
		return solveFull(l, x, dep - 1) * solveFull(r, x, dep - 1) * 2;
	}
	int getSize(int x, int f){
		size[x] = 1;
		for(int p = g[x]; p; p = nxt[p])
			if(to[p] != f)
				size[x] += getSize(to[p], x);
		return size[x];
	}
	void addEdge(int u, int v){
		nxt[++ edgeSize] = g[u];
		to[g[u] = edgeSize] = v;
	}
	LL countWays(vector <int> st, vector <int> ed){
		int i, dep; LL ans = 0LL;
		n = st.size() + 1;
		for(i = dep = 1; i <= n; i <<= 1, ++ dep) ;
		-- dep;
		for(i = 0; i < n - 1; ++ i)
			addEdge(st[i], ed[i]), addEdge(ed[i], st[i]);
		for(i = 1; i <= n; ++ i){ //Enumerate nodes to be #1
			getSize(i, -1);
			if(n == (1 << dep) - 1) ans += solveFull(i, -1, dep);
			else ans += solveComp(i, -1, dep);
		} return ans;
	}
};
