/*
	Conclusion.
	Thx to the /Solution/.
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
const int MAXN = 2333;
const int nn = 63;
vector<int> E[MAXN];
int dA[MAXN], dB[MAXN];
int id[nn][nn];
int N, A, B;
void add(int u, int v){
	E[u].push_back(v);
	E[v].push_back(u);
}
void bfs(int x, int d[]){
	static int q[MAXN], l, r;
	rep(i, 1, N) d[i] = -1;
	for (l = r = d[x] = 0, q[0] = x; l <= r; ++l)
		for (int v : E[q[l]]) if (d[v] < 0)
			d[q[++r] = v] = d[q[l]] + 1; 
}
int dfs(int u, int fa){
	int ret = 1;
	for (int v : E[u]) if (fa != v) ret = max(ret, dfs(v, u) + 1);
	return ret;
}
class GameInDarknessDiv1 {
	public:
	string check(vector <string> field) {
		memset(id, 0, sizeof id);
		int n = field.size(), m = field[0].size();
		rep(i, 0, n - 1) rep(j, 0, m - 1) if (field[i][j] != '#'){
			id[i][j] = ++N;
			if (field[i][j] == 'A') A = N;
			if (field[i][j] == 'B') B = N;
		}
		rep(i, 1, N) E[i].clear();
		rep(i, 0, n - 1) rep(j, 0, m - 1) if (id[i][j]){ // build tree
			if (id[i + 1][j]) add(id[i][j], id[i + 1][j]);
			if (id[i][j + 1]) add(id[i][j], id[i][j + 1]);
		}
		bfs(A, dA); bfs(B, dB); // calculate distance from A and B
		rep(i, 1, N){ // magic conclusion
			if (dA[i] < dB[i] + 2) continue;
			int cnt = 0;
			for (int j : E[i]) cnt += (dfs(j, i) >= 3);
			if (cnt >= 3) return "Bob wins"; 
		}
		return "Alice wins";
	}
};

/*
	Arisu to Bobu wa itsumo asondeiru
*/
