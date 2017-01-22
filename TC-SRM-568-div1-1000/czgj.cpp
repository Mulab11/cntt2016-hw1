/*
	Brute force
	Bipartite graph
	Gauss elimination
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int _r = (r), i = (l); i <= _r; ++i)
#define red(i, r, l) for (int _l = (l), i = (r); i >= _l; --i)
#define xx first
#define yy second
using namespace std;
typedef long long LL;
typedef pair<int, int> PI;
const int K = 12;
const int MAXN = 64;
vector<int> a;
int n;
bool intersect(PI a, PI b){
	if (a > b) swap(a, b);
	return a.xx < b.xx && b.xx < a.yy && a.yy < b.yy;
}
namespace solve1{ // not so many unknown labels --> brute force && bipartite graph coloring
	vector<PI> b;
	vector<int> E[MAXN];
	bool mark[MAXN], vis[MAXN], col[MAXN];
	bool color(int x, bool c = 0){ // bipartite graph coloring
		if (vis[x] && c ^ col[x]) return 0;
		if (vis[x]) return 1;
		vis[x] = 1; col[x] = c;
		for (int y : E[x]) if (!color(y, !c)) return 0;
		return 1;
	}
	bool check(){ // make graph
		rep(i, 0, n - 1) E[i].clear();
		int t = b.size();
		rep(i, 0, t - 1) rep(j, i + 1, t - 1)
			if (intersect(b[i], b[j]))
				E[i].push_back(j), E[j].push_back(i);
		memset(vis, 0, sizeof vis);
		rep(i, 0, t - 1) if (!vis[i] && !color(i)) return 0;
		return 1;
	}
	bool dfs(int d){ // enumerate all possible matchings
		if (d >= n) return check();
		if (mark[d]) return dfs(d + 1);
		rep(i, d + 1, n - 1) if (!mark[i]){
			mark[i] = 1; b.push_back(PI(d, i));
			if (dfs(d + 1)) return 1;
			mark[i] = 0; b.pop_back();
		}
		return 0;
	}
	bool Main(){ // some pre-processing
		b.clear();
		rep(i, 0, n - 1)
			if (a[i] == -1) mark[i] = 0;
			else{
				mark[i] = 1;
				rep(j, i + 1, n - 1) if (a[j] == a[i]) b.push_back(PI(i, j));
			}
		return dfs(0);
	}
}
namespace solve2{ // not so many known labels --> brute force && Gauss elimination
	typedef bitset<64> bits;
	int m;
	vector<PI> b;
	bool mark[MAXN];
	bool check(bits mask){ // check this mask
		rep(i, 0, m - 1) rep(j, 0, m - 1) // invalid : known semicircles have intersected
			if (mask[i] == mask[j] && intersect(b[i], b[j]))
				return 0;
		// make xor equations by : the number of the points in the same direction should be even
		vector<bits> A; A.resize(m + 1);
		rep(i, 0, m - 1){
			int cnt = 0;
			rep(j, b[i].xx, b[i].yy) if (!mark[j]) ++cnt, A[i][j] = 1;
			A[i][n] = (mask[i]) && (cnt & 1);
		}
		rep(i, 0, n - 1) if (!mark[i]) A[m][i] = 1;
		int p = 0;
		rep(i, 0, n - 1){ // elimination
			int id = -1;
			rep(j, p, m) if (A[j][i]) {id = j; break;}
			if (id == -1) continue;
			swap(A[p], A[id]);
			rep(j, p + 1, m) if (A[j][i]) A[j] ^= A[p];
			++p;
		}
		bits fail; fail[n] = 1;
		rep(i, 0, m) if (A[i] == fail) return 0;
		return 1;
	}
	bool Main(){
		b.clear();
		rep(i, 0, n - 1) mark[i] = (a[i] != -1);
		rep(i, 0, n - 1) rep(j, i + 1, n - 1)
			if (a[i] != -1 && a[i] == a[j])
				b.push_back(PI(i, j));
		m = b.size();
		rep(i, 0, (1 << m) - 1) if (check(i)) return 1; // enumerate the direction of each semicircle
		return 0;
	}
}
class DisjointSemicircles {
	public:
	string getPossibility(vector <int> labels) {
		::a = labels; n = a.size();
		int cnt = 0;
		rep(i, 0, n - 1) cnt += (a[i] == -1);
		return (cnt <= K ? solve1::Main() : solve2::Main()) ? "POSSIBLE" : "IMPOSSIBLE";
	}
};

/*
	Withered leaf
*/
