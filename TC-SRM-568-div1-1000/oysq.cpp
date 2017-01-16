#line 2 "DisjointSemicircles.cpp"  
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
const int INF = 1e9;

int n;
std::vector<int> lab;
std::vector<pii> ori;
int l[N + 9], r[N + 9];

int col[N + 9];

bool inter(const pii &p, const pii &q) {
	bool f1 = p.fi >= q.fi && p.fi <= q.se;
	bool f2 = p.se >= q.fi && p.se <= q.se;
	return f1 != f2;
}

bool color(int x, int c) {
	col[x] = c;
	for(int i = 0; i < n; ++i)
		if(x != i && inter(ori[x], ori[i])) {
			if(col[i] != -1) {
				if(col[i] + col[x] != 1)
					return false;
			}
			else {
				if(!color(i, !c))
					return false;
			}
		}
	return true;
}

bool check() {
	memset(col, -1, sizeof col);
	for(int i = 0; i < n; ++i)
		if(col[i] == -1)
			if(!color(i, 0))
				return false;
	return true;
}

bool dfsedge(int x) {
	if(x == n * 2)
		return check();
	if(lab[x] == -1) {
		lab[x] = INF;
		for(int i = x + 1; i < SZ(lab); ++i)
			if(lab[i] == -1) {
				lab[i] = INF;
				ori.pb(mp(x, i));
				if(dfsedge(x + 1))
					return true;
				ori.pop_back();
				lab[i] = -1;
			}
		lab[x] = -1;
	}
	else {
		if(dfsedge(x + 1))
			return true;
	}
	return false;
}

bool solve1() {
	return dfsedge(0);
}

std::vector<pii> adj[N + 9];
int pt[N + 9];

bool getpt(int x, int p) {
	pt[x] = p;
	for(int i = 0; i < SZ(adj[x]); ++i) {
		int y = adj[x][i].fi, v = adj[x][i].se;
		if(pt[y] != -1) {
			if(pt[y] != (pt[x] ^ v))
				return false;
		}
		else {
			if(!getpt(y, p ^ v))
				return false;
		}
	}
	return true;
}

bool solve2() {
	static int fb[N + 9];
	memset(fb, 0, sizeof fb);
	for(int i = 0; i < SZ(ori); ++i)
		for(int j = i + 1; j < SZ(ori); ++j)
			if(inter(ori[i], ori[j]))
				fb[i] |= 1 << j, fb[j] |= 1 << i;
	for(int i = 0; i < (1 << SZ(ori)); ++i) {
		bool valid = true;
		for(int j = 0; j < SZ(ori); ++j)
			if(i >> j & 1) {
				if(fb[j] & i) {
					valid = false;
					break;
				}
			}
			else {
				if(fb[j] & ((1 << SZ(ori)) - 1 - i)) {
					valid = false;
					break;
				}
			}
		if(!valid) continue;
		for(int j = 0; j <= n * 2; ++j)
			adj[j].clear();
		for(int j = 0; j < SZ(ori); ++j)
			if(i >> j & 1) {
				adj[ori[j].fi + 1].pb(mp(ori[j].se, 0));
				adj[ori[j].se].pb(mp(ori[j].fi + 1, 0));
				adj[ori[j].fi].pb(mp(ori[j].fi + 1, 1));
				adj[ori[j].fi + 1].pb(mp(ori[j].fi, 1));
				adj[ori[j].se].pb(mp(ori[j].se + 1, 1));
				adj[ori[j].se + 1].pb(mp(ori[j].se, 1));
			}
			else {
				int l = ori[j].se - ori[j].fi + 1;
				adj[ori[j].fi + 1].pb(mp(ori[j].se, l & 1));
				adj[ori[j].se].pb(mp(ori[j].fi + 1, l & 1));
				adj[ori[j].fi].pb(mp(ori[j].fi + 1, 0));
				adj[ori[j].fi + 1].pb(mp(ori[j].fi, 0));
				adj[ori[j].se].pb(mp(ori[j].se + 1, 0));
				adj[ori[j].se + 1].pb(mp(ori[j].se, 0));
			}
		adj[0].pb(mp(n * 2, 0)), adj[n * 2].pb(mp(0, 0));
		memset(pt, -1, sizeof pt);
		bool ok = true;
		for(int j = 0; j <= n * 2; ++j)
			if(pt[j] == -1)
				if(!getpt(j, 0)) {
					ok = false;
					break;
				}
		if(ok) return true;
	}
	return false;
}

class DisjointSemicircles {  
public:  
	string getPossibility(vector <int> _lab) {
		memset(l, -1, sizeof l), memset(r, -1, sizeof r), ori.clear(), lab = _lab;
		n = SZ(lab) / 2;
		for(int i = 0; i < n * 2; ++i)
			if(lab[i] != -1) {
				if(l[lab[i]] == -1) l[lab[i]] = i;
				else r[lab[i]] = i, ori.pb(mp(l[lab[i]], i));
			}
		bool ans;
		if(SZ(ori) >= 18) ans = solve1();
		else ans = solve2();
		if(ans) return "POSSIBLE";
		else return "IMPOSSIBLE";
	}  
};  
