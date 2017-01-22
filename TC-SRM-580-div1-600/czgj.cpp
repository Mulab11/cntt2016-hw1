/*
	Brute force BFS
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
const int MAXN = 2600;
int s[MAXN], t[MAXN], f[MAXN], d1[MAXN], d2[MAXN];
bool vis[MAXN];
queue<int> q;
class ShoutterDiv1 {
	public:
	int getArgs(int Dst[], const vector<string> a, int w){
		int ret = 0;
		rep(i, 0, (int)a.size() - 1)
			rep(j, 0, (int)a[i].size() - 1)
				Dst[++ret] += w * (a[i][j] - '0');
		return ret;
	}
	int getArgs(int Dst[], const vector<string>& a1000, const vector<string>& a100, const vector<string>& a10, const vector<string>& a1){
		memset(Dst, 0, MAXN * sizeof(int));
		getArgs(Dst, a1000, 1000);
		getArgs(Dst, a100, 100);
		getArgs(Dst, a10, 10);
		return getArgs(Dst, a1, 1);
	}
	int count(vector <string> s1000, vector <string> s100, vector <string> s10, vector <string> s1, vector <string> t1000, vector <string> t100, vector <string> t10, vector <string> t1) {
		memset(d1, 0, sizeof d1); memset(d2, 0, sizeof d2);
		int n = getArgs(s, s1000, s100, s10, s1); getArgs(t, t1000, t100, t10, t1);
		// BFS : left -> right
		memset(vis, 0, sizeof vis);
		int l = 10000; rep(i, 1, n) l = min(t[i], l);
		rep(i, 1, n) if (s[i] <= l) vis[i] = 1, q.push(i);
		while (!q.empty()){
			int p = q.front(); q.pop();
			rep(i, 1, n) if (s[i] <= t[p] && !vis[i]) d1[i] = d1[p] + 1, vis[i] = 1, q.push(i);
		}
		rep(i, 1, n) if (!vis[i]) return -1; // judge if not connected
		// BFS : right -> left
		memset(vis, 0, sizeof vis);
		int r = -1; rep(i, 1, n) r = max(s[i], r);
		rep(i, 1, n) if (t[i] >= r) vis[i] = 1, q.push(i);
		while (!q.empty()){
			int p = q.front(); q.pop();
			rep(i, 1, n) if (t[i] >= s[p] && !vis[i]) d2[i] = d2[p] + 1, vis[i] = 1, q.push(i);
		}
		// ans = left + right
		rep(i, 1, n) f[i] = d1[i] + d2[i];
		// spj
		rep(i, 1, n) rep(j, 1, n) if (s[i] >= s[j] && t[i] <= t[j]) f[i] = min(f[i], f[j] + 1);
		// sum
		int ret = 0;
		rep(i, 1, n) ret += f[i];
		return ret;
	}
};

/*
	Akemashite omedetou!
*/

