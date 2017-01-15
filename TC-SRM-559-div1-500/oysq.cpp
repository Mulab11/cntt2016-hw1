// BEGIN CUT HERE

// END CUT HERE
#line 5 "HatRack.cpp"
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

int n;
vector<int> adj[N + 9];// adj[i] -> nodes adjacent to i
bool ok[N + 9];// ok[i] -> if i can be root
int cnt[N + 9];// cnt[i] -> number of nodes in each depth
bool f[N + 9][3];
// f[i][0] = true -> in the subtree rooted at i, there exists nodes with 2 rods to bottom depth
// f[i][1] = true -> in the subtree rooted at i, there exists nodes with 1 rod to bottom depth
// f[i][2] = true -> in the subtree rooted at i, there exists nodes end at (bottom depth - 1)
// the order of 0,1,2 is 0 -> 1 -> 2

int getdep(int x, int fa) {// get the deepest node's depth
	int ret = -1;
	for(int i = 0; i < SZ(adj[x]); ++i)
		if(adj[x][i] != fa)
			chkmax(ret, getdep(adj[x][i], x));
	return ret + 1;
}

void getdepcnt(int x, int fa, int dep) {// count the nodes in each depth
	cnt[dep]++;
	for(int i = 0; i < SZ(adj[x]); ++i)
		if(adj[x][i] != fa)
			getdepcnt(adj[x][i], x, dep + 1);
}

int getsingle(int x, int fa, int dep, int mostdep) {// count the nodes with 1 rod to the bottom depth
	if(dep == mostdep - 1) {
		if(SZ(adj[x]) - (fa > 0) == 1) return 1;
		else return 0;
	}
	int ret = 0;
	for(int i = 0; i < SZ(adj[x]); ++i)
		if(adj[x][i] != fa)
			ret += getsingle(adj[x][i], x, dep + 1, mostdep);
	return ret;
}

ll calc(int x, int fa, int dep, int mostdep) {
	int c = SZ(adj[x]) - (fa > 0);
	if(dep == mostdep - 1) {
		if(c == 0) f[x][2] = true;
		else if(c == 1) f[x][1] = true;
		else f[x][0] = true;
		return 1 + (c == 2);
	}
	else {
		vector<ll> val;// children's return value
		vector<int> s;// children's id
		for(int i = 0; i < SZ(adj[x]); ++i)
			if(adj[x][i] != fa) {
				val.pb(calc(adj[x][i], x, dep + 1, mostdep));
				s.pb(adj[x][i]);
				for(int j = 0; j < 3; ++j)
					f[x][j] |= f[adj[x][i]][j];// update f
			}
		if(c == 2) {
			if(!f[s[0]][1] && !f[s[1]][1] && ((!f[s[0]][2] && !f[s[1]][2]) || (!f[s[0]][0] && !f[s[1]][0]))) return val[0] * val[1] * 2;// we can swap two subtrees or not
			else {
				// check if there exists an order of substrees satisfying the condition
				bool flag = true;
				for(int i = 0; i < 3; ++i)
					for(int j = 0; j < i; ++j)
						if(f[s[0]][i] && f[s[1]][j]) {
							flag = false;
							break;
						}
				if(flag) return val[0] * val[1];
				flag = true;
				for(int i = 0; i < 3; ++i)
					for(int j = 0; j < i; ++j)
						if(f[s[1]][i] && f[s[0]][j]) {
							flag = false;
							break;
						}
				if(flag) return val[0] * val[1];
				else return 0;
			}
		}
		else return val[0];
	}
}

struct HatRack {
    long long countWays(vector <int> knob1, vector <int> knob2) {
		n = SZ(knob1) + 1;
		for(int i = 1; i <= n; ++i) adj[i].clear();
		for(int i = 0; i < n - 1; ++i) adj[knob1[i]].pb(knob2[i]), adj[knob2[i]].pb(knob1[i]);// connect (knob1[i], knob2[i])
		for(int i = 1; i <= n; ++i) {
			if(SZ(adj[i]) <= 2) ok[i] = true;// ok[i] = true means it can be root of the tree
			else if(SZ(adj[i]) > 3) return 0ll;// binary tree requires each node's degree at most 3
		}
		ll ans = 0;
		for(int i = 1; i <= n; ++i) {//enumerate the root
			if(!ok[i]) continue;
			int dep = getdep(i, 0);// get the bottom depth of the tree
			memset(cnt, 0, sizeof cnt);
			getdepcnt(i, 0, 0);// get the number of nodes in each depth
			bool flag = true;
			for(int j = 0; j < dep; ++j)
				if(cnt[j] != (1ll << j)) {// check if number the of nodes on depth j equils 2 ^ j
					flag = false;
					break;
				}
			if(!flag) continue;
			int single = getsingle(i, 0, 0, dep);
			if(single > 1) continue;// at most 1 node with a single rod to the bottom
			memset(f, false, sizeof f);
			ans += calc(i, 0, 0, dep);// calculate the answer
		}
		return ans;
    }
};
