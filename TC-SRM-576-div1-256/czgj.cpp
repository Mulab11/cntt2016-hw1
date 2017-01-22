/*
	Simply build a MST.
*/

#include <bits/stdc++.h>
using namespace std;
const int MAXN = 23333;
struct edge{int u, v, w;}E[MAXN];
bool operator <(const edge& a, const edge& b){return a.w < b.w;}
class ArcadeManao {
	public:
	int r, c, e;
	int fa[MAXN]; // dsu
	int getf(int x){return fa[x] == x ? x : fa[x] = getf(fa[x]);} // dsu
	int getid(int r0, int c0){return r0 * c + c0;}
	int shortestLadder(vector <string> level, int coinRow, int coinColumn) {
		--coinRow, --coinColumn;
		r = level.size(); c = level[0].length(); e = 0;
		memset(fa, 0, sizeof fa);
		for (int i = 0; i < r * c; ++i) fa[i] = i; // initialization for dsu
		for (int i = 0; i < r; ++i) for (int j = 1; j < c; ++j)
			if (level[i][j] == 'X' && level[i][j - 1] == 'X')
				E[++e] = edge{getid(i, j), getid(i, j - 1), 0}; // connect adjacent cells
		for (int i = 0; i < r - 1; ++i) for (int j = 0; j < c; ++j) if (level[i][j] == 'X')
			for (int k = i + 1; k < r; ++k) if (level[k][j] == 'X'){
				E[++e] = edge{getid(i, j), getid(k, j), k - i}; // build ladders
				break;
			}
		sort(E + 1, E + e + 1);
		if (getf(getid(r - 1, 0)) == getf(getid(coinRow, coinColumn))) return 0; // spj 0
		for (int i = 1; i <= e; ++i){ // MST
			fa[getf(E[i].u)] = getf(E[i].v);
			if (getf(getid(r - 1, 0)) == getf(getid(coinRow, coinColumn))) return E[i].w;
		}
		return -1;
	}
};

/*
	Higurashi ga naku akazu no mori e
	Atomodori wa mou dekinai
		- Higurashi no Naku Koro ni
*/

