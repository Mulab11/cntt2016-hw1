#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = l, _r = r; i <= _r; ++i)
#define red(i, r, l) for (int i = r, _l = l; i >= _l; --i)
#define MEM(x, y) memset(x, y, sizeof x)
using namespace std;
typedef long long LL;
typedef vector<int> VI;
const int MAXN = 63;
const int NN = 60;
const LL INF = 0x3f3f3f3f3f3f3f3fll;
LL d[MAXN][MAXN][MAXN * 2];
void cmin(LL &x, LL y){x = min(x, y);}
void cmax(LL &x, LL y){x = max(x, y);}
class YamanoteLine{
	public:
	LL howMany(int n, VI s1, VI t1, VI l1, VI s2, VI t2, VI l2){
		MEM(d, 0x3f);
		rep(i, 0, n) d[i][i][NN] = 0;
		rep(i, 0, n - 1) d[i + 1][i][NN] = -1;
		d[0][n][NN + 1] = d[n][0][NN - 1] = 0;
		
		rep(i, 0, s1.size() - 1) cmin(d[t1[i]][s1[i]][NN + (s1[i] > t1[i])], -l1[i]);
		rep(i, 0, s2.size() - 1) cmin(d[s2[i]][t2[i]][NN - (s2[i] > t2[i])], l2[i]);
		
		rep(k, 0, n) rep(i, 0, n) rep(x, -NN, NN) if (d[i][k][x + NN] != INF)
			rep(j, 0, n) rep(y, max(-NN, -NN - x), min(NN, NN - x)) if(d[k][j][y + NN] != INF)
				cmin(d[i][j][NN + x + y], d[i][k][x + NN] + d[k][j][y + NN]);

		LL l = n, r = INF;
		rep(i, 0, n) rep(j, -NN, NN) if(j){
			if (d[i][i][j + NN] != INF){
				if (j > 0) cmax(l, (-d[i][i][j + NN] - 1) / j + 1);
				else cmin(r, d[i][i][j + NN] / (-j));
			}
		}
		else if (d[i][i][j + NN] < 0) return 0;
		
		if (r == INF) return -1;
		return max(0ll, r - l + 1);
	}
};

