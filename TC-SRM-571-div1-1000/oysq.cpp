#line 2 "CandyOnDisk.cpp"  
#include <bits/stdc++.h> 

using namespace std;  

#define ui unsigned
#define ll long long

#define pii std::pair<int,int>
#define mp std::make_pair
#define fi first
#define se second

#define SZ(x) (int)(x).size()
#define pb push_back

template<class T>inline void chkmax(T &x, const T &y) {if(x < y) x = y;}
template<class T>inline void chkmin(T &x, const T &y) {if(x > y) x = y;}

const int N = 50;

int n;
std::vector<double> d[N + 9];// 半径范围
std::vector<int> id[N + 9];// 它们的id
int tot;// id总数
std::vector<int> adj[N * N + 9];// 邻接表
int ids;// s所在的位置的id
int idt;// t所在的位置的id

ll sqr(int x) {// x ^ 2
	return (ll)x * x;
}

ll dist2(int x1, int y1, int x2, int y2) {// 两点距离的平方
	return sqr(x1 - x2) + sqr(y1 - y2);
}

bool bfs(int s, int t) {// bfs判断s, t是否有路径到达
	if(s == -1 || t == -1) {// s, t中有点不在之前求出来的范围内
		return false;
	}
	static bool vis[N * N + 9];
	memset(vis, false, sizeof vis);
	std::queue<int> q;
	q.push(s);
	vis[s] = true;
	while(!q.empty()) {
		int x = q.front();
		q.pop();
		for(auto i : adj[x]) {
			if(!vis[i]) {
				q.push(i);
				vis[i] = true;
			}
		}
	}
	return vis[t] == true;
}

bool eq(int x1, int y1, int x2, int y2) {// 判断坐标(x1, y1), (x2, y2)是否相等
	return x1 == x2 && y1 == y2;
}

class CandyOnDisk {  
public:  
	string ableToAchieve(vector <int> x, vector <int> y, vector <int> r, int sx, int sy, int tx, int ty) {
		if(sx == tx && sy == ty) {// 如果起点终点相同，肯定可以
			return "YES";
		}
		n = SZ(x);
		tot = 0;
		for(int i = 0; i < n * n; ++i) {
			adj[i].clear();
		}
		for(int i = 0; i < n; ++i) {// 如果s, t在同一个圆的同一半径上，肯定可以，否则至少要通过2个圆才能到达
			ll ds = dist2(sx, sy, x[i], y[i]);
			ll dt = dist2(tx, ty, x[i], y[i]);
			if(ds == dt && ds <= sqr(r[i])) {
				return "YES";
			}
		}
		for(int i = 0; i < n; ++i) {
			d[i].clear();
			for(int j = 0; j < n; ++j) {
				ll d2 = dist2(x[i], y[i], x[j], y[j]);
				if(!eq(x[i], y[i], x[j], y[j]) && d2 <= sqr(r[i] + r[j])) {// 两个圆如果相交，且圆心不在同一个点，那么相交的圆周范围内都是可以任意到达的
					d[i].pb(std::min((double)r[i], r[i] - (sqrt((double)d2) - r[j])));
				}
			}
			std::sort(d[i].begin(), d[i].end());
			d[i].resize(std::unique(d[i].begin(), d[i].end()) - d[i].begin());
			id[i].clear();
			for(int j = 0; j < SZ(d[i]); ++j) {
				id[i].pb(tot++);
				if(j) {// 同一个圆相邻圆周层连边
					adj[id[i][j]].pb(id[i][j - 1]);
					adj[id[i][j - 1]].pb(id[i][j]);
				}
			}
		}
		for(int i = 0; i < n; ++i) {
			for(int j = i + 1; j < n; ++j) {
				ll d2 = dist2(x[i], y[i], x[j], y[j]);
				if(!eq(x[i], y[i], x[j], y[j]) && d2 <= sqr(r[i] + r[j])) {// 相交的圆的圆周连边
					int li = std::lower_bound(d[i].begin(), d[i].end(), std::min((double)r[i], r[i] - (sqrt((double)d2) - r[j]))) - d[i].begin();
					int lj = std::lower_bound(d[j].begin(), d[j].end(), std::min((double)r[j], r[j] - (sqrt((double)d2) - r[i]))) - d[j].begin();
					adj[id[i][li]].pb(id[j][lj]);
					adj[id[j][lj]].pb(id[i][li]);
				}
			}
		}
		ids = -1;
		for(int i = 0; i < n; ++i) {// 求出s所在位置
			ll d2 = dist2(sx, sy, x[i], y[i]);
			if(SZ(d[i]) && d2 <= sqr(r[i])) {
				std::vector<double>::iterator j = std::lower_bound(d[i].begin(), d[i].end(), r[i] - sqrt((double)d2));
				if(j == d[i].end()) {
					continue;
				}
				ids = id[i][j - d[i].begin()];
				break;
			}
		}
		idt = -1;
		for(int i = 0; i < n; ++i) {// 求出t所在位置
			ll d2 = dist2(tx, ty, x[i], y[i]);
			if(SZ(d[i]) && d2 <= sqr(r[i])) {
				std::vector<double>::iterator j = std::lower_bound(d[i].begin(), d[i].end(), r[i] - sqrt((double)d2));
				if(j == d[i].end()) {
					continue;
				}
				idt = id[i][j - d[i].begin()];
				break;
			}
		}
		return bfs(ids, idt) ? "YES" : "NO";
	}    
};  
