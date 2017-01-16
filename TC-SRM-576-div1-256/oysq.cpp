// BEGIN CUT HERE

// END CUT HERE
#line 5 "ArcadeManao.cpp"
#include <bits/stdc++.h>

using namespace std;

#define SZ(x) (int)(x).size()
#define pb push_back
#define mp make_pair
#define fi first
#define se second

typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<double> VD;
typedef long long ll;
typedef pair<int,int> pii;

template<class T>inline void chkmax(T &x, const T &y) {if(x < y) x = y;}
template<class T>inline void chkmin(T &x, const T &y) {if(x > y) x = y;}

const int N = 50;

int n, m;
bool vis[N + 9][N + 9];
std::queue<pii> q;

void push(int x, int y) {// 入队
	if(!vis[x][y]) vis[x][y] = true, q.push(mp(x, y));
}

bool check(int len, int cx, int cy, std::vector<std::string> g) {// bfs判断能否到达
	memset(vis, false, sizeof vis);
	push(n - 1, 0);
	while(!q.empty()) {
		pii p = q.front();q.pop();
		if(p.se && g[p.fi][p.se - 1] == 'X') push(p.fi, p.se - 1);// 左移
		if(p.se < m - 1 && g[p.fi][p.se + 1] == 'X') push(p.fi, p.se + 1);// 右移
		for(int i = 0; i < n; ++i)// 上下用梯子走
			if(g[i][p.se] == 'X' && abs(i - p.fi) <= len)
				push(i, p.se);
	}
	if(g[cx][cy] == 'X') {
		if(cy && vis[cx][cy - 1]) return true;
		if(cy < m - 1 && vis[cx][cy + 1]) return true;
	}
	for(int i = 0; i < n; ++i)
		if(vis[i][cy] && abs(i - cx) <= len)
			return true;
	return false;
}

struct ArcadeManao {
    int shortestLadder(vector <string> g, int cx, int cy) {
		cx--, cy--;
		n = SZ(g), m = SZ(g[0]);
		int l = 0, r = n;
		while(l < r) {// 二分答案
			int mid = (l + r) >> 1;
			if(check(mid, cx, cy, g)) r = mid;
			else l = mid + 1;
		}
		return l;
    }
};
