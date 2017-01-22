/*
	Maximum bipartite matching
*/

#include <bits/stdc++.h>
#define mem(x, y) memset(x, (y), sizeof x)
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
const int MAXN = 63;
char ban;
string c;
vector<string> g;
int n, p[MAXN];
bool vis[MAXN];
class GearsDiv1 {
	public:
	char c1, c2;
	bool dfs(int x){ // Hungarian Algorithm
		if (vis[x]) return 0;
		vis[x] = 1;
		rep(i, 0, n - 1)
			if (c[i] == c2 && g[x][i] == 'Y' && (p[i] < 0 || dfs(p[i]))){
				p[i] = x; return 1;
			}
		return 0;
	}
	int solve(char a, char b){ // Try disconnect every pair of color(a, b)
		int ret = 0; c1 = a; c2 = b;
		memset(p, -1, sizeof p);
		rep(i, 0, n - 1) if (c[i] == c1) mem(vis, 0), ret += dfs(i);
		return ret;
	}
	int getmin(string color, vector <string> graph) {
		n = color.size(); c = color; g = graph;
		return min({solve('R', 'G'), solve('G', 'B'), solve('B', 'R')});
	}
};

/*
	2 ways to match
*/
