/*
	Features of XOR
	Transform every flip into two flips that begin at the root
	Tree dp
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
const int MAXN = 60;
vector<int> E[MAXN];
bool imp[MAXN], mark[MAXN];
class TurnOnLamps {
	public:
	int dfs(int x){
		int ret = 0;
		rep(i, 0, (int)E[x].size() - 1) ret += dfs(E[x][i]);
		if (imp[x] && ((ret & 1) ^ mark[x])) ++ret; // Another flip on this node
		return ret;
	}
	int minimize(vector <int> roads, string initState, string isImportant) {
		int n = roads.size() + 1;
		rep(i, 0, n - 1) E[i].clear();
		rep(i, 0, n - 2) E[roads[i]].push_back(i + 1);
		rep(i, 1, n - 1) imp[i] = (isImportant[i - 1] == '1'), mark[i] = (initState[i - 1] == '0');
		return (dfs(0) + 1) / 2;
	}
};

/*
	Kantan sugiru kamo...
*/

