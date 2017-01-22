/*
	Tricky force.
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
typedef pair<int, int> PI;
const int MAXN = 60;
const int MAXM = 60 * 60;
int a[MAXN];
int ex[MAXM], ey[MAXM];
int g[MAXN][MAXN];
int n, ne, ret, limit;
void dfs(int dep, LL mask, bool upd = 1){
	if (__builtin_popcountll(mask) > limit) return; // not enough points left
	if (upd){ // update the answer
		bool ok = 1; int sum = 0;
		rep(i, dep, ne) if (!((mask >> ex[i] & 1) || (mask >> ey[i] & 1))) {ok = 0; break;} // not connected, fail
		if (ok){
			rep(i, 0, n - 1) if ((~mask >> i) & 1) sum += a[i];
			if (sum > ret) ret = sum;
		}
	}
	if (dep > ne) return;
	if ((mask >> ex[dep] & 1) || (mask >> ey[dep] & 1)) { //
		dfs(dep + 1, mask, 0); // take nothing
	}
	else {
		dfs(dep + 1, mask | (1ll << ex[dep])); // take x
		dfs(dep + 1, mask | (1ll << ey[dep])); // take y
	}
}
class MagicMolecule {
	public:
	int maxMagicPower(vector <int> magicPower, vector <string> magicBond) {
		n = magicPower.size(); ne = 0; limit = n - (n * 2 - 1) / 3 - 1; // limit = n - ceil(n * 2 / 3)
		rep(i, 0, n - 1) a[i] = magicPower[i];
		rep(i, 0, n - 1) rep(j, 0, i - 1)
			if (magicBond[i][j] == 'N')
				++ne, ex[ne] = i, ey[ne] = j;
		ret = -1; dfs(1, 0);
		return ret;
	}
};

/*
	114 514
		- 893
*/
