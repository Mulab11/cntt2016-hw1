/*
	Expected value
	Easy countings
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
const int MAXN = 333;
int n, fa[MAXN], f1[MAXN], f2[MAXN];
vector<int> E[MAXN];
class TreeUnion {
	public:
	void dfs(int Dst[], int p, int fa = -1, int s = 1){ // Count the chains of lengths [2,5]
		if (s > 1) ++Dst[s]; if (s > 5) return;
		rep(i, 0, (int)E[p].size() - 1) if (fa != E[p][i]) dfs(Dst, E[p][i], p, s + 1);
	}
	void calcTree(int Dst[], vector<string> tree){
		memset(Dst, 0, MAXN * 4);
		string s; rep(i, 0, (int)tree.size() - 1) s += tree[i];
		n = 0; stringstream ss(s); while (ss >> fa[++n]); // read complete
		rep(i, 0, n - 1) E[i].clear();
		rep(i, 1, n - 1) E[i].push_back(fa[i]), E[fa[i]].push_back(i); // make the tree
		rep(i, 0, n - 1) dfs(Dst, i); // Count
		rep(i, 2, 5) Dst[i] /= 2;
	}
	double expectedCycles(vector <string> tree1, vector <string> tree2, int k) {
		calcTree(f1, tree1); calcTree(f2, tree2);
		LL sum = 0; double p0 = 2.0 / n / (n - 1);
		rep(i, 2, k - 2) sum += f1[i] * f2[k - i]; // easy formula
		return sum * p0;
	}
};

/*
	if k > 7....?
	that's an another story...
*/
