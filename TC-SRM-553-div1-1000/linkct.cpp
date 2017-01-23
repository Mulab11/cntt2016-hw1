#include <bits/stdc++.h>
using namespace std;
const int MAXN = 55, MAXM = 55;
typedef long long int LL;
const LL INF = 0x3f3f3f3f3f3f3f3fLL;
typedef vector <int> vi;

class YamanoteLine{
public:
	LL g[MAXN][MAXN][MAXM * 2];
	inline void update(LL &a, LL b){if(a > b) a = b;}
	LL howMany(int n, vi gts, vi gtt, vi gtl, vi lts, vi ltt, vi ltl){
		int i, j, k, a, b, m; LL lb, ub;
		m = max(gts.size() + 1, lts.size());
		memset(g, 0x3f, sizeof(g));
		for(i = 1; i < n; ++ i)
			g[i + 1][i][m] = -1;
		g[1][n][m + 1] = -1;
		for(i = 0; i < int(gts.size()); ++ i){
			++ gts[i], ++ gtt[i];
			if(gts[i] < gtt[i]) update(g[gtt[i]][gts[i]][m], - gtl[i]);
			else update(g[gtt[i]][gts[i]][m + 1], - gtl[i]);
		}
		for(i = 0; i < int(lts.size()); ++ i){
			++ lts[i], ++ ltt[i];
			if(lts[i] < ltt[i]) update(g[lts[i]][ltt[i]][m], ltl[i]);
			else update(g[lts[i]][ltt[i]][m - 1], ltl[i]);
		}
		for(k = 1; k <= n; ++ k)
			for(i = 1; i <= n; ++ i)
				for(j = 1; j <= n; ++ j)
					for(a = -m; a <= m; ++ a)
						for(b = max(- m - a, - m); b <= min(m, m - a); ++ b)
							if(g[i][k][a + m] != INF && g[k][j][b + m] != INF)
								update(g[i][j][a + b + m], g[i][k][a + m] + g[k][j][b + m]);
		lb = n, ub = INF;
		for(i = 1; i <= n; ++ i){
			if(g[i][i][0] < 0) return 0;
			for(j = 0; j < m; ++ j){
				if(g[i][i][j] == INF) continue;
				ub = min(ub, g[i][i][j] / (m - j));
			}
			for(++ j; j <= 2 * m; ++ j){
				if(g[i][i][j] >= 0) continue;
				lb = max(lb, (- g[i][i][j] - 1) / (j - m) + 1);
			}
		} if(ub == INF) return -1;
		return max(ub - lb + 1, 0LL);
	}
};
